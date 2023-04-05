#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

ll solve( ll a, ll b ) {
	ll g = __gcd(a - 1, b - 1);
	if (g == 1) {
		return (a * b) / 2 - 1;
	}
	ll a1 = (a - 1) / g + 1;
	ll b1 = (b - 1) / g + 1;
	return a1 * b1 / 2 + (g - 1) * (a1 * b1 - a1 - b1 + 1) - 1;
}

ll stupid_solve( ll a, ll b ) {
	vector<vector<bool>> u(a, vector<bool>(b));
	int x = 0, y = 0, dx = 1, dy = 1;
	forn(i, a * b) {
		u[x][y] = 1;
		x += dx, y += dy;
		if (x == 0 || x == a - 1) dx *= -1;
		if (y == 0 || y == b - 1) dy *= -1;
	}
	int cnt = 0;
	forn(i, a) forn(j, b) cnt += u[i][j];
	// forn(i, a) {
	// 	forn(j, b) printf("%c", u[i][j] ? '*' : '.');
	// 	puts("");
	// }
	return cnt;
}

int main() {
	// stupid_solve(7,10);
	// return 0;
	long long a, b;
	cni >> a >> b;
	for (int a = 2; a <= 20; a++) {
		for (int b = 2; b < a; b++) {
			ll f = solve(a, b) + 1, g = stupid_solve(a, b);
			if (f != g) {
				printf("a=%d,b=%d: %d,%d,%d (%lld,%lld,diff=%lld)\n", a, b, a - 1, b - 1, __gcd(a - 1, b - 1), f, g, abs(f - g));
				// printf("(%d,%d) ", a, b);
			}
		}
		// puts("");
	}

}