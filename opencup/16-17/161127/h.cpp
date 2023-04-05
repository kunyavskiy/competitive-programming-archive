#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define pb push_back 

typedef long long ll;
typedef pair<int, int> pii;

const int N = 1010, VN = N * N, K = 20;

int n, m, d[VN], p[VN];
int dep[VN], up[VN][K], w[VN][K];
char s[N][N];
queue<pii> q;
vector<int> g[VN];

int get( int v ) {
	return v == p[v] ? v : (p[v] = get(p[v]));
}

int v( int i, int j ) {
	return i * n + j;
}

void add(int i, int j, int D) {
	if (0 <= i && i < n && 0 <= j && j < n && d[v(i, j)] == -1)
		d[v(i, j)] = D, q.push(pii(i, j));
}

struct Cell {
	int i, j;
	bool operator < ( Cell c ) const {
		return d[v(i, j)] > d[v(c.i, c.j)];
	}
};
vector<Cell> cs;

void adde( int i1, int j1, int i2, int j2 ) {
	if (!(0 <= i2 && i2 < n && 0 <= j2 && j2 < n && s[i2][j2] == '+'))
		return;
	int a = v(i1, j1), b = v(i2, j2);
	if (get(a) != get(b)) 
		p[get(a)] = get(b), g[a].pb(b), g[b].pb(a);
}

void dfs( int v, int pr, int depth ) {
	dep[v] = depth;
	up[v][0] = pr, w[v][0] = d[v];
	forn(k, K - 1) {
		up[v][k + 1] = up[up[v][k]][k];
		w[v][k + 1] = min(w[v][k], w[up[v][k]][k]);
	}
	for (int x : g[v])
		if (x != pr)
			dfs(x, v, depth + 1);
}

int main() {
	scanf("%d", &n);
	memset(d, -1, sizeof(d));
	forn(i, n) 
		scanf("%s", s[i + 1] + 1);
	n += 2;
	forn(i, n) 
		forn(j, n)
			if (!i || !j || i == n - 1 || j == n - 1)
				s[i][j] = '#';
	forn(i, n) 
		forn(j, n)
			if (s[i][j] == '#')
				add(i, j, 0);
			else
				cs.pb({i, j});
	while (!q.empty()) {
		pii p = q.front(); q.pop();
		int i = p.first, j = p.second, D = d[v(i, j)] + 1;
		for (int di = -1; di <= 1; di++)
			for (int dj = -1; dj <= 1; dj++)
				add(i + di, j + dj, D);
	} 
	sort(cs.begin(), cs.end());
	forn(i, n * n)
		p[i] = i;
	for (Cell c : cs) {
		s[c.i][c.j] = '+';
		adde(c.i, c.j, c.i + 1, c.j);
		adde(c.i, c.j, c.i, c.j + 1);
		adde(c.i, c.j, c.i - 1, c.j);
		adde(c.i, c.j, c.i, c.j - 1);
	}
	for (auto c : cs) {
		int x = v(c.i, c.j);
		if (!dep[x])
			dfs(x, x, 1);
	}

	scanf("%d", &m);
	while (m--) {
		int i1, j1, i2, j2;
		scanf("%d%d%d%d", &i1, &j1, &i2, &j2);
		int a = v(i1, j1), b = v(i2, j2), res = INT_MAX;
		if (get(a) != get(b)) {
			puts("0");
			continue;
		}
		forn(t, 2) {
			for (int k = K - 1; k >= 0; k--)
				if (dep[a] - (1 << k) >= dep[b])
					res = min(res, w[a][k]), a = up[a][k];
			swap(a, b);
		}
		for (int k = K - 1; k >= 0; k--)
			if (up[a][k] != up[b][k]) {
				res = min(res, w[a][k]), a = up[a][k];
				res = min(res, w[b][k]), b = up[b][k];
			}
		if (a != b) {
			res = min(res, w[a][0]), a = up[a][0];
			res = min(res, w[b][0]), b = up[b][0];
		}
		res = min(res, d[a]);
		printf("%d\n", !res ? 0 : (res * 2 - 1));
	}
}
