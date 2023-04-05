#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int K = 256, N = 40000;

int n, a[N], px[N], py[N], mx, my;
vector<int> x[K], y[K];
vector<int> s[6][6];

int main() {
	scanf("%d", &n);
	forn(i, K) {
		x[i].push_back(0);
		y[i].push_back(n + 1);
	}
	forn(i, n) {
		scanf("%d", &a[i]);
		forn(j, K)
			if (x[j].back() < a[i]) {
				x[j].push_back(a[i]);
				mx = max(mx, j);
				// printf("%d: x=%d\n", i, j);
				px[i] = j;
				break;
			}
		forn(j, K)
			if (y[j].back() > a[i]) {
				y[j].push_back(a[i]);
				// printf("%d: y=%d\n", i, j);
				my = max(my, j);
				py[i] = j;
				break;
			}
	}
	if (mx < my) {
		forn(i, mx + 1) {
			for (int z : x[i]) if (z != 0 && z != n + 1)
				printf("%d ", z);
			puts("");
		}
	} else {
		forn(i, my + 1) {
			for (int z : y[i]) if (z != 0 && z != n + 1)
				printf("%d ", z);
			puts("");
		}
	}
}
