struct Point {
	int x, y, w;
};
bool xless( Point a, Point b ) { return a.x < b.x; }
bool yless( Point a, Point b ) { return a.y < b.y; }

typedef pair<ll, int> T;

struct Tree {
	vector<vector<int>> y;
	vector<vector<T>> f;
	void build( vector<Point> p ) {
		int n = sz(p);
		y.resize(2 * n);
		forn(i, n) 
			y[n + i].resize(1), y[n + i][0] = p[i].y;
		sort(p.begin(), p.end(), xless);
		for (int i = n - 1; i > 0; i--) {
			y[i].resize(sz(y[2 * i]) + sz(y[2 * i + 1]));
			merge(all(y[2 * i]), all(y[2 * i + 1]), y[i].begin());
		}
		f.resize(2 * n);
		forn(i, 2 * n) 
			f[i].assign(y[i].size(), T(0, -1));
	}
	T innerGet( int i, int ry ) {
		T res(LONG_LONG_MIN, -1);
		int n = y[i].size(), l = n, r = n + upper_bound(all(y[i]), ry) - y[i].begin();
		for (; l < r; l >>= 1, r >>= 1) {
			if (l & 1) res = max(res, f[i][l++]);
			if (r & 1) res = max(res, f[i][--r]);
		}
		return res;
	}

	T getMax( const vector<Point> &p, int rx, int ry ) {
		T res(LONG_LONG_MIN, -1);
		int n = p.size(), l = n, r = n + upper_bound(all(p), Point {rx, 0}, xless) - p.begin();
		for (; l < r; l >>= 1, r >>= 1) {
			if (l & 1) res = max(res, innerGet(l++, ry));
			if (r & 1) res = max(res, innerGet(--r, ry));
		}
		return res;
	}
	void innerChangeValue( int i, int ry, T value ) {
		int n = y[i].size(), j = lower_bound(all(y[i]), ry) - y[i].begin();
		f[i][j += n] = value;
		for (j /= 2; j > 0; j /= 2)
			f[i][j] = max(f[i][2 * j], f[i][2 * j + 1]);

	}
	void changeValue( const vector<Point> &p, int rx, int ry, T value ) {
		int i = lower_bound(all(p), Point {rx, 0}, xless) - p.begin();
		for (i += p.size(); i > 0; i /= 2)
			innerChangeValue(i, ry, value);
	}
} tree;

vector<int> solve( vector<Point> p ) {
	int n = sz(p), ri = 0;
	vector<T> f(n);
	tree.build(p);
	forn(i, n) {
		f[i] = tree.getMax(p, p[i].x, p[i].y); 
		f[i].second += p[i].w;
		tree.changeValue(p, p[i].x, p[i].y, {f[i].second, i});
		if (f[i].second > f[ri].second)
			ri = i;
	}
	vector<int> res;
	for (; ri != -1; ri = f[ri].first)
		res.push_back(ri);
	reverse(all(res));
	return res;
}

