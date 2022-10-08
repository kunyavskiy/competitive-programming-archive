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

typedef long long ll;
typedef long double ld;

void PreCalc() {
}

constexpr long long SECOND = 1'000'000'000;
constexpr long long MINUTE = SECOND * 60;
constexpr long long HOUR = MINUTE * 60;
constexpr long long FULL = 12 * HOUR;

void solve() {
  long long a, b, c;
  scanf("%lld %lld %lld", &a, &b, &c);

  auto find = [](vector<long long> a) {
    sort(a.begin(), a.end());
    do {
      for (int h = 0; h < 12; h++) {
        long long t = a[1] + h * HOUR * 12 - a[0];
        if (t % 11 != 0) continue;
        long long x = (t / 11) % FULL;
        if (x < 0) x += FULL;
        long long s = a[0] - x;
        eprintf("? %lld %lld %lld %lld\n", x / HOUR, (x % HOUR) / MINUTE, (x % MINUTE) / SECOND, x % SECOND);
        if ((12 * x + s) % FULL != a[1]) continue;
        if ((12 * 60 * x + s) % FULL != a[2]) continue;
        return x;
      }
    } while (next_permutation(a.begin(), a.end()));
    assert(false);
  };

  long long x = find({a, b, c});
  printf("%lld %lld %lld %lld\n", x / HOUR, (x % HOUR) / MINUTE, (x % MINUTE) / SECOND, x % SECOND);
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
