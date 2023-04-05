// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

vector<vector<int>> field;
map<vector<vector<int>>, int> h;

int n, m, k;

void flip( int i, int j ) {
	forn(di, k)
		forn(dj, k)
			field[i + di][j + dj] ^= 1;

}
int go( int dep = 0 ) {
	if (h.count(field))
		return h[field];
	int &res = h[field];
	forn(i, n - k + 1)
		forn(j, m - k + 1) {
			bool can = 1;
			forn(di, k)
				forn(dj, k)
					if (field[i + di][j + dj])
						can = 0, di = dj = k;
			if (can) {
				flip(i, j);
				if (go(dep + 1) == 0) {
					res++;
					if (!dep)
						printf("di = %d, dj = %d\n", i, j);
				}
				flip(i, j);
			}
		}
	return res; 
}

ll solve( int n, int m, int k ) {
	if (n < m) swap(n, m);
	if (k == 1) {
		if (n * m % 2 == 0)
			return 0;
		return n * m;
	}
	vector<int> x, y;
	auto gen = [&]( vector<int> &x, int n ) {
		x.push_back(0);
		x.push_back(k);
		x.push_back(2 * k);
		x.push_back(n - k + 1);
		x.push_back(n - 2 * k + 1);
		x.push_back(n - 3 * k + 1);
		sort(x.begin(), x.end());
		x.resize(unique(x.begin(), x.end()) - x.begin());
	};
	gen(x, n);
	gen(y, m);

	ll ans = 0;
	// for (int a : x) printf("%d ", a); puts("");
	// for (int a : y) printf("%d ", a); puts("");
	forn(i, x.size() - 1)
		forn(j, y.size() - 1) {
			int lx = x[i], rx = n - x[i] - k;
			int ly = y[j], ry = m - y[j] - k;
			if (lx < 0 || rx < 0 || ly < 0 || ry < 0) continue;
			// printf("[%d,%d] [%d,%d] : ", lx, rx, ly, ry);
			
			ll moves = (ll)(x[i + 1] - x[i]) * (y[j + 1] - y[j]);
			lx /= k, rx /= k, ly /= k, ry /= k;
			if (lx + rx > ly + ry)
				swap(lx, ly), swap(rx, ry);
			if (lx > rx)
				swap(lx, rx);
			if (ly > ry)
				swap(ly, ry);
			bool good = 0;
			if (lx + rx == 0)
				good = (ly == ry);
			else if (lx + rx == 1)
				good = (ly == 0 && ry == 2 && !(n + m >= 6 * k - 1)); // ???
			else if (rx == 1 && ry == 1)
				good = 1; // 1 1 1 1
			else if (rx == 1 || ry == 1)
				good = 0; // 0 2 1 1 
			else
				good = 0; // 0 2 0 2
			// printf("x = [%d, %d], y = [%d, %d], moves = %lld, good = %d\n", lx, rx, ly, ry, moves, good);
			if (good)
				ans += moves;
		}
	return ans;
}

void check() {
	printf("check n=%d m=%d k=%d :", n, m, k);
	field = vector<vector<int>>(n, vector<int>(m));
	//flip(0, 1);
	// printf("brute force says: \n");
	// fflush(stdout);
	h.clear();
	int ans = go();
	int out = solve(n, m, k);
	printf("ans=%d out=%d\n", ans, out);
	fflush(stdout);
	assert(ans == out);
}

int main() {
	// for (k = 2;; k++)
	// 	for (n = k; n <= 3 * k; n++)
	// 		for (m = k; m <= 3 * k; m++)
	// 			if (n >= m)
	// 				check();
	cin >> n >> m >> k;
	// n  =m = k = 3;
	// field = vector<vector<int>>(n, vector<int>(m));
	// printf("%d\n", go());
	printf("%lld\n", solve(n, m, k));
}
