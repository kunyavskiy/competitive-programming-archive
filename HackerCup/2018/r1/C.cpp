#include <iostream>
#include <fstream>
#include <vector>

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

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<int> h(n);
  scanf("%d%d", &h[0], &h[1]);
  ll w, x, y, z;
  scanf("%lld%lld%lld%lld", &w, &x, &y, &z);
  for (int i = 2; i < n; i++) {
    h[i] = (w * h[i-2] + x * h[i-1] + y) % z;
  }

  vector<ld> l(n, 1e18);
  vector<ld> r(n, 1e18);
  for (int i = 0; i < m; i++) {
    int a, b, u, d;
    scanf("%d%d%d%d", &a, &b, &u, &d);
    if (a > b) {
      swap(a, b);
      swap(u, d);
    }
    --a, --b;

    for (int j = a + 1; j <= b; j++) {
      l[j] = min(l[j], (ld)d);
      r[j] = min(r[j], (ld)u);
    }
  }

  ld lf = 0;
  ld rg = 1e9;

  for (int i = 0; i < 100; i++) {
    ld v = (lf + rg) / 2;
    ld lx = h[0] - v;
    ld rx = h[0] + v;
    bool ok = true;

    for (int j = 1; j < n; j++) {
      lx -= l[j];
      rx += r[j];
      lx = max(lx, h[j] - v);
      rx = min(rx, h[j] + v);
      if (lx > rx) {
        ok = false;
      }
    }

    if (ok) {
      rg = v;
    } else {
      lf = v;
    }
  }

  printf("%.18lf\n", (double)((lf + rg) / 2));
}


int main() {
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);

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
