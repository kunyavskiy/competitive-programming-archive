#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;
typedef pair<int, int> pii;

const int INF = 1e9 + 10;

struct Tree {
	int tn;
	vector<pii> t;
	Tree( int n, vector<int> &a ) : tn(n), t(2 * n) {
		forn(i, tn)
			t[tn + i] = {a[i], i};
		for (int i = tn - 1; i > 0; i--)
			t[i] = max(t[2 * i + 1], t[2 * i]);
	};
	void change( int i, pii p ) {
		t[tn + i] = max(t[tn + i], p);
		for (i = (tn + i) >> 1; i > 0; i >>= 1)
			t[i] = max(t[2 * i], t[2 * i + 1]);
	}
	pii get( int l, int r ) {
		pii res(-INF, -INF);
		for (l += tn, r += tn; l <= r; l >>= 1, r >>= 1) {
			if ((l & 1) == 1) res = max(res, t[l++]);
			if ((r & 1) == 0) res = max(res, t[r--]);
		}
		return res;
	}
	pii get( int l, int r, int i ) {
		return max(get(l, i - 1), get(i + 1, r));
	}
};

int main() {
	int n, q;
	scanf("%d%d", &n, &q);
	vector<int> x1(n), x2(n), y1(n), y2(n);
	forn(i, n) {
		int x, y;
		scanf("%d%d", &x, &y);
		x1[i] = x, x2[i] = -x;
		y1[i] = y, y2[i] = -y;
	}
	Tree x_max(n, x1), x_min(n, x2);
	Tree y_max(n, y1), y_min(n, y2);

	while (q--) {
		int l, r;
		scanf("%d%d", &l, &r), l--, r--;
		// printf("%d..%d\n", l, r);
		if (r - l <= 1) {
			puts("0");
			continue;
		}
		int res = 2e9;
		auto relax = [&]( int i ) {
			res = min(res, max(
				x_max.get(l, r, i).first + x_min.get(l, r, i).first,
				y_max.get(l, r, i).first + y_min.get(l, r, i).first
			));
		};
		relax(x_min.get(l, r).second);
		relax(x_max.get(l, r).second);
		relax(y_min.get(l, r).second);
		relax(y_max.get(l, r).second);
		printf("%d\n", res);

	}
}
