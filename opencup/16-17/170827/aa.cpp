#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int P = 1e9 + 7;

typedef unsigned long long ull;

const int D = 203, N = 5003;

int d, n, m, c[D][N];
vector<int> ids[D][N];
ull deg[D], sum[N];
unordered_map<ull, int> cnt(N);

ull res = 0;
int change( ull x, int add ) {
	int &value = cnt[x];
	res -= value * value;
	value += add;
	res += value * value;
	if (!value)
		cnt.erase(x);
}

int main() {
	scanf("%d%d%d", &d, &n, &m);
	deg[0] = 1;
	forn(i, d)
		deg[i + 1] = deg[i] * P;
	forn(j, d) 
		forn(i, n) {
			c[j][i] = i;
			ids[j][i].push_back(i);
			sum[i] += c[j][i] * deg[j];
		}

	forn(i, n)
		change(sum[i], 1);
	while (m--) {
		int a, b, k;
		scanf("%d%d%d", &a, &b, &k), a--, b--, k--;
		if (c[k][a] != c[k][b]) {
			if (ids[k][c[k][a]].size() < ids[k][c[k][b]].size())
				swap(a, b);
			for (int v : ids[k][c[k][b]]) {
				change(sum[v], -1);
				sum[v] -= c[k][v] * deg[k];
				c[k][v] = c[k][a];
				sum[v] += c[k][v] * deg[k];
				change(sum[v], 1);
				ids[k][c[k][a]].push_back(v);
			}
		}
		printf("%llu\n", res);
	}
}
