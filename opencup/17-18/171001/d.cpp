#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;
typedef pair<int, int> pii;

int main() {
	int n, m, k, T;
	scanf("%d%d%d%d", &n, &m, &k, &T);
	vector<int> value(n), good(T);
	vector<pii> events[T];
	forn(i, n) 
		scanf("%d", &value[i]);
	forn(_, k) {
		int i, q, t;
		scanf("%d%d%d", &i, &q, &t), i--, q--, t--;
		events[t].push_back({i, q});
		if (q == m - 1)
			good[t] = 1;
	}
	double p[m][T + 1];
	for (int t = 1; t <= T; t++)
		forn(q, m - 1) 
			scanf("%lf", &p[q][t]);
	forn(q, m - 1) {
		auto &a = p[q];
		partial_sum(a + 1, a + T + 1, a + 1);
	}
	
	int rt = 0;
	double res = 0;
	int l[n][m];
	memset(l, -1, sizeof(l));
	forn(t, T) {
		for (auto e : events[t])
			l[e.first][e.second] = t;
		if (good[t]) {
			double tmp = 0;
			// printf("----------------> t = %d\n", t);
			forn(i, n) 
				if (l[i][m - 1] != -1) {
					double pr = 1;
					forn(q, m - 1) 
						if (l[i][q] != -1) {
							// printf("i = %d, q = %d : %g = %g - %g [%d..%d]\n", i, q, p[q][t + 1] - p[q][l[i][q]], p[q][t + 1], p[q][l[i][q]],
							// 	l[i][q], t);
							pr *= 1 - (p[q][t] - p[q][l[i][q]]);
						}
					// printf("i = %d : pr = %g, value = %d\n", i, pr, value[i]);
					tmp += pr * value[i];
				}
			// printf("t = %d : %g\n", t, tmp);
			if (tmp > res)
				res = tmp, rt = t;
		}
	}
	printf("%.15f %d\n", res, rt + 1);
}
