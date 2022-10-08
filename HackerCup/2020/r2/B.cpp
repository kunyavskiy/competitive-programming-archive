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

const int MAXN = 8000;

void PreCalc() {
}

void solve() {
  int n;
  double p;
  scanf("%d%lf", &n, &p);
  vector<double> dp(1);

  for (int i = 2; i <= n; i++) {
    vector<double> ndp(i);
    for (int j = 0; j < i; j++) {
      int total = i * (i - 1) / 2;
      int two_better = j * (j - 1) / 2;
      int two_worse = (i - j - 1) * (i - j - 2) / 2;
      int two_diffrent = j * (i - j - 1);
      int better_and_me = j;
      int worse_and_me = (i - j - 1);
      assert(two_better + two_worse +two_diffrent + better_and_me + worse_and_me == total);

      if (j != 0) {
        ndp[j] += dp[j - 1] * two_better;
        ndp[j] += dp[j - 1] * two_diffrent * (1 - p);
        ndp[j] += dp[j - 1] * better_and_me * (1 - p);
      }
      if (j != i - 1) {
        ndp[j] += dp[j] * two_worse;
        ndp[j] += dp[j] * two_diffrent * p;
        ndp[j] += dp[j] * worse_and_me * p;
      }
      ndp[j] /= total;
      ndp[j] += 1;
    }

    dp = std::move(ndp);
  }

  reverse(dp.begin(), dp.end());

  for (double a : dp) {
    printf("%.15f\n", a);
  }

}


int main() {
#ifdef LOCAL
//  freopen("b.in", "r", stdin);
//  freopen("b.out", "w", stdout);
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
    printf("Case #%d:\n", testId);
    solve();
  }

  TIMESTAMP(end);
  return 0;
}
