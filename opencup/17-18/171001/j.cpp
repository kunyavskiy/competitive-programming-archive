#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

void solve() {
	int n;
	double l;
	scanf("%d%lf", &n, &l);
	l *= 1e3;
	struct Item {
		int a, t;
		bool operator < ( Item x ) const {
			return a > x.a;
		}
	} p[n];
	forn(i, n) {
		scanf("%d%d", &p[i].a, &p[i].t);
	}
	double v = 0, t = 0, s = 0;
	sort(p, p + n);
	forn(i, n) {
		double dt = 1e-6 * p[i].t;
		// printf("%d %g\n", p[i].a, dt);
		double s1 = s + v * dt + 0.5 * p[i].a * dt * dt;
		// printf("%d %g %g\n", p[i].a, dt, s1);
		if (s1 > l) {
			double A = 0.5 * p[i].a, B = v, C = s - l;
			double x = (-B + sqrt(B * B - 4 * A * C)) / (2 * A);
			printf("%.15f\n", t + x);
			return;
		}
		s = s1, v += p[i].a * dt, t += dt;
	}
	printf("%.15f\n", t + (l - s) / v);

}

int main() {
	int tn;
	scanf("%d", &tn);
	while (tn--)
		solve();
}
