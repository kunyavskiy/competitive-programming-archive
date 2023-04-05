#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int N = 2e5, MAX_K = 19, INF = 1e9;

int n, l[MAX_K][N], r[MAX_K][N], sl[N], sr[N], tl[N], tr[N];

int get_min( int *a, int l, int r ) {
	l = max(l, 0);
	r = min(r, n - 1);
	if (l > r) return INF;
	// printf("min[%d..%d]", l, r);
	return *min_element(a + l, a + r + 1);
}

int get_max( int *a, int l, int r ) {
	l = max(l, 0);
	r = min(r, n - 1);
	if (l > r) return -INF;
	// printf("max[%d..%d]", l, r);
	return *max_element(a + l, a + r + 1);
}

void join( int *l1, int *r1, int *l2, int *r2, int *l3, int *r3 ) {
	// printf("join[%d]: ", n);
	forn(i, n) {
		l3[i] = get_min(l2, l1[i], r1[i]);
		r3[i] = get_max(r2, l1[i], r1[i]);
	}
	// puts("ok");
}

bool check( int *l, int *r ) {
	forn(i, n) {
		int L = get_max(l, r[i] + 1, n - 1);
		int R = get_min(r, 0, l[i] - 1);
		// printf("n=%d check says for %d [%d..%d] : L=%d R=%d\n", n, i, l[i], r[i], L, R);
		if (L > i || R < i)
			return 1;
	}
	return 0;
}

int main() {
	scanf("%d", &n);
	forn(i, n) {
		int s;
		scanf("%d", &s);
		l[0][i] = i - s;
		r[0][i] = i + s;
		// printf("%d: [%d..%d]\n", i, l[0][i], r[0][i]);
	}
	int K = 0;
	while ((1 << (K + 1)) < n)
		K++;

	forn(k, K) {
		join(l[k], r[k], l[k], r[k], l[k + 1], r[k + 1]);
		// printf("---> %d\n", k + 1);
		// forn(i, n)
		// 	printf("%d: [%d..%d]\n", i, l[k + 1][i], r[k + 1][i]);
	}
	// puts(".");
	forn(i, n)
		sl[i] = sr[i] = i;

	int ans = 0;
	for (int k = K; k >= 0; k--) {
		join(sl, sr, l[k], r[k], tl, tr);
		// printf("---> for k = %d\n", k);
		// forn(i, n)
		// 	printf("%d: [%d..%d]\n", i, tl[i], tr[i]);
		if (check(tl, tr)) {
			// printf("k=%d : ok\n", k);
			ans += 1 << k;
			forn(i, n)
				sl[i] = tl[i], sr[i] = tr[i];
		}
	}
	printf("%d\n", ans + 1);
}
