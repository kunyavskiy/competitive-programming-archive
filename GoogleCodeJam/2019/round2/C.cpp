#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

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

struct pt {
  int x, y;
};

struct rat {
  ll x, y;
  bool operator<(const rat & other) const {
    return x * other.y < y *  other.x;
  }

  bool operator==(const rat& other) const {
    return x * other.y == y * other.x;
  }
};

rat find_best(rat l, rat r) {
  if (l.x >= l.y) {
    ll d = l.x / l.y;
    rat res = find_best({l.x - d * l.y, l.y}, {r.x - d * r.y, r.y});
    res.x += res.y * d;
    return res;
  }
  if (r.x > r.y) {
    return {1, 1};
  }
  rat res = find_best({r.y, r.x}, {l.y, l.x});
  return {res.y, res.x};
}

void solve() {
  int n;
  scanf("%d", &n);
  vector<pt> v(n);
  for (pt &p : v) {
    scanf("%d%d", &p.x, &p.y);
  }

  rat l{0, 1}, r{1, 0};

  for (int i = 0; i + 1 < n; i++) {
    int dx = v[i + 1].x - v[i].x;
    int dy = v[i + 1].y - v[i].y;
    if (dx >= 0 && dy >= 0) continue;
    if (dx <= 0 && dy <= 0) {
      r = {0, 1};
      continue;
    }
    assert(dx && dy);
    if (dx > 0) {
      l = max(l, rat{-dy, dx});
    } else {
      r = min(r, rat{dy, -dx});
    }
  }

  if (!(l < r)) {
    printf("IMPOSSIBLE\n");
    return;
  }

  eprintf("%lld/%lld <= C / J <= %lld/%lld\n", l.x, l.y, r.x, r.y);

  rat res = find_best(l, r);
  printf("%lld %lld\n", res.x, res.y);

#ifdef LOCAL
  for (int i = 1; i <= 10000; i++) {
    for (int j = 1; j <= 10000; j++) {
      bool ok = true;
      for (int k = 0; k + 1 < n; k++) {
        ok &= v[k].x * i + v[k].y * j < v[k + 1].x * i + v[k + 1].y * j;
      }
      if (ok) {
        eprintf("res = %lld/%lld, ans = %d/%d\n", res.x, res.y, i, j);
        assert(i == res.x && j == res.y);
        return;
      }
    }
  }
  eprintf("res = %lld/%lld, ans = ???\n", res.x, res.y);
  assert(false);
#endif
}


int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
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
