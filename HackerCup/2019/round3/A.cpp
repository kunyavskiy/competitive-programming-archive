#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

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

vector<vector<int>> solve(vector<pair<int,int>> v) {
  vector<vector<int>> dp(2);
  dp[0].push_back(0);
  dp[1].push_back(0);
  for (auto x : v) {
    int c = x.second - 1;
    dp[c].push_back(0);
    for (int i = (int)dp[c].size() - 1; i > 0; i--) {
      dp[c][i] = max(dp[c][i], dp[c][i-1] + (i - 1));
    }
    for (int i = (int)dp[1 - c].size() - 1; i >= 0; i--) {
      dp[c][1] = max(dp[c][1], dp[1 - c][i]);
    }
  }
  return dp;
}

void solve() {
  int h, n;
  scanf("%d%d", &h, &n);
  vector<pair<int, int>> lf, rg;
  for (int i = 0; i < n; i++) {
    int x, c;
    scanf("%d%d", &x, &c);
    if (x < h) {
      lf.emplace_back(x, c);
    } else {
      rg.emplace_back(2 * h - x, c);
    }
  }
  sort(lf.begin(), lf.end());
  sort(rg.begin(), rg.end());
  vector<vector<int>> lfs = solve(lf);
  vector<vector<int>> rgs = solve(rg);

  int ans = 0;
  for (int c1 = 0; c1 < (int)lfs.size(); c1++) {
    for (int i1 = 0; i1 < (int)lfs[c1].size(); i1++) {
      for (int c2 = 0; c2 < (int)rgs.size(); c2++) {
        for (int i2 = 0; i2 < (int)rgs[c2].size(); i2++) {
          int extra = (c1 == c2) ? i1 * i2 : 0;
          ans = max(ans, lfs[c1][i1] + rgs[c2][i2] + extra);
        }
      }
    }
  }

  printf("%d\n", ans);
}


int main() {
#ifdef LOCAL
//  freopen("a.in", "r", stdin);
//  freopen("a.out", "w", stdout);
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
