// #include <bits/stdc++.h>

// using namespace std; 

// #define forn(i, n) for (int i = 0; i < (int)(n); i++)

// typedef long long ll;

// const int N = 5003;

// int n, a[N];

// typedef long double dbl;

// dbl dbl_sum(dbl a, dbl b) {
// 	if (a < b) {
// 		swap(a, b);
// 	}
// 	return a + logl(1 + expl(b - a));
// }

// int main() {
// 	scanf("%d", &n);
// 	forn(i, n) 
// 		scanf("%d", &a[i]);
// 	if (n == 1) {
// 		printf("%d\n", a[0]);
// 		return 0;
// 	}

// 	// dbl l = -1e9, r = 1e9;
// 	// forn(_, 100) {
// 	// 	dbl lambda = (l + r) / 2;
// 	// 	dbl sum = 0;
// 	// 	forn(i, n)
// 	// 		sum += expl((lambda - logl(a[i]) - logl(n)) / (n - 1));
// 	// 	(sum > n - 1 ? r : l) = lambda;
// 	// }

// 	// dbl sum = 0, lambda = (l + r) / 2;
// 	dbl x[n], sum = 0;
// 	forn(i, n) {
// 		x[i] = -logl(a[i]) / (n - 1);
// 	}
// 	sort(x, x + n);
// 	dbl s = x[0];
// 	for (int i = 1; i < n; i++) {
// 		s = dbl_sum(s, x[i]);
// 	}
// 	dbl suma = 0;
// 	dbl qsum = logl(n - 1) - s;
// 	dbl qsumn = expl(qsum * n);
// 	//printf("qsum = %.10Lf\n", qsum);
// 	forn(i, n) {
// 		// dbl q = expl((lambda - logl(a[i]) - logl(n)) / (n - 1));
// 		// printf("%.5f [%.5Lf]\n", (double)q, x[i] / res);
// 		// printf("%d : a = %d, p = %.3f, q = %.3f\n", i, a[i], 1 - q, q);
// 		suma += a[i];
// 		sum += powl(a[i], -1.0 / (n - 1)) * qsumn;
// 	}
// 	printf("%.15f\n", (double)(suma - sum) / n);
// }


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
	if (n == 1) {
		printf("%d\n", a[0]);
		return 0;
	}

	// dbl l = -1e9, r = 1e9;
	// forn(_, 100) {
	// 	dbl lambda = (l + r) / 2;
	// 	dbl sum = 0;
	// 	forn(i, n)
	// 		sum += expl((lambda - logl(a[i]) - logl(n)) / (n - 1));
	// 	(sum > n - 1 ? r : l) = lambda;
	// }

	// dbl sum = 0, lambda = (l + r) / 2;
	dbl x[n], res = 0, sum = 0;
	forn(i, n)
		x[i] = 1. / powl(a[i], 1.0L / (n - 1)), res += x[i];
	forn(i, n) {
		// dbl q = expl((lambda - logl(a[i]) - logl(n)) / (n - 1));
		dbl q = (n - 1) * x[i] / res;
		// printf("%.5f [%.5Lf]\n", (double)q, x[i] / res);
		// printf("%d : a = %d, p = %.3f, q = %.3f\n", i, a[i], 1 - q, q);
		sum += a[i] * (1 - powl(q, 1. * n));
	}
	printf("%.15f\n", (double)sum / n);
}
