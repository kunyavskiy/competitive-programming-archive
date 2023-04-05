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

	dbl x[n], res = 0;
	dbl res2 = 0;

	// returns a^x - 1 (x is 0+eps)
	auto Pow1 = [&]( dbl a, dbl x ) {
		dbl t = logl(a);
		dbl res2 = 0, add = 1;
		for (int k = 1; k <= 20; k++)
			add *= t * x / k, res2 += add;
		return res2;
	};
	// returns (1+a)^x (a is 0+eps)
	auto Pow2 = [&]( dbl a, dbl x ) {
	};

	forn(i, n) {
		x[i] = powl(a[i], -1.0L / (n - 1));
		res += x[i];
		res2 += Pow1(a[i], -1.0L / (n - 1));
	}

	dbl sum1 = 0, sum2 = 0;
	forn(i, n) {	
		dbl q = (n - 1) * x[i] / res;
		sum1 += a[i] - powl(a[i], -1.0L / (n-1)) * powl((res) / (n - 1), -n);
		sum2 += a[i] - (1 + Pow1(a[i], -1.0L / (n-1))) * powl(1 + (1 + res2) / (n - 1), -n);
	}
	if (n < 10)
		printf("%.15Lf\n", sum1 / n);
	else
		printf("%.15Lf\n", sum2 / n);
}
