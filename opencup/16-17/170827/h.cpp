#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int M = 1e6 + 100, K = 3000;

typedef long long ll;
int pn, p[M / 10], is[M];

int main() {
	for (int i = 2; i < M; i++)
		if (!is[i]) {
			p[pn++] = i;
			for (int j = i + i; j < M; j += i)
				is[j] = 1;
		}
	for (int i = 1; i < M; i++)
		is[i] = !is[i] + is[i - 1];
	auto get = [&]( int l, int r ) {
		return is[r] - (l ? is[l - 1] : 0);
	};

	int q, a, b;
	scanf("%d", &q);
	while (q--) {
		scanf("%d%d", &a, &b);
		int i;
		ll ans = 0;
		for (i = 0; p[i] < K; i++) {
			ll n = b / p[i] - (a - 1) / p[i];
			ans += n * (n - 1) / 2;
		}
		int l = K, cnt = 0;
		for (cnt = 0;; cnt++) {
			int x = b / l, y = (a - 1) / l;
			// printf("x = %d, y = %d\n", x, y);
			if (!x) break;
			ll n = x - y;
			ll add = n * (n - 1) / 2;
			auto f = [&]( int b, int x ) {
				// printf("b = %d, x = %d --> %d : %d\n", b, x, b / x + 1, b / (b / x + 1));
				return b / x + 1;
			};
			int r1 = f(b, x);
			int r2 = y == 0 ? INT_MAX : f(a - 1, y);
			int r = min(r1, r2);
			// printf("l = %d --> r = %d\n", l, r);
			ans += add * get(l, r - 1);
			l = r;
		}
		// fprintf(stderr, "cnt = %d\n", cnt);
		printf("%lld\n", ans);
		fflush(stdout);
	}
}