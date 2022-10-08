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

void PreCalc() {
}

void solve() {
  int n, q;
  scanf("%d%d", &n, &q);
  vector<int> d(n), s(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &d[i], &s[i]);
  }
  vector<vector<ll>> g(n, vector<ll>(n, -1));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%lld", &g[i][j]);
      if (i == j) g[i][j] = 0;
    }
  }

  for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        if (g[i][k] != -1 && g[k][j] != -1) {
          if (g[i][j] == -1) {
            g[i][j] = g[i][k] + g[k][j];
          } else {
            g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
          }
        }
      }

  vector<vector<double>> g2(n, vector<double>(n, 1e100));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (g[i][j] != -1 && g[i][j] <= d[i]) {
        g2[i][j] = g[i][j] * 1.0 / s[i];
      }
    }
  }

  for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        g2[i][j] = min(g2[i][j], g2[i][k] + g2[k][j]);
      }

  for (int i = 0; i < q; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    printf("%.18lf ", g2[a][b]);
  }
  printf("\n");

}


int main() {
//  freopen("c.in", "r", stdin);
//  freopen("c.out", "w", stdout);


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