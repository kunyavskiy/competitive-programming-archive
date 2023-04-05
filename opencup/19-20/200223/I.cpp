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

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


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
typedef pair<ll, int> pli;

pair<int, pli> solve2(ll A, int B,
                      const vector<ll> &a,
                      const vector<ll> &sum,
                      const vector<int> &count_eq,
                      int L, int R) {
  auto is_good = [&](int moves, pli &res) {
    int last_pos = R - moves * B - 1;
    if (last_pos < L) {
      res = {0, 0};
      return true;
    }
    ll maxX = a[last_pos];
    int countAll = (last_pos - L + 1);
    int countMax = std::min(count_eq[last_pos], countAll);
    int countLess = countAll - countMax;
    ll sumLess = sum[L + countLess] - sum[L];
    ll needSum = (maxX - 1) * countLess - sumLess;
    if (needSum <= A * moves) {
      ll sumAll = sum[L + countAll] - sum[L];
      ll endMaxX = (A * moves + sumAll) / countAll;
      int cntX = (A * moves + sumAll) % countAll;
      if (cntX == 0) {
        cntX = countAll;
      } else {
        endMaxX++;
      }
      res = {endMaxX, cntX};
      return true;
    }
    return false;
  };

  int left = 0;
  int right = (R - L);
  pli res;
  while (left + 1 < right) {
    int middle = (left + right) / 2;
    if (is_good(middle, res)) {
      right = middle;
    } else {
      left = middle;
    }
  }
  assert(is_good(right, res));
  return {max(0, (R - L) - B * right),  res};
}

void solve() {
  int n, B;
  ll A;
  scanf("%d%lld%d", &n, &A, &B);
  vector<ll> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lld", &a[i]);
  }
  sort(a.begin(), a.end());
  vector<int> count_eq(n);
  for (int i = 0; i < n; ++i) {
    if (i && a[i - 1] == a[i]) {
      count_eq[i] = count_eq[i - 1] + 1;
    } else {
      count_eq[i] = 1;
    }
  }
  vector<ll> sum(n + 1);
  for (int i = 1; i <= n; ++i) {
    sum[i] = sum[i - 1] + a[i - 1];
  }
  vector<pli> best(n + 1);
  best[n] = {(A - B - 1) / B, n};
  for (int i = 0; i < n; ++i) {
    auto res = solve2(A, B, a, sum, count_eq, n - i - 1, n);
    eprintf("i %d res (%d (%lld %d))\n", i, res.first, res.second.first, res.second.second);
    best[res.first] = max(best[res.first], res.second);
  }

  auto make_move = [&](int cnt, pli state) {
    eprintf("make_move(%d %lld %d) => ", cnt, state.first, state.second);
    assert(cnt > B);
    ll x1 = state.first;
    int k1 = state.second;
    int k0 = cnt - k1;
    ll have = A;
    assert(have >= B);
    have -= B;
    k0 -= B;
    k1 += B;
    assert(have >= (x1 - 1) * (B - 1));
    k0 += B - 1;
    have -= (x1 - 1) * (B - 1);
    cnt--;
    ll delta = have / cnt;
    x1 += delta;
    have -= delta * cnt;

    int p = min<ll>(k0, have);
    k1 += p;
    k0 -= p;
    have -= p;

    if (have) {
      assert(k0 == 0);
      assert(have < cnt);
      x1++;
      k0 = k1 - (int)have;
      k1 = have;
      have = 0;
    }
    eprintf("(%d %lld %d)\n", cnt, x1, k1);
    return pli{x1, k1};
  };

  for (int i = n; i > B; --i) {
    best[i - 1] = max(best[i - 1], make_move(i, best[i]));
  }
  ll ans = 0;
  for (int i = 1; i <= B; ++i) {
    ans = max(ans, best[i].first + A);
  }
  printf("%lld\n", ans);
}

int main() {
#ifdef LOCAL
  freopen("in", "r", stdin);
#endif

  int tt;
  scanf("%d", &tt);
  for (int ii = 0; ii < tt; ++ii) {
    solve();
    eprintf("-----\n");
  }

  return 0;
}

/*
 15
18
118
i 0 res (0 (0 0))
i 1 res (1 (7 1))
i 2 res (2 (4 2))
make_move(3 3 3) => (2 6 1)
make_move(2 6 1) => (1 10 2)
-----
i 0 res (0 (0 0))
i 1 res (1 (7 1))
i 2 res (2 (4 2))
i 3 res (3 (3 2))
i 4 res (4 (2 4))
make_move(5 3 5) => (4 5 1)
make_move(4 5 1) => (3 6 3)
make_move(3 6 3) => (2 9 1)
make_move(2 9 1) => (1 13 2)
-----
i 0 res (0 (0 0))
i 1 res (0 (0 0))
i 2 res (0 (0 0))
i 3 res (0 (0 0))
i 4 res (0 (0 0))
-----
i 0 res (0 (0 0))
i 1 res (1 (8 1))
i 2 res (2 (5 2))
i 3 res (2 (5 2))
i 4 res (3 (4 3))
i 5 res (4 (4 1))
i 6 res (5 (3 4))
i 7 res (6 (3 2))
make_move(8 1 8) => (7 2 3)
make_move(7 2 3) => (6 2 6)
make_move(6 3 2) => (5 3 5)
make_move(5 3 5) => (4 4 3)
make_move(4 4 3) => (3 5 2)
make_move(3 5 2) => (2 6 3)
make_move(2 6 3) => I: /home/pavel/olymp/opencup/200223/I/I.cpp:160: solve()::<lambda(int, pli)>: Assertion `have < cnt' failed.

 */
