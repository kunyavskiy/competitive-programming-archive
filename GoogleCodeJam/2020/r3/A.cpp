#include <cassert>
#include <algorithm>
#include <fstream>
#include <iostream>
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
  string a, b;
  cin >> a >> b;
  auto distance = [](const string& a, const string& b) {
    vector<vector<int>> dp(a.size() + 1, vector<int>(b.size() + 1, 1e9));
    dp[0][0] = 0;

    for (size_t i = 0; i <= a.size(); i++) {
      for (size_t j = 0; j <= b.size(); j++) {
        if (i != a.size()) {
          dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);
        }
        if (j != b.size()) {
          dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + 1);
        }
        if (i != a.size() && j != b.size()) {
          dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + (a[i] != b[j]));
        }
      }
    }
    return dp;
  };

  string result;
  auto dp = distance(a, b);
  int ans = dp.back().back();
  int i = a.size();
  int j = b.size();
  while (dp[i][j] > ans / 2) {
    if (i && dp[i][j] == dp[i - 1][j] + 1) {
      i--;
    } else {
      result += b[j - 1];
      if (j && dp[i][j] == dp[i][j - 1] + 1) {
        j--;
      } else {
        assert(i && j && dp[i][j] == dp[i - 1][j - 1] + (a[i - 1] != b[j - 1]));
        i--, j--;
      }
    }
  }
  reverse(result.begin(), result.end());
  result = a.substr(0, i) + result;
  printf("%s\n", result.c_str());
#ifdef LOCAL
  int d1 = distance(a, result).back().back();
  int d2 = distance(b, result).back().back();
  eprintf("%d %d %d\n", d1, d2,dp.back().back());
  assert(d1 + d2 == dp.back().back());
  assert(abs(d1 - d2) <= 1);
#endif
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
