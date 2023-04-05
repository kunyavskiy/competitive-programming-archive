#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");

#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

struct segtree {
  int n;
  vector<pair<int, int>> min;
  vector<int> add;

  void build(int n, int ll, int rr) {
    if (rr == ll + 1) {
      min[n] = {ll + 1, ll};
    } else {
      int mm = (ll + rr) / 2;
      build(2 * n + 1, ll, mm);
      build(2 * n + 2, mm, rr);
      if (min[2 * n + 1] < min[2 * n + 2]) {
        min[n] = min[2 * n + 1];
      } else {
        min[n] = min[2 * n + 2];
      }
    }
//    cout << "! " << " "<< ll << "," << rr << ":" << min[n].first << "\n";
  }

  segtree(int _n) {
    n = _n;
    min.resize(4 * n);
    add.resize(4 * n);
//    cout << "!!" << n << "\n";
    build(0, 0, n);
  }
  void inc(int l, int r, int d) {
    if (r > l)
      inc(l, r, d, 0, 0, n);
  }
  void push(int n) {
    add[2 * n + 1] += add[n];
    min[2 * n + 1].first += add[n];
    add[2 * n + 2] += add[n];
    min[2 * n + 2].first += add[n];
    add[n] = 0;
  }
  void inc(int l, int r, int d, int n, int ll, int rr) {
    if (l >= rr || ll >= r) return;
    if (rr > ll + 1) push(n);
    if (ll >= l && rr <= r) {
      add[n] += d;
      min[n].first += d;
      return;
    }
    int mm = (ll + rr) / 2;
    inc(l, r, d, 2 * n + 1, ll, mm);
    inc(l, r, d, 2 * n + 2, mm, rr);
    if (min[2 * n + 1] < min[2 * n + 2]) {
      min[n] = min[2 * n + 1];
    } else {
      min[n] = min[2 * n + 2];
    }
  }

  int get(int i) {
    assert(i >= 0 && i < n);
    return get(i, 0, 0, n);
  }
  int get(int i, int n, int ll, int rr) {
    assert(rr > ll) ;
    if (rr > ll + 1) {
      push(n);
    }
    if (rr == ll + 1) {
      return min[n].first;
    }
    int mm = (ll + rr) / 2;
    if (i < mm) {
      return get(i, 2 * n + 1, ll, mm);
    } else {
      return get(i, 2 * n + 2, mm, rr);
    }
  }
  pair<int, int> getmin() {
    return min[0];
  }
};

vector<vector<int>> g;
vector<int> p;
vector<int> sz;

void dfs(int x, int p) {
  sz[x] = 1;
  int i = 0;
  int mx = -1;
  for (int y : g[x]) {
    if (y != p) {
      dfs(y, x);
      sz[x] += sz[y];
      if (mx == -1 || sz[g[x][i]] > sz[g[x][mx]]) {
        mx = i;
      }
    }
    i++;
  }
  if (mx >= 0) {
     swap(g[x][0], g[x][mx]);
  }
}

vector<int> ans;
vector<segtree> d;

void dfs2(int x, int p, int q) {
//  cout << ">" << x << " " << q << "\n";
  assert(q < (int)d.size());
  int i = 0;
  for (int y : g[x]) {
    if (y == p) continue;
    i++;
    if (i == 1) {
      dfs2(y, x, q);
    } else {
      d.push_back(segtree(sz[y]));
      int yy = (int)d.size() - 1;
      dfs2(y, x, yy);
      for (int j = 0; j < sz[y]; j++) {
        int k = j + 1 - d[yy].get(j);
//        eprintf("for j = %d, from y = %d got k = %d\n", j, y, k);
        d[q].inc(j, j + 1, -k);
      }
      d[q].inc(sz[y], d[q].n, -sz[y]);
    }
  }
  d[q].inc(0, d[q].n, -1);
  while (true) {
    auto p = d[q].getmin();
    if (p.first <= 0) {
      ans[p.second]++;
      d[q].inc(p.second, p.second + 1, -p.first + (p.second + 1));
    } else {
      break;
    }
  }
//  cout << x << " " << q << ": ";
//  for (int i = 0; i < d[q].n; i++) {
//    cout << (i + 1) - d[q].get(i) << " ";
//  }
//  for (int i = 0; i < (int)ans.size(); i++) {
//    cout << " " << ans[i];
//  }
//  cout << "\n";
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  g.resize(n);
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    x--;
    y--;
    g[x].push_back(y);
    g[y].push_back(x);
  }

  sz.resize(n);
  dfs(0, -1);

  d.reserve(n);
  d.push_back(segtree(n));
  ans.resize(n);
  dfs2(0, -1, 0);

  for (int i = 0; i < n; i++) {
    cout << ans[i] << "\n";
  }

  return 0;
}
