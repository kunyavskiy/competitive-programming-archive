#include <iostream>
#include <fstream>
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

struct edge {
  int x, y, w;
};

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<vector<int>> g(n, vector<int>(n, 1 << 29));
  vector<edge> es(m);
  for (edge &e:es) {
    scanf("%d%d%d", &e.x, &e.y, &e.w);
    --e.x, --e.y;
    g[e.x][e.y] = g[e.y][e.x] = e.w;
  }
  for (int i = 0; i < n; i++) {
    g[i][i] = 0;
  }
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
      }
    }
  }
  for (edge e:es) {
    if (g[e.x][e.y] != e.w) {
      printf("Impossible\n");
      return;
    }
  }
  printf("%d\n", m);
  for (edge e:es) {
    printf("%d %d %d\n", e.x + 1, e.y + 1, e.w);
  }
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
