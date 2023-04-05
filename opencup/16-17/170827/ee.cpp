#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int N = 5003;

int n, a[N];

typedef long double dbl;

int main() {
	scanf("%d", &n);
	forn(i, n) 
		scanf("%d", &a[i]);
	sort(a, a + n);
	if (n == 1) {
		printf("%d\n", a[0]);
		return 0;
	}
	dbl opt = 0;

	// dbl l = -1e9, r = 1e9;
	// forn(_, 100) {
	// 	dbl lambda = (l + r) / 2;
	// 	dbl sum = 0;
	// 	forn(i, n)
	// 		sum += expl((lambda - logl(a[i]) - logl(n)) / (n - 1));
	// 	(sum > n - 1 ? r : l) = lambda;
	// }

	// dbl sum = 0, lambda = (l + r) / 2;
	dbl x[n], res = 0;
	forn(i, n)
		x[i] = powl(a[i], -1.0L / (n - 1)), res += x[i];

	for (int len = n; len >= 1; len--) {
		dbl sum = 0;
		bool bad = 0;
		for (int i = n - len; i < n; i++) {
			// dbl q = expl((lambda - logl(a[i]) - logl(n)) / (n - 1));
			dbl q = (len - 1) * x[i] / res;
			// pri/ntf("%.5Lf\n", q);
			bad |= q > 1;
			// printf("%d : a = %d, p = %.3f, q = %.3f\n", i, a[i], 1 - q, q);
			sum += a[i] * (1 - powl(q, 1. * n));
		}
		res -= x[n - len];
		// printf("len = %d of %d, sum = %.9Lf\n", len, n, sum_q);
		if (!bad) {
			// printf("len = %d\n", len);
			printf("%.15f\n", (double)sum / n);
			return 0;
		}
	}
	assert(0);
}
