#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

typedef long long ll;
typedef long double ld;

void PreCalc() {
}

void solve() {
  int n, l;
  scanf("%d%d", &n, &l);
  vector<pair<int, int>> ids;
  int last = 0;
  for (int i = 0; i <= n; i++) {
    if ((i * 200LL + n) / (2 * n) > last) {
      last = (i * 200LL + n) / (2 * n);
      ids.push_back({i, last});
    }
  }
  const int INF = (1 << 29);
  vector<int> dp(n + 1, -INF);
  dp[0] = 0;
  vector<int> cnts(l);
  for (int i = 0; i < l; i++) {
    scanf("%d", &cnts[i]);
  }
  sort(cnts.rbegin(), cnts.rend());
  while ((int)cnts.size() < n) cnts.push_back(0);
  for (int i = 0; i < (int)cnts.size(); i++) {
    for (int from = n; from >= 0; from--) {
      if (from + cnts[i] <= n) {
        dp[from + cnts[i]] = max(dp[from + cnts[i]], dp[from] + ((cnts[i] * 200 + n) / (2 * n)));
      }
      for (auto x : ids) {
        if (from + x.first > n) break;
        if (x.first < cnts[i]) continue;
        dp[from + x.first] = max(dp[from + x.first], dp[from] + x.second);
      }
      if (cnts[i])
        dp[from] = -INF;
    }
  }
  printf("%d\n", *max_element(dp.begin(), dp.end()));
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
