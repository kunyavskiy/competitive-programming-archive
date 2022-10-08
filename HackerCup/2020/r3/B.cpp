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

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  vector<int> pos(n);
  vector<int> type(n);
  vector<int> ids(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &pos[i], &type[i]);
    ids[i] = i;
  }
  sort(ids.begin(), ids.end(), [&](int a, int b) { return pos[a] < pos[b]; });

  const int INF = 1e9;

  vector<vector<int>> cost(n, vector<int>(n + 1, INF));
  vector<vector<int>> todo(n, vector<int>(n + 1, -1));
  auto min_remove = [](const vector<int> &no, const vector<int> &yes) {
    int ans = no.size();
    int pt = 0;
    for (int i = 0; i < (int) no.size(); i++) {
      while (pt < (int) yes.size() && yes[pt] < no[i]) pt++;
      ans = min(ans, pt + (int) no.size() - i - 1);
    }
    return ans;
  };
  for (int i = 0; i < n; i++) {
    vector<int> ts[2];
    if (i != 0 && pos[ids[i]] == pos[ids[i - 1]]) continue;
    for (int j = i; j < n; j++) {
      auto &v = ts[type[ids[j]]];
      v.insert(lower_bound(v.begin(), v.end(), ids[j]), ids[j]);
      if (j != n - 1 && pos[ids[j]] == pos[ids[j + 1]]) continue;
      cost[i][j + 1] = min_remove(ts[0], ts[1]);
      todo[i][j + 1] = !ts[1].empty();
    }
  }

  vector<vector<int>> dp(n + 1, vector<int>(n + 1, INF));
  dp[0][0] = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (dp[i][j] == INF) continue;
      for (int t = i + 1; t <= n; t++) {
        if (todo[i][t] != -1) {
          int& to = dp[t][j + todo[i][t]];
          int val = dp[i][j] + cost[i][t];
          if (to > val) {
            to = val;
//            printf("[%d, %d] updates [%d, %d] to %d by %d\n", i, j, t, j + todo[i][t], val, cost[i][t]);
          }
        }
      }
    }
  }
  int ans = 0;
  while (ans <= n && dp[n][ans] > k) ans++;
  if (ans == n + 1) ans = -1;
  printf("%d\n", ans);
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
    printf("Case #%d: ", testId);
    solve();
  }

  TIMESTAMP(end);
  return 0;
}
