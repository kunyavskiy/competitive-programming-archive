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

constexpr int MAXN = 1'100'000;

vector<int> ans;

void PreCalc() {
  vector<vector<int>> divs(MAXN);
  for (int i = 1; i < MAXN; i++) {
    for (int j = i; j < MAXN; j += i) {
      divs[j].push_back(i);
    }
  }
  vector<int> dp(MAXN);
  for (int i = 2; i < MAXN; i++) {
    dp[i] = 1;
    for (int d : divs[i]) {
      if (d > 1 && d != i) {
        dp[i] = max(dp[i], dp[i / d - 1] + 1);
      }
    }
  }


  ans.resize(MAXN);
  for (int i = 3; i < MAXN; i++) {
    ans[i] = 1;
    for (int d : divs[i]) {
      if (d > 2 && d != i) {
        ans[i] = max(ans[i], dp[i / d - 1] + 1);
      }
    }
  }
}

void solve() {
  int n;
  scanf("%d", &n);
  printf("%d\n", ans[n]);
}


int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
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
