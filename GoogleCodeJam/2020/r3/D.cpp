#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <tuple>

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
  int n;
  ll d;
  scanf("%d%lld", &n, &d);
  assert(n == 2);
  auto read = [] () -> pair<int, int> {
    int x, y;
    scanf("%d%d", &x, &y);
    return {x + y, x - y};
  };
  ll x, y;
  {
    int x1, y1;
    tie(x1, y1) = read();
    tie(x, y) = read();
    x -= x1;
    y -= y1;
    x = abs(x);
    y = abs(y);
  }

  ll num, den;
  if (max(x, y) >= 2 * d) {
    num = 0;
    den = 1;
  } else if (max(x, y) <= d){
    ll sqi = (2 * d - x) * (2 * d - y);
    den = 8 * d * d - sqi;
    num = den - 4 * x * y;
  } else {
    ll sqi = (2 * d - x) * (2 * d - y);
    den = 8 * d * d - sqi;
    num = 3 * sqi;
  }
  ll g = __gcd(num, den);
  printf("%lld %lld\n", num / g, den / g);
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
