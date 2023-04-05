#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

double dist( double x, double y ) {
	return sqrt(x * x + y * y);
}

const int N = 5e4;
int n, x[N], y[N];

int main() {
	ll need;
	scanf("%d%lld", &n, &need);
	forn(i, n) scanf("%d%d", &x[i], &y[i]);

	ll S = 0;
	double p = 0;
	forn(i, n) {
		int j = (i + 1) % n;
		S += (ll)x[i] * y[j] - (ll)x[j] * y[i];
		p += dist(x[i] - x[j], y[i] - y[j]);
	}
	S = abs(S);
	// cout << S << " " << need << endl;
	if (2 * need <= S)
		puts("0");
	else {
		double A = M_PI;
		double B = p;
		double C = 0.5 * (S - 2 * need); // < 0
		printf("%.15f\n", 2 * C / (-B - sqrt(B * B - 4 * A * C)));
		// printf("%.15f\n", (-B + sqrt(B * B - 4 * A * C)) / (2 * A));
	}
}