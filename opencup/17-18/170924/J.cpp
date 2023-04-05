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
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char* what) : what(what){};
  __timestamper(const string& what) : what(what){};
  ~__timestamper(){
    TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

class SegmentTree {
  typedef int value_t;
  typedef int update_t;

  static const value_t EMPTY_VALUE = 100000000;
  static const update_t EMPTY_UPDATE = 0;

  static inline value_t merge_values(const value_t &a, const value_t &b) {
    return min(a, b);
  }

  void apply(int v, const update_t &u) {
    tree[v] += u;
    upd[v] += u;
  }

  vector<value_t> tree;
  vector<update_t> upd;
  int lst;

  void push(int v) {
    apply(2 * v, upd[v]);
    apply(2 * v + 1, upd[v]);
    upd[v] = EMPTY_UPDATE;
  }

  value_t get(int v, int l, int r, int L, int R) {
    if (r <= L || R <= l) {
      return EMPTY_VALUE;
    }
    if (L <= l && r <= R) {
      return tree[v];
    }
    push(v);
    return merge_values(get(2 * v, l, (l + r) / 2, L, R), get(2 * v + 1, (l + r) / 2, r, L, R));
  }

  int find_min_r(int v, int l, int r, int L, int R) {
    if (r <= L || R <= l) {
      return -1;
    }
    if (tree[v] > 0) {
      return -1;
    }
    if (r == l + 1) {
      return l;
    }
    push(v);
    int res = find_min_r(2 * v + 1, (l + r) / 2, r, L, R);
    if (res == -1) {
      res = find_min_r(2 * v, l, (l + r) / 2, L, R);
    }
    return res;
  }

  int find_min_l(int v, int l, int r, int L, int R) {
    if (r <= L || R <= l) {
      return -1;
    }
    if (tree[v] > 0) {
      return -1;
    }
    if (r == l + 1) {
      return l;
    }
    push(v);
    int res = find_min_l(2 * v, l, (l + r) / 2, L, R);
    if (res == -1) {
      res = find_min_l(2 * v + 1, (l + r) / 2, r, L, R);
    }
    return res;
  }


  void update(int v, int l, int r, int L, int R, const update_t &u) {
    if (r <= L || R <= l) {
      return;
    }
    if (L <= l && r <= R) {
      apply(v, u);
      return;
    }
    push(v);
    update(2 * v, l, (l + r) / 2, L, R, u);
    update(2 * v + 1, (l + r) / 2, r, L, R, u);
    tree[v] = merge_values(tree[2 * v], tree[2 * v + 1]);
  }

public:

  void init(int n) {
    lst = 2;
    while (lst < n) lst *= 2;
    tree = vector<value_t>((size_t) (2 * lst), 0);
    upd = vector<update_t>((size_t) (2 * lst), 0);
  }

  value_t get(int l, int r) {
    return get(1, 0, lst, l, r);
  }

  int find_min_r(int l, int r) {
    return find_min_r(1, 0, lst, l, r);
  }

  int find_min_l(int l, int r) {
    return find_min_l(1, 0, lst, l, r);
  }

  void update(int l, int r, update_t u) {
    return update(1, 0, lst, l, r, u);
  }
};

vector<int> p[200002];

vector<int> build(vector<int> &a, vector<int> &from, vector<int> &to) {
  SegmentTree tree;
  SegmentTree tree2;
  tree.init(100002);
  tree2.init(100002);
  tree2.update(0, 100002, 1000000000);

  int n = (int)from.size();
  vector<int> res(n);

  for (int i = 0; i < n; i++) {
    int ll = min(from[i], to[i]);
    int rr = max(from[i], to[i]);
    tree.update(ll, rr, 1);
    tree2.update(from[i], from[i] + 1, -1000000000 + a[from[i]]);
  }

  for (int i = 0; i < 200002; i++) {
    p[i].clear();
  }

  for (int i = n - 1; i >= 0; i--) {
    p[a[from[i]]].push_back(from[i]);
  }

  for (int i = 0; i < n; i++) {
    int x = to[i];
//    cerr << a[from[i]] << " " << from[i] << " " << to[i] << endl;
    if (from[i] == x) {
      res[i] = a[from[i]];
      p[a[from[i]]].pop_back();
    } else if (from[i] < x) {
      int l;
      if (tree.get(0, x) > 0) {
        l = 0;
      } else {
        l = tree.find_min_r(0, x) + 1;
      }
      int m = tree2.get(l, x + 1);
      int y = p[m].back();
      p[m].pop_back();
      tree2.update(y, y + 1, 1000000000);
      tree.update(y, x, -1);
      res[i] = m;
    } else {
      int r = tree.find_min_l(x, 100002);
//      cerr << r << endl;
      int m = tree2.get(x, r + 1);
//      cerr << m << endl;
      int y = p[m].back();
      p[m].pop_back();
//      cerr << y << endl;
      tree2.update(y, y + 1, 1000000000);
      tree.update(x, y, -1);
      res[i] = m;
    }
  }
  return res;
}

pair<ll, vector<int>> solve(vector<int> &a, vector<int> &odd, vector<int> &even,
                            vector<int> &need_odd, vector<int> &need_even) {
  int n = a.size();
  ll s = 0;
  for (int i = 0; i < (int)odd.size(); i++) {
    s += abs(odd[i] - need_odd[i]);
  }
  for (int i = 0; i < (int)even.size(); i++) {
    s += abs(even[i] - need_even[i]);
  }

  vector<int> b_even = build(a, even, need_even);
  vector<int> b_odd = build(a, odd, need_odd);

  vector<int> b(n);
  for (int i = 0; i < (int)even.size(); i++) {
    b[need_even[i]] = b_even[i];
  }
  for (int i = 0; i < (int)odd.size(); i++) {
    b[need_odd[i]] = b_odd[i];
  }

  return {s, b};
};

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  vector<int> as = a;
  sort(as.begin(), as.end());
  as.erase(unique(as.begin(), as.end()), as.end());

  for (int i = 0; i < n; i++) {
    int t = lower_bound(as.begin(), as.end(), a[i]) - as.begin();
    a[i] = 2 * t + (a[i] % 2);
  }

  vector<int> odd;
  vector<int> even;
  vector<int> need_odd;
  vector<int> need_even;
  for (int i = 0; i < n; i++) {
    if (a[i] & 1) {
      odd.push_back(i);
    } else {
      even.push_back(i);
    }
    if (i & 1) {
      need_odd.push_back(i);
    } else {
      need_even.push_back(i);
    }
  }

  pair<ll, vector<int>> res = {-1, vector<int>(0)};
  if (odd.size() == need_odd.size()) {
    res = solve(a, odd, even, need_odd, need_even);
  }
  if (odd.size() == need_even.size()) {
    pair<ll, vector<int>> res2 = solve(a, odd, even, need_even, need_odd);
    if (res.first == -1 || res2.first < res.first || (res2.first == res.first && res2.second < res.second)) {
      res = res2;
    }
  }

  for (int i = 0; i < n; i++) {
    printf("%d ", as[res.second[i] / 2]);
  }
  puts("");

  return 0;
}
