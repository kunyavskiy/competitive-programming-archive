#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>

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

const int INF = 1e9;

vector<int> solve(vector<int> v) {
  vector<vector<int>> dp(v.size() + 1, vector<int>(v.size() + 1, INF)); // [prefix, switches]
  dp[1][0] = 0;
  for (int i = 0; i <= (int) v.size(); i++) {
    for (int j = 0; j <= (int) v.size(); j++) {
      if (i < (int) v.size() && j < (int) v.size()) {
        dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j]);
      }
      if (i != (int)v.size()) {
        dp[min(i + 2, (int) v.size())][j] = min(dp[min(i + 2, (int) v.size())][j], dp[i][j] + v[i]);
      }
    }
  }
  dp.back().pop_back();
  return dp.back();
}

void solve() {
  int h, s, q;
  scanf("%d%d%d", &h, &s, &q);
  vector<string> v(h);
  for (int i = 0; i < h; i++) {
    char buf[1000];
    scanf("%s", buf);
    v[i] = buf;
  }
  vector<int> ls(q);
  for (int &x : ls) {
    scanf("%d", &x);
  }
  vector<int> ans(q, 100000);

  for (int st = 'A'; st <= 'B'; st++) {
    vector<int> dels(h + 2);
    for (int j = 0; j < s; j++) {
      vector<int> cnt;
      if (v[0][j] != st) {
        cnt.push_back(0);
      }
      int start = 0;
      for (int k = 1; k <= h; k++) {
        if (k == h || v[k][j] != v[k - 1][j]) {
          cnt.push_back(k - start);
          start = k;
        }
      }
      auto local_dels = solve(cnt);
      for (int i = 1; i < (int)local_dels.size(); i++) {
        local_dels[i] = min(local_dels[i], local_dels[i - 1]);
      }
//      eprintf("cnt: ");
//      for (int x : cnt) {
//        eprintf("%d ", x);
//      }
//      eprintf("\n");
      for (int i = 0; i < (int)local_dels.size(); i++) {
//        eprintf("%d ", local_dels[i]);
        assert(local_dels[i] <= h + 100);
        dels[i] += local_dels[i];
      }
//      eprintf("\n");
    }
    for (int i = 1; i <= h + 1; i++) {
      assert(dels[i] <= dels[i - 1]);
    }
//    eprintf("===\n");
    for (int i = 0; i < q; i++) {
      int cur = lower_bound(dels.begin(), dels.end(), ls[i], greater<>()) - dels.begin();
//      eprintf("%d ", cur + 1);
      ans[i] = min(ans[i], cur + 1);
    }
//    eprintf("\n");
//    eprintf("===========\n");
  }

  for (int i = 0; i < q; i++) {
    printf("%d%c", ans[i], " \n"[i == q - 1]);
  }
}



int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
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
