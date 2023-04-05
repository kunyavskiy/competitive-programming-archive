/**                        
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

/** Begin fast allocation */
const int MAX_MEM = 5e8;
int mpos = 0;
char mem[MAX_MEM];
inline void * operator new ( size_t n ) {
	assert((mpos += n) <= MAX_MEM);
	return (void *)(mem + mpos - n);
}
inline void operator delete ( void * ) noexcept { } // must have!
/** End fast allocation */

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a).size()

typedef long long ll;
typedef pair<int, int> pii;

const int N = 1e5, K = 17;
const int VN = K * N + N;

int n, m, q, centroid, color[N], level[N], parent[N];
int d[K][N], start[N], cc;
vector<int> c[N];
vector<pii> order[N], g[VN];
ll dist[VN];

void add_edge( int a, int b, int w ) {
	// printf("[n=%d] edge: %d --%d--> %d\n", n, a, w, b);
	assert(a < VN && b < VN);
	g[b].push_back({a, w});
}

int get_centroid( int v, int p, int n ) {
	int size = 1;
	for (int x : c[v])
		if (x != p && level[x] == -1)
			size += get_centroid(x, v, n);
	if (centroid == -1 && (size * 2 >= n || p == -1))
		centroid = v;
	return size;
}

void calc( int *d, int v, int dep, int pr = -1 ) {
	d[v] = dep;
	// printf("center = %d, v = %d, dist = %d\n", centroid, v, dep);
	order[centroid].push_back(pii(dep, v));
	for (int x : c[v])
		if (x != pr && level[x] == -1)
			calc(d, x, dep + 1, v);
}

void build( int v, int p, int dep, int size ) {
	assert(dep < K);
	centroid = -1;
	get_centroid(v, -1, size);
	int C = centroid;
	calc(d[dep], C, 0);
	sort(all(order[C]));
	forn(i, sz(order[C]) - 1)
		add_edge(n + cc + i + 1, n + cc + i, 0);
	forn(i, sz(order[C]))
		add_edge(n + cc + i, order[C][i].second, 0);
	start[C] = cc, cc += sz(order[C]);
	level[C] = dep, parent[C] = p;
	for (int x : c[C])
		if (level[x] == -1)
			build(x, C, dep + 1, size / 2);
}

int main() {
	scanf("%d%d%d", &n, &m, &q);
	forn(i, n - 1) {
		int a, b;
		scanf("%d%d", &a, &b), a--, b--;
		c[a].push_back(b);
		c[b].push_back(a);
	}
	memset(level, -1, sizeof(level));
	build(0, -1, 0, n);
	while (m--) {
		int v, k, w;
		scanf("%d%d%d", &v, &k, &w), v--;
		// printf("--------------------- v=%d k=%d w=%d\n", v, k, w);
		for (int c = v; c != -1; c = parent[c])
			if (d[level[c]][v] <= k) {
				int rest = k - d[level[c]][v];
				int pos = lower_bound(all(order[c]), pii(rest + 1, -1)) - order[c].begin();
				// printf("center=%d, distance=%d [rest=%d, pos=%d]\n", c, d[level[c]][v], rest, pos);
				assert(pos > 0);
				add_edge(v, n + start[c] + pos - 1, w);
			}
	}

	fill(dist, dist + VN, (ll)1e18);
	dist[0] = 0;

	typedef pair<ll, int> T;
	priority_queue<T, vector<T>, greater<T>> s;

	s.push(make_pair(dist[0], 0));
	while (s.size()) {
		auto top = s.top();//*s.begin();
		int v = top.second;
		s.pop();//erase(s.begin());
		if (dist[v] != top.first) continue;
		for (auto p : g[v]) {
			int x = p.first;
			ll tmp = dist[v] + p.second;
			if (dist[x] > tmp) {
				s.push(make_pair(dist[x] = tmp, x));
			}
		}

	}

	while (q--) {
		int v;
		scanf("%d", &v), v--;
		if (dist[v] > 1e9 * 1e6)
			puts("Impossible");
		else
			printf("%lld\n", dist[v]);
	}
}
