#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int X = 1e6, N = 403;

int x, n, ans[N], ma[X + N];
string s;

void relax( int &a, int b ) {
	a = max(a, b);
}

int main() {
	cin >> x >> s;
	int n = s.size();
	double opt = 2;
	int len = 0, a = 0, b = 0;
	forn(i, n) {
		(s[i] == 'Y' ? a : b)++;
		// printf("%d: %f\n", i, 1. * a / (a + b));
		double tmp = 1. * a / (a + b);
		if (tmp < opt)
			opt = tmp, len = i + 1;
	}
	// printf("len  =%d\n", len);
	if (x >= X) {
		int cnt = (x - X) / len + 1;
		forn(i, len)
			ans[i] += cnt;
		x -= cnt * len; 
	}
	// forn(i, n)
	// 	printf("%d%c" ,ans[i], " \n"[i == n - 1]);
	forn(i, X) {
		int b = 0;
		forn(j, n) {
			b += (s[j] == 'N');
			relax(ma[i + j + 1], ma[i] + b);
		}
	}
	while (x > 0) {
		// printf("x = %d : f = %d : ", x, ma[x]);
		int b = 0;
		forn(j, n) {
			b += (s[j] == 'N');
			if (ma[x] == ma[x - j - 1] + b) {
				j++;
				// printf("add first %d\n", j);
				forn(pos, j) ans[pos]++;
				x -= j;
				break;
			}
		}
	}
	int output = 0;
	forn(i, n)
		if (s[i] == 'Y')
			output += ans[i];
	printf("%d\n", output);
	forn(i, n)
		printf("%d%c" ,ans[i], " \n"[i == n - 1]);
}
