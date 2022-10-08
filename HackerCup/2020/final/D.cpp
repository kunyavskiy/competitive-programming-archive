#include <iostream>
#include <fstream>
#include <utility>
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

typedef long long ll;
typedef long double ld;

void PreCalc() {
}

vector<int> read_gen(int n, int k) {
  vector<int> data;
  data.resize(k);
  for (int &x : data) scanf("%d", &x);
  int a, b, c, d;
  scanf("%d%d%d%d", &a, &b, &c, &d);
  while ((int)data.size() < n) {
    data.push_back((a * 1LL * data[data.size()- 2] + b * 1LL * data.back() + c) % d + 1);
  }
  return data;
}

const int MOD = 1000000007;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) {
  return mpow(x, MOD - 2);
}


struct fenw_tree {
  vector<int> vals;
  explicit fenw_tree(int n) : vals(n) {}
  void add(int pos, int x) {
    while (pos < (int)vals.size()) {
      ::add(vals[pos], x);
      pos = pos | (pos + 1);
    }
  }
  int get(int pos) {
    int ans = 0;
    while (pos != -1) {
      ::add(ans, vals[pos]);
      pos = (pos & (pos + 1)) - 1;
    }
    return ans;
  }
};

struct linear_adder {
  vector<int> pos;
  fenw_tree a;
  fenw_tree b;

  explicit linear_adder(vector<int> poss) : pos(std::move(poss)), a(0), b(0) {
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    a = fenw_tree(pos.size());
    b = fenw_tree(pos.size());
  }

  void add(int l, int r, int av, int bv) {
//    eprintf("[%d..%d] += (%d, %d)\n", l, r, av, bv);
    l = lower_bound(pos.begin(), pos.end(), l) - pos.begin();
    r = lower_bound(pos.begin(), pos.end(), r) - pos.begin();
    a.add(l, av);
    a.add(r, MOD - av);
    b.add(l, bv);
    b.add(r, MOD - bv);
  }
  int get(int x) {
    int posx = lower_bound(pos.begin(), pos.end(), x) - pos.begin();
//    eprintf("f(%d) = %d * %d + %d = ", x, a.get(posx), x, b.get(posx));
    int ans = mul(a.get(posx), x);
    ::add(ans, b.get(posx));
//    eprintf("%d\n", ans);
    return ans;
  }
};

void solve() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  vector<int> h = read_gen(n, k);
  vector<int> x = read_gen(m, k);
  vector<int> y = read_gen(m, k);
  vector<int> z = read_gen(m, k);
  vector<int> w = read_gen(m, k);

  linear_adder solver(w);
  map<int, int> cur;
  int cnst = 0;
  for (int i = 1; i < n; i++) {
    add(cnst, mul(2, mul(i, n - i)));
  }
  solver.add(numeric_limits<int>::min(), numeric_limits<int>::max(), 0, cnst);
  auto add_pair = [&](int a, int b, int pos) {
//    eprintf("+ %d %d %d\n", a, b, pos);
    int coef = mul(2, mul(pos, n - pos));
    solver.add(numeric_limits<int>::min(), min(a, b), 0, mul(coef, abs(a - b)));
    solver.add(min(a, b), max(a, b), MOD - coef, mul(coef, max(a, b)));
  };
  auto remove_pair = [&](int a, int b, int pos) {
//    eprintf("- %d %d %d\n", a, b, pos);
    int coef = mul(2, mul(pos, n - pos));
    solver.add(numeric_limits<int>::min(), min(a, b), 0, MOD - mul(coef, abs(a - b)));
    solver.add(min(a, b), max(a, b), coef, MOD - mul(coef, max(a, b)));
  };
  auto insert = [&](int x, int val) {
    auto it = cur.find(x);
    assert(it == cur.end());
    auto nxt = cur.lower_bound(x);
    if (nxt == cur.begin()) {
      if (nxt != cur.end()) {
        add_pair(val, nxt->second, nxt->first);
      }
    } else if (nxt == cur.end()) {
      auto prv = std::prev(nxt);
      add_pair(prv->second, val, x);
    } else {
      auto prv = std::prev(nxt);
      remove_pair(prv->second, nxt->second, nxt->first);
      add_pair(prv->second, val, x);
      add_pair(nxt->second, val, nxt->first);
    }
    cur[x] = val;
  };

  auto remove = [&](int x) {
    auto it = cur.find(x);
    if (it == cur.end()) {
      return;
    }
    if (it == cur.begin()) {
      auto nit = next(it);
      remove_pair(it->second, nit->second, nit->first);
      cur.erase(it);
    } else {
      auto nit = next(it);
      auto pit = prev(it);
      remove_pair(pit->second, it->second, it->first);
      if (nit != cur.end()) {
        remove_pair(it->second, nit->second, nit->first);
        add_pair(pit->second, nit->second, nit->first);
      }
      cur.erase(it);
    }
  };

  auto change = [&](int x, int val) {
    remove(x);
    insert(x, val);
  };
  for (int i = 0; i < n; i++) {
    if (i == 0 || h[i] != h[i - 1]) {
      change(i, h[i]);
    }
  }

  int ans = 1;

  for (int i = 0; i < m; i++) {
    int l = x[i] - 1;
    int r = min(x[i] + y[i] - 1, n);
    int prevval = prev(cur.upper_bound(l))->second;
    change(l, z[i]);
    auto it = cur.lower_bound(l);
    while (true) {
      auto nit = next(it);
      if (nit == cur.end() || nit->first >= r) {
        if (r != n) {
          if (nit->first != r) {
            change(r, prevval);
          }
        } else {
          assert(nit == cur.end());
        }
        break;
      }
      prevval = nit->second;
      remove(nit->first);
    }

    int res = solver.get(w[i]);
//    eprintf("res = %d\n", res);
    ans = mul(ans, res);
  }
  printf("%d\n", ans);
}


int main() {
#ifdef LOCAL
//  freopen("d.in", "r", stdin);
//  freopen("d.out", "w", stdout);
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
