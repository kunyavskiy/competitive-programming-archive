#include <iostream>
#include <fstream>
#include <vector>
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

struct dsu {
  vector<int> p;
  vector<int> sz;

  explicit dsu(int n) : p(n), sz(n, 1) {
    for (int i = 0; i < n; i++) {
      p[i] = i;
    }
  }

  int get(int x) {
    if (p[x] == x) return x;
    return p[x] = get(p[x]);
  }

  void join(int a, int b) {
    a = get(a);
    b = get(b);
    if (a == b) return;
    if (sz[a] > sz[b]) swap(a, b);
    p[a] = b;
    sz[b] += sz[a];
  }
};

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  dsu d(n);
  for (int _ = 0; _ < m; _++) {
    int a, b;
    scanf("%d%d", &a, &b);
    for (int i = a - 1, j = b - 1; i < j; i++, j--) {
      d.join(i, j);
    }
  }
  vector<vector<int>> v;
  for (int i = 0; i < n; i++) {
    if (d.p[i] == i) {
      v.emplace_back();
      for (int j = 0; j < n; j++) {
        if (d.get(i) == d.get(j)) {
          v.back().push_back(j);
        }
      }
    }
  }

  vector<vector<bool>> dp(v.size() + 1, vector<bool>(n + 1));
  dp[0][0] = true;
  for (int i = 0; i < (int) v.size(); i++) {
    int s = v[i].size();
    dp[i + 1] = dp[i];
    for (int j = 0; j + s <= n; j++) {
      dp[i + 1][j + s] = dp[i + 1][j + s] || dp[i][j];
    }
  }
  string ans(n, '0');
  int best = 0;
  for (int i = 0; i < n; i++) {
    if (dp.back()[i] && (abs(i - (n - i)) < abs(best - (n - best)))) {
      best = i;
    }
  }

  for (int i = (int)v.size() - 1; i >= 0; i--) {
    if (!dp[i][best]) {
      assert(dp[i][best - v[i].size()]);
      best -= v[i].size();
      for (int x : v[i]) {
        ans[x] = '1';
      }
    }
  }

  printf("%s\n", ans.c_str());
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
