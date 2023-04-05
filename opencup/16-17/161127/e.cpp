#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;
typedef int INT;
#define int ll
int k, cnt = 0;
void check( int a, int b, int c ) {
	if (a * a + b * b + c * c == k * (a * b + b * c + c * a) + 1 && 1 <= c && c < b)
		printf("%lld: %lld %lld %lld\n", ++cnt, a, b, c);
}

INT main() {
	cin >> k;
	set<int> v[k];
	forn(a, k) 
		forn(b, k)
			forn(c, k)
				if ((a * a + b * b + c * c) % k == 1)
					v[a].insert(b);
	int sum = 0;
	forn(a, k) 
		sum += v[a].size();
	printf("k = %lld, average = %.3f\n", k, 1. * sum / k);

	for (int a = k * k;; a++) {
		int sa = pow(a, 2. / 3);
		for (int b0 : v[a % k])
			for (int b = b0; b <= sa && b < a; b += k) {
				// a^2 + b^2 + c^2 = k(ab + bc + ac) + 1
				// c^2 - k(a+b)c + (a^2 + b^2 - k * ab - 1)
				int B = k * (a + b);
				int C = a * a + b * b - k * a * b  - 1;
				int D = floor(sqrt(fabs(B * B - 4 * C)) + 0.5);
				check(a, b, (B - D) / 2);
				check(a, b, (B + D) / 2);
			}
	}
}
