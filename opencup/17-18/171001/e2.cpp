// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a).size()

typedef long long ll;

struct Point {
  int x, y, w;
};

bool xless(Point a, Point b) { return a.x < b.x; }

bool yless(Point a, Point b) { return a.y < b.y; }

typedef pair<ll, int> T;

struct Tree {
  vector<vector<int>> y;
  vector<vector<T>> f;
  vector<Point> p;

  void build(const vector<Point> &_p) {
    p = _p;
    int n = sz(p);
    sort(all(p), xless);
    y.resize(2 * n);
    forn(i, n)y[n + i].resize(1), y[n + i][0] = p[i].y;
    for (int i = n - 1; i > 0; i--) {
      y[i].resize(sz(y[2 * i]) + sz(y[2 * i + 1]));
      merge(all(y[2 * i]), all(y[2 * i + 1]), y[i].begin());
    }
    f.resize(2 * n);
    forn(i, 2 * n)f[i].assign(2 * y[i].size(), T(0, -1));
  }

  T innerGet(int i, int ry) {
    T res(LONG_LONG_MIN, -1);
    int n = y[i].size(), l = n, r = n + (upper_bound(all(y[i]), ry) - y[i].begin());
    for (; l < r; l >>= 1, r >>= 1) {
      if (l & 1) res = max(res, f[i][l++]);
      if (r & 1) res = max(res, f[i][--r]);
    }
    return res;
  }

  T getMax(int rx, int ry) {
    T res(LONG_LONG_MIN, -1);
    // printf("getMax %d %d\n", rx, ry);
    // for (auto a : p) printf("x=%d y=%d w=%d\n", a.x, a.y, a.w);
    int n = p.size(), l = n, r = n + (upper_bound(all(p), Point {rx, 0, 0}, xless) - p.begin());
    // printf("getMax: r=%d\n", r);
    for (; l < r; l >>= 1, r >>= 1) {
      if (l & 1) res = max(res, innerGet(l++, ry));
      if (r & 1) res = max(res, innerGet(--r, ry));
    }
    return res;
  }

  void innerChangeValue(int i, int ry, T value) {
    // printf("innerChangeValue: i=%d\n", i);
    int n = y[i].size(), j = lower_bound(all(y[i]), ry) - y[i].begin();
    // printf("innerChangeValue: i=%d j=%d (size=%ld, %ld)\n", i, j, y[i].size(), f[i].size());
    f[i][j += n] = value;
    for (j /= 2; j > 0; j /= 2)
      f[i][j] = max(f[i][2 * j], f[i][2 * j + 1]);

  }

  void changeValue(int rx, int ry, T value) {
    int i = lower_bound(all(p), Point {rx, 0, 0}, xless) - p.begin();
    // printf("change: i=%d\n", i);
    for (i += p.size(); i > 0; i /= 2)
      innerChangeValue(i, ry, value);
  }
} tree;

#define FAST 1

vector<int> solve(vector<Point> p) {
  int n = sz(p), ri = 0;
  vector<T> f(n);
  // puts("!");
#if FAST
  tree.build(p);
#endif
  // puts("!");
  forn(i, n) {
    // printf("i=%d\n", i);
#if FAST
    f[i] = tree.getMax(p[i].x, p[i].y);
#endif
                          // printf("%d: %lld %d\n", i, f[i].first, f[i].second);
#if not FAST
    f[i] = {LONG_LONG_MIN, -1};
    for (int j = 0; j < i; j++)
      if (p[j].x <= p[i].x && p[j].y <= p[i].y)
        f[i] = max(f[i], T {f[j].first, j});
#endif
    f[i].first += p[i].w;
#if FAST
    tree.changeValue(p[i].x, p[i].y, {f[i].first, i});
#endif
    if (f[i].second > f[ri].second)
      ri = i;
  }
  // forn(i, n)
  //   printf("%d: %lld %d\n", i, f[i].first, f[i].second);

  ri = n - 1;

  vector<int> res;
  for (; ri != -1; ri = f[ri].second)
    res.push_back(ri);
  reverse(all(res));
  return res;
}

int main() {
  freopen("input.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);

  int m, n;
  scanf("%d%d", &m, &n);
  vector<int> p(n + 1, -1);
  vector<int> s(n + 1);
  vector<int> ps(n + 1);
  for (int i = 0; i < m; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    x--;
    if (x >= 0) {
      if (p[x] == -1) {
        p[x] = i;
      }
      s[x]++;
    }
  }
  p[n] = m;
  for (int i = 0; i < n; i++) {
    ps[i + 1] = ps[i] + s[i];
  }
  vector<int> id;
  vector<Point> pp;
  for (int i = 0; i <= n; i++) {
    if (p[i] - ps[i] >= 0) {
      pp.push_back({p[i], p[i] - ps[i], s[i]});
      id.push_back(i);
    }
  }

//  for (int i = 0; i < sz(pp); i++) {
//    cout << pp[i].x << " " << pp[i].y << " " << pp[i].w << endl;
//  }

  vector<int> res = solve(pp);
  vector<bool> stay(n);
  for (int i = 0; i < ((int) res.size()) - 1; i++) {
    stay[id[res[i]]] = true;
  }

  vector<int> to(m, -1);
  int cur = 0;
  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (stay[i]) {
      cur = p[i];
    } else {
      ans += s[i];
    }
    for (int j = 0; j < s[i]; j++) {
      to[p[i] + j] = cur + j;
    }
    cur += s[i];
  }

  vector<vector<int>> q;
  vector<bool> done(m);
  for (int i = 0; i < m; i++) {
    if (to[i] >= 0 && to[i] != i && !done[i]) {
      vector<int> pt;
      pt.push_back(i);
      done[i] = true;
      int j = to[i];
      while (to[j] >= 0 && !done[j]) {
        done[j] = true;
        pt.push_back(j);
        j = to[j];
      }
      pt.push_back(j);
      q.push_back(pt);
    }
  }

  cout << ans << " " << q.size() << endl;
  for (auto pt : q) {
    cout << pt.size();
    for (auto x : pt) {
      cout << " " << (x + 1);
    }
    cout << endl;
  }
}
