#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int N = 1e6;

vector<int> c[N], g[N];

int md, mv;
void dfs( int v, int p, int d ) {
	if (d > md)
		md = d, mv = v;
	for (int x : c[v])
		if (x != p)
			dfs(x, v, d + 1);
}
void dfs2( int v, int p, int d ) {
	md += d;
	for (int x : c[v])
		if (x != p)
			dfs2(x, v, d + 1);
}

int diam() {
	mv = 0;
	md = 0, dfs(mv, -1, 0);
	md = 0, dfs(mv, -1, 0);
	return md;
}

int p[N];

int get( int i ) {
	return i == p[i] ? i : (p[i] = get(p[i]));
}
void join( int a, int b ) {
	p[get(a)] = get(b);
}

void add( int a, int b ) {
	c[a].push_back(b);
	c[b].push_back(a);
}

void gen_random( int n ) {
	forn(i, n)
		p[i] = i, c[i].clear();
	forn(i, n - 1) {
		int a, b;
		do {
			a = rand() % n;
			b = rand() % n;
		} while (get(a) == get(b));
		join(a, b);
		add(a, b);
	}		
}

int deg( int n ) {
	int x = 0;
	forn(i, n) x = max(x, (int)c[i].size());
	return x;
}

int used[N], size[N];

void calc_size( int v, int p = -1 ) {
	size[v] = 1;
	for (int x : g[v])
		if (x != p && !used[x]) 
			calc_size(x, v), size[v] += size[x];
}

vector<int> candidates;
void centroid( int v, int p, int all ) {
	bool good = 2 * (all - size[v]) <= all;
	for (int x : g[v])
		if (x != p && !used[x]) 
			centroid(x, v, all), good &= 2 * size[x] <= all;
	if (good)
		candidates.push_back(v);
}

bool check( int v ) {
	calc_size(v);
	candidates.clear();
	centroid(v, -1, size[v]);
	bool good = 0;
	for (int x : candidates)
		good |= x == v;
	if (!good) {
		// puts("EXIT");
		return 0;
	}
	used[v] = 1;
	for (int x : g[v])
		if (!used[x]) {
			// printf("%d --> %d\n", v, x);
			if (!check(x))
				return 0;
		}
	return 1;
}

bool check_centroid( int n ) {
	forn(i, n)
		g[i] = c[i], used[i] = 0;
	calc_size(0);
	candidates.clear();
	centroid(0, -1, size[0]);
	vector<int> to_check = candidates;
	for (int root : to_check) {
		// printf("check %d\n", root);
		forn(i, n)
			g[i] = c[i], used[i] = 0;
		if (check(root))
			return 1;
	}
	return false;
}

void build( int v, int p = -1 ) {
	// printf("build: v = %d, p = %d\n", v, p);
	calc_size(v);
	// puts(".");
	candidates.clear();
	centroid(v, -1, size[v]);
	assert(candidates.size());
	int save = candidates[0];
	// if (p == -1) printf("gen_centroid: start from %d\n", save);
	// else printf("%d --> %d\n", p, save);
	used[save] = 1;
	// printf("save = %d\n", save);
	if (p != -1)
		add(save, p);
	for (int x : g[save])
		if (!used[x]) {
			build(x, save);
		}
}

void gen_centroid( int n ) {
	gen_random(n);
	forn(i, n)
		used[i] = 0, g[i] = c[i], c[i].clear();
	build(0);
}

int diam2() {
	calc_size(0);
	centroid(0, -1, size[0]);
	md = 0;
	dfs2(candidates[0], -1, 0);
	return md;
}

int main() {
	// int t = 0, n = 60, M = 1e6 / n;
	// double mi1 = N, ma1 = 0;
	// double mi2 = N, ma2 = 0;
	// double x, y;
	// // scanf("%d%d", &t, &n);
	// forn(_, M) {
	// 	// puts(".");
	// 	gen_random(n);
	// 	x = diam();
	// 	mi1 = min(mi1, x);
	// 	ma1 = max(ma1, x);
	// 	assert(!check_centroid(n));

	// 	gen_centroid(n);
	// 	x = diam();
	// 	mi2 = min(mi2, x);
	// 	ma2 = max(ma2, x);
	// 	assert(check_centroid(n));
	// }
	// fprintf(stderr, "n = %d\n", n);
	// fprintf(stderr, "diam(random)   = %.3f .. %.3f\n", mi1, ma1);
	// fprintf(stderr, "diam(centroid) = %.3f .. %.3f\n", mi2, ma2);
	// gen_centroid(n);
	// printf("diam(centroid) = %d\n", diam());	
	int n, t;
	scanf("%d%d", &t, &n);
	while (t--) {
		forn(i, n)
			c[i].clear();
		forn(i, n - 1) {
			int a, b;
			scanf("%d%d", &a, &b), a--, b--;
			add(a, b);
		}
		puts(check_centroid(n) ? "Centroid" : "Random");
	}
}
