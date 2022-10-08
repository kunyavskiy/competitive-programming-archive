#include <iostream>
#include <fstream>
#include <vector>

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

struct solver {
  vector<vector<int>> g;
  vector<int> mt;
  vector<bool> used;

  bool dfs(int v) {
    if (used[v]) return false;
    used[v] = true;
    for (int u : g[v]) {
      if (mt[u] == -1 || dfs(mt[u])) {
        mt[u] = v;
        return true;
      }
    }
    return false;
  }

public:
  solver(int n) : g(n) {

  }

  void add(int v, int u) {
    g[v].push_back(u);
  }

  int solve() {
    mt.resize(g.size(), -1);
    int ans = 0;
    for (int i = 0; i < (int)g.size(); i++) {
      used = vector<bool>(g.size());
      if (dfs(i)) {
        ans++;
      }
    }
    return ans;
  }
};

void PreCalc() {
}

void solve() {
  int n;
  scanf("%d", &n);
  vector<vector<int>> v(n, vector<int>(n, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &v[i][j]);
    }
  }

  int ans = n * n;

  for (int c = -n; c <= n; c++) {
    solver s(n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (v[i][j] == c) {
          s.add(i, j);
        }
      }
    }
    int r = s.solve();
    ans -= r;
  }

  printf("%d\n", ans);
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
