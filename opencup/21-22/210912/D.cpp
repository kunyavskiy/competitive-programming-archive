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
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

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

struct Solver {
  vector<int> tree;
  int lst;

  explicit Solver(int n) {
    lst = 2;
    while (lst < n) lst *= 2;
    tree.resize(2 * lst);
  }

  void set(int pos, int x) {
    pos += lst;
    tree[pos] = x;
    while (pos >>= 1) {
      tree[pos] = tree[2 * pos] + tree[2 * pos + 1];
    }
  }

  int left(int pos) {
    pos += lst;
    while (tree[pos] == 0) {
      if ((pos & (pos - 1)) == 0) return -1;
      pos = (pos - 1) >> 1;
    }
    while (pos < lst) {
      if (tree[2 * pos + 1] > 0)
        pos = 2 * pos + 1;
      else
        pos = 2 * pos;
    }
    return pos - lst;
  }

  int right(int pos) {
    pos += lst;
    while (tree[pos] == 0) {
      if ((pos & (pos + 1)) == 0) return -1;
      pos = (pos + 1) >> 1;
    }
    while (pos < lst) {
      if (tree[2 * pos] > 0)
        pos = 2 * pos;
      else
        pos = 2 * pos + 1;
    }
    return pos - lst;
  }
};

struct query {
  int l, r, id;
  int64_t ord;
};

inline int64_t gilbertOrder(int x, int y, int pow, int rotate) {
  if (pow == 0) {
    return 0;
  }
  int hpow = 1 << (pow-1);
  int seg = (x < hpow) ? (
                           (y < hpow) ? 0 : 3
                           ) : (
                           (y < hpow) ? 1 : 2
                         );
  seg = (seg + rotate) & 3;
  const int rotateDelta[4] = {3, 0, 0, 1};
  int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
  int nrot = (rotate + rotateDelta[seg]) & 3;
  int64_t subSquareSize = int64_t(1) << (2*pow - 2);
  int64_t ans = seg * subSquareSize;
  int64_t add = gilbertOrder(nx, ny, pow-1, nrot);
  ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
  return ans;
}


int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n, q;
  while (scanf("%d%d", &n, &q) == 2) {
    Solver s(n);
    vector<int> poss(n);
    vector<int> vals(n);
    for (int i = 0; i <n ; i++) {
      scanf("%d", &vals[i]);
      --vals[i];
      poss.at(vals[i]) = i;
    }
    vector<ll> ans(q);
    vector<query> qs(q);
    for (int i = 0; i < q; i++) {
      scanf("%d%d", &qs[i].l, &qs[i].r);
      qs[i].id = i;
      qs[i].ord = gilbertOrder(qs[i].l, qs[i].r, 21, 0);
    }
    constexpr int BLOCK = 700;
    sort(qs.begin(), qs.end(), [](const query &a, const query &b) {
      return a.ord < b.ord;
      int lfb = a.l / BLOCK;
      int rgb = b.l / BLOCK;
      if (lfb != rgb) return lfb < rgb;
      if (lfb % 2 == 0) return a.r < b.r;
      else return a.r > b.r;
    });
    ll cur = 0;
    vector<int> next(n, -1);
    vector<int> prev(n, -1);
    auto add = [&](int pos) {
      int val = vals[pos];
      int lf = s.left(val);
      int rg = s.right(val);
      if (lf != -1 && rg != -1) cur -= abs(poss[lf] - poss[rg]);
      if (lf != -1) cur += abs(pos - poss[lf]);
      if (rg != -1) cur += abs(pos - poss[rg]);
      next[val] = rg;
      prev[val] = lf;
      if (lf != -1) next[lf] = val;
      if (rg != -1) prev[rg] = val;
      s.set(val, 1);
    };
    auto remove = [&](int pos) {
      int val = vals[pos];
      s.set(val, 0);
      int lf = prev[val];
      int rg = next[val];
//      assert(lf == s.left(val));
//      assert(rg == s.right(val));
      if (lf != -1 && rg != -1) cur += abs(poss[lf] - poss[rg]);
      if (lf != -1) cur -= abs(pos - poss[lf]);
      if (rg != -1) cur -= abs(pos - poss[rg]);
      if (lf != -1) next[lf] = rg;
      if (rg != -1) prev[rg] = lf;
      next[val] = prev[val] = -1;
    };

    int curl, curr;
    curl = curr = 0;
    for (auto &q : qs) {
      int l = q.l - 1, r = q.r;
      while (curr < r) add(curr++);
      while (curl > l) add(--curl);
      while (curr > r) remove(--curr);
      while (curl < l) remove(curl++);
      ans[q.id] = cur;
    }
    for (ll x : ans) {
      printf("%lld\n", x);
    }
  }

  return 0;
}
