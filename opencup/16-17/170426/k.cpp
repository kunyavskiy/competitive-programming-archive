#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

typedef long long ll;

const int N = 2e5;
const ll INF = 1e18;

struct Edge {
	int to, w;
};

int n, root, color[N];
vector<Edge> c[N];

void read( int cc ) {
	int k;
	scanf("%d", &k);
	while (k--) {
		int x;
		scanf("%d", &x), x--;
		root = x, color[x] = cc;
	}
}

ll f[N][3];

void dfs( int v, int p ) {
	f[v][0] = color[v] != 0 ? INF : 0;
	f[v][1] = color[v] == 2 ? INF : 0;
	f[v][2] = color[v] == 1 ? INF : 0;
	int x;
	for (auto e : c[v])
		if ((x = e.to) != p) {
			dfs(x, v);
			ll mi = *min_element(f[x], f[x] + 3);
			forn(t, 3)
				f[v][t] += min(min(f[x][0], f[x][t]), mi + e.w);
		}
}

int main() {
	scanf("%d", &n);
	forn(i, n - 1) {
		int a, b, w;
		scanf("%d%d%d", &a, &b, &w), a--, b--;
		c[a].push_back({b, w});
		c[b].push_back({a, w});
	}
	read(1);
	read(2);
	dfs(root, -1);
	printf("%lld\n", f[root][color[root]]);
}
