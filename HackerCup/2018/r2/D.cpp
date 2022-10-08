#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <deque>
#include <set>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

using namespace std;

typedef long long ll;
typedef long double ld;

void PreCalc() {
}

class SegmentTree {
  typedef ll value_t;
  typedef ll update_t;

  static const value_t EMPTY_VALUE = 1LL << 60;
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

  void init(vector<value_t> v) {
    int n = (int) v.size();
    lst = 2;
    while (lst < n) lst *= 2;
    tree = vector<value_t>((size_t) 2 * lst, EMPTY_VALUE);
    for (int i = 0; i < n; i++) {
      tree[lst + i] = v[i];
    }
    for (int i = lst; i > 0; i--) {
      tree[i] = merge_values(tree[2 * i], tree[2 * i + 1]);
    }
    upd = vector<update_t>((size_t) 2 * lst, EMPTY_UPDATE);
  }

  value_t get(int l, int r) {
    value_t res = get(1, 0, lst, l, r);
//    eprintf("l = %d, r = %d -> %lld\n", l, r, res);
    return res;
  }

  void update(int l, int r, update_t u) {
//    eprintf("l = %d, r = %d, u = %lld\n", l, r, u);
    return update(1, 0, lst, l, r, u);
  }
};


vector<int> get_gen(int k) {
  vector<int> res;
  for (int i = 0; i < k; i++) {
    int l, a, x, y, z;
    scanf("%d%d%d%d%d", &l, &a, &x, &y, &z);
    for (int j = 0; j < l; j++) {
      res.push_back(a);
      a = (x * 1LL * a + y) % z + 1;
    }
  }
  return res;
}

void solve() {
  int n, s, m, k;
  scanf("%d%d%d%d", &n, &s, &m, &k);
  vector<pair<int, int>> v(n);
  {
    vector<int> p = get_gen(k);
    vector<int> d = get_gen(k);

    for (int i = 0; i < n; i++) {
      v[i] = {p[i], d[i]};
    }
  }

  sort(v.begin(), v.end());

  SegmentTree tree;
  tree.init(vector<ll>(n + 1));

  int ptr = 0;

  vector<pair<int, int>> st;
  st.push_back({0x3fffffff, 0});
  vector<ll> dp(n);
  tree.update(0, 1, s);

  for (int i = 0; i < n; i++) {
    while (ptr < i && v[i].first - v[ptr].first > 2 * m) {
      tree.update(ptr, ptr + 1, 1LL << 60);
      ptr++;
    }
    while (st.size() >= 2 && st.back().second >= ptr && st.back().first <= v[i].second) {
      tree.update(st[st.size() -2].second, st.back().second, -st.back().first);
      st.pop_back();
    }
    tree.update(st.back().second, i + 1, v[i].second);
    st.push_back({v[i].second, i + 1});
    dp[i] = tree.get(0, i + 1);
    tree.update(i + 1, i + 2, dp[i] + s);
  }

  printf("%lld\n", dp.back());
}


int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  PreCalc();
  TIMESTAMP(PreCalc);

  char buf[1000];
  int testNum;
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d", &testNum);

  for (int testId = 1; testId <= testNum; testId++) {
    if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
      TIMESTAMPf("Test %d", testId);
    printf("Case #%d: ", testId);
    solve();
  }

  TIMESTAMP(end);
  return 0;
}
