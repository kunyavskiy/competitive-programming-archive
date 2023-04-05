#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int M = 7, N = 40000;

int n, f[M][M];
vector<int> x[M][M];

void solve( int i, int j ) {
	if (i == 6 && j == 6)
		return;
	if (!x[i][j].size())
		return;
	vector<int> &v = x[i][j];
	// printf("--------------------> solve %d %d [%d]\n", i, j, (int)v.size());
	// if ((int)v.size() > f[i][j]) printf("failed %d %d : %d > %d\n", i, j, (int)v.size() , f[i][j]);
	assert((int)v.size() <= f[i][j]);
	if (((i == 5 && j == 6) || (i == 6 && j == 5)) && v.size() == 2U) {
		char c = (i < 6 ? 'D' : 'R');
		if (v[0] < v[1]) {
			printf("%d %d %c 1\n", i, j, c);
			printf("%d %d %c 1\n", i, j, c);
			x[6][6].push_back(v[1]);
			x[6][6].push_back(v[0]);
		} else {
			printf("%d %d %c 2\n", i, j, c);
			x[6][6].push_back(v[0]);
			x[6][6].push_back(v[1]);
		}
		v.clear();
		return;
	}
	int mi = *min_element(v.begin(), v.end());
	int ma = *max_element(v.begin(), v.end());
	vector<int> pi(ma - mi + 1, -1);
	vector<int> pj(ma - mi + 1, -1);
	int pos = 0;
	for (int i1 = 6; i1 >= i; i1--)
		for (int j1 = 6; j1 >= j; j1--)
			if (i1 != i || j1 != j) {
				forn(t, f[i1][j1])  {
					if (ma - pos < mi) break;
					pi[pos] = i1, pj[pos++] = j1;
				}
			}
	// forn(i, ma - mi + 1) printf("%d: %d %d\n", i, pi[i], pj[i]);
	while (v.size()) {
		int a = v.back();
		v.pop_back();
		int i1 = i, j1 = j, z = ma - a;
		assert(pi[z] <= 6);
		assert(pj[z] <= 6);
		assert(pi[z] != -1);
		// printf("make %d from %d %d to %d %d\n", a, i, j, pi[z], pj[z]);
		while (i1 < pi[z]) printf("%d %d D 1\n", i1, j1), i1++;
		while (j1 < pj[z]) printf("%d %d R 1\n", i1, j1), j1++;
		x[i1][j1].push_back(a);
	}
	for (int i1 = 6; i1 >= i; i1--)
		for (int j1 = 6; j1 >= j; j1--)
			if (i1 != i || j1 != j) 
				solve(i1, j1);
}

int main() {
	scanf("%d", &n);
	x[1][1].resize(n);
	forn(i, n) scanf("%d", &x[1][1][i]);
	f[6][6] = 1;
	f[6][5] = 2;
	f[5][6] = 2;
	for (int x = 6; x >= 1; x--)
		for (int y = 6; y >= 1; y--) {
			if (f[x][y]) continue;
			int res = 0;
			for (int dx = x; dx <= 6; dx++)
				for (int dy = y; dy <= 6; dy++)
					if (dx != x || dy != y)
						res += f[dx][dy];
			f[x][y] = res;
		}
	solve(1, 1);
	// for (int z : x[6][6]) printf("%d ", z);
	// for (int x = 1; x < M; x++) {
	// 	for (int y = 1; y < M; y++)
	// 		printf("%6d ", f[x][y]);
	// 	puts("");
	// }
}