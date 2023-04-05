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
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl
#define pb push_back
#define sz(a) (int)(a).size()
#define all(a) (a).begin() (a).end()
#define pw(x) (1ll << (x))


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

const int INF = 1e9;

struct segtree {
  int n, N;
  vector<int> a;
  vector<int> t, p;

  segtree(int _n) {
    n = _n;
    N = 1;
    while (N < n) N <<= 1;
    t.assign(2 * N, 0);
    p.assign(2 * N, 0);
  }

  void push(int v, int tl, int tr) {
    if (p[v] == 0) return;
    if (tl != tr) {
      p[v * 2] += p[v];
      p[v * 2 + 1] += p[v];
    }
    t[v] += p[v];
    p[v] = 0;
  }

  void add(int v, int tl, int tr, int l, int r, int x) {
    push(v, tl, tr);
    if (l > r) return;
    if (l == tl && r == tr) {
      p[v] += x;
      push(v, tl, tr);
      return;
    }
    int tm = (tl + tr) >> 1;
    add(v * 2, tl, tm, l, min(r, tm), x);
    add(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, x);
    t[v] = max(t[v * 2], t[v * 2 + 1]);
  }

  void add(int l, int r, int x) {
    add(1, 0, n - 1, l, r, x);
  }

  int get(int v, int tl, int tr, int l, int r) {
    push(v, tl, tr);
    if (l > r) return -INF;
    if (l == tl && r == tr) return t[v];
    int tm = (tl + tr) >> 1;
    return max(get(v * 2, tl, tm, l, min(r, tm)), get(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
  }

  int get(int l, int r) {
    return get(1, 0, n - 1, l, r);
  }
};

vector<int> solve(vector<int> a, int k) {
  int n = a.size();
  vector<int> dp(n + 2, INF);
  dp[0] = -INF;

  vector<pair<int, int>> old(n);
  for (int i = 0; i < n; i++) {
    int j = lower_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
    if (dp[j - 1] < a[i]) {
      old[i] = {j, dp[j]};
      dp[j] = a[i];
    }
  }

  vector<int> dp2(n + 2, -INF);
  dp2[0] = INF;

  segtree t(n + 1);
  for (int i = 0; i <= n; i++) {
    t.add(i, i, +i);
  }

  int o = 0;
  while (dp[o + 1] < INF) {
    o++;
  }
  t.add(0, 0, o);


  auto rollback = [&](int i) {
    ///int L = lower_bound(dp2.begin(), dp2.end(), greater<int>(), dp[old[i].first + 1]) - dp2.begin();
    int L = lower_bound(dp2.begin(), dp2.end(), dp[old[i].first], greater<int>()) - dp2.begin();
    int R = lower_bound(dp2.begin(), dp2.end(), old[i].second, greater<int>()) - dp2.begin();
    if (L > R) swap(L, R);
    t.add(L, R - 1, -1);
    dp[old[i].first] = old[i].second;
  };

  for (int i = n - 1; i > n - k; i--) {
    rollback(i);
  }

  vector<int> ans(n - k + 1);

  int mxR = 0;
  for (int i = n - k; i >= 0; i--) {
    rollback(i);

    ans[i] = t.get(0, mxR);

    int x = a[i + k - 1];
    int j = lower_bound(dp2.begin(), dp2.end(), x, greater<int>()) - dp2.begin();
    if (dp2[j - 1] > x) {
      dp2[j] = x;
      mxR = max(mxR, j);

      int was = t.get(j, j);
      int lb = lower_bound(dp.begin(), dp.end(), x) - dp.begin() - 1;
      t.add(j, j, -was + lb + j);
    }
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  //freopen("g.out", "w", stdout);
#endif

  int n, k;
  while (scanf("%d%d", &n, &k) == 2) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }

    auto ans = solve(a, k);
    for (int x : ans) printf("%d\n", x);
  }

  return 0;
}
