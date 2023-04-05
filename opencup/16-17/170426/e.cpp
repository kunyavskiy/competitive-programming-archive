#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int N = 2e5, MAX_K = 19, INF = 1e9;

int n, l[MAX_K][N], r[MAX_K][N], sl[N], sr[N], cl[N], cr[N];
int tl[2 * N], tr[2 * N];

void build_min( int *a, int *t ) {
	forn(i, n) t[i + n] = a[i];
	for (int i = n - 1; i > 0; i--) t[i] = min(t[2 * i], t[2 * i + 1]);
}
int tree_min( int *a, int l, int r ) {
	int res = INF;
	for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
		if ((l & 1) == 1) res = min(res, a[l++]);
		if ((r & 1) == 0) res = min(res, a[r--]);
	}
	return res;
}
void build_max( int *a, int *t ) {
	forn(i, n) t[i + n] = a[i];
	for (int i = n - 1; i > 0; i--) t[i] = max(t[2 * i], t[2 * i + 1]);
}
int tree_max( int *a, int l, int r ) {
	int res = -INF;
	for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
		if ((l & 1) == 1) res = max(res, a[l++]);
		if ((r & 1) == 0) res = max(res, a[r--]);
	}
	return res;
}

int get_min( int *a, int l, int r ) {
	l = max(l, 0);
	r = min(r, n - 1);
	if (l > r) return INF;
	// printf("min[%d..%d]", l, r);
	// return *min_element(a + l, a + r + 1);
	return tree_min(a, l, r);
}

int get_max( int *a, int l, int r ) {
	l = max(l, 0);
	r = min(r, n - 1);
	if (l > r) return -INF;
	// printf("max[%d..%d]", l, r);
	// return *max_element(a + l, a + r + 1);
	return tree_max(a, l, r);
}

void join( int *l1, int *r1, int *l2, int *r2, int *l3, int *r3 ) {
	// printf("join[%d]: ", n);
	build_min(l2, tl);
	build_max(r2, tr);
	forn(i, n) {
		l3[i] = get_min(tl, l1[i], r1[i]);
		r3[i] = get_max(tr, l1[i], r1[i]);
	}
	// puts("ok");
}

bool check( int *l, int *r ) {
	build_max(l, tl);
	build_min(r, tr);
	forn(i, n) {
		int L = get_max(tl, r[i] + 1, n - 1);
		int R = get_min(tr, 0, l[i] - 1);
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
		join(sl, sr, l[k], r[k], cl, cr);
		// printf("---> for k = %d\n", k);
		// forn(i, n)
		// 	printf("%d: [%d..%d]\n", i, tl[i], tr[i]);
		if (check(cl, cr)) {
			// printf("k=%d : ok\n", k);
			ans += 1 << k;
			forn(i, n)
				sl[i] = cl[i], sr[i] = cr[i];
		}
	}
	printf("%d\n", ans + 1);
}
