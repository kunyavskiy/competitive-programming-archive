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

bool check(const vector<ll> &v, ll m) {
  ll lx = v[0] - m;
  ll rx = v[0] + m;
  for (ll x : v) {
    lx = max(lx, x - m);
    rx = min(rx, x + m);
  }
  return lx <= rx;
}

void solve() {
  int n;
  scanf("%d", &n);
  vector<ll> x(n), y(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld%lld", &x[i], &y[i]);
  }

  ll l = -1;
  ll r = (ll)1e18;
  while (r - l > 1) {
    ll m = (l + r) / 2;
    if (check(x, m) && check(y, m)) {
      r = m;
    } else {
      l = m;
    }
  }

  printf("%lld\n", r);
}


int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
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
