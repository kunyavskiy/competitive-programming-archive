#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int N = 3e5 + 10, INF = 1e9;

typedef pair<int, int> pii;

struct Data {
	int f1, s1;
	int f2, s2;
};
Data comb( Data a, Data b ) {
	pii p[] = {{a.f1, a.s1}, {a.f2, a.s2}, {b.f1, b.s1}, {b.f2, b.s2}};
	sort(p, p + 4, []( pii a, pii b) {
		return a.first > b.first || (a.first == b.first && a.second < b.second);
	});
	int i = 0;
	while (i < 3 && p[i].first == p[0].first)
		i++;
	// forn(j, 4) printf("(%d,%d) ", p[i].first, p[i].second);
	// puts("");
	return {p[0].first, p[0].second, p[i].first, p[i].second};
}

int n, l, r, a[N], s[N], f[N];
Data t[2 * N], inf = {-INF, 0, -INF, 0};

void change( int i ) {
	// printf("change i=%d, f=%d, s=%d [n=%d]\n", i, f[i], s[i], n);
	t[i + n] = {f[i], s[i], f[i], s[i]};
	for (i = (i + n) / 2; i >= 1; i /= 2) {
		t[i] = comb(t[i * 2], t[i * 2 + 1]);
		// printf("%d <--- %d %d %d %d\n", i, t[i].f1, t[i].s1, t[i].f2, t[i].s2);
	}
}

Data get( int l, int r ) {
	Data res = inf;
	for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
		// printf("l=%d r=%d\n", l, r);
		if ((l & 1) == 1) res = comb(res, t[l++]);
		if ((r & 1) == 0) res = comb(res, t[r--]);
	}
	return res;
}

int calc( int i, int f, int sl ) {
	int sum = s[i] - sl;
	return f + (sum > 0 ? 1 : (sum < 0 ? -1 : 0));
}

int main() {
	scanf("%d%d%d", &n, &l, &r);
	forn(i, n)
		scanf("%d", &a[i]), s[i + 1] = s[i] + a[i];
	forn(i, 2 * N)
		t[i] = inf;
	forn(i, l)
		f[i] = (!i ? 0 : -INF), change(i);
	for (int i = l; i <= n; i++) {
		// puts("tree");
		// forn(i, 2 * n)
		// 	printf("%d <--- %d %d %d %d\n", i, t[i].f1, t[i].s1, t[i].f2, t[i].s2);
		int a = max(0, i - r), b = i - l;
		Data d = get(a, b);
		f[i] = max(calc(i, d.f1, d.s1), calc(i, d.f2, d.s2));
		// printf("%d: f=%d <%d,%d> and <%d,%d> [%d..%d]\n", i, f[i], d.f1, d.s1, d.f2, d.s2, a, b);
		change(i);
	}
	if (f[n] <= -INF / 2)
		puts("Impossible");
	else
		printf("%d\n", f[n]);
}