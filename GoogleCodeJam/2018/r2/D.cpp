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

int s[25][25];
int p[25][25];

int cur;
int n, m;

void dfs(int x, int y) {
  if (x < 0 || y < 0 || x >= n || y >= m || !p[x][y]) return;
  cur++;
  p[x][y] = 0;
  dfs(x - 1, y);
  dfs(x + 1, y);
  dfs(x, y - 1);
  dfs(x, y + 1);
}

void solve() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      char c;
      scanf(" %c", &c);
      s[i][j] = c == 'B';
    }
  }

  vector<bool> have(16);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      have[s[i][j] * 15] = 1;
      if (j + 1 < m) {
        have[s[i][j] * 5 + s[i][j + 1] * 10] = 1;
      }
      if (i + 1 < n) {
        have[s[i][j] * 3 + s[i + 1][j] * 12] = 1;
      }
      if (i + 1 < n && j + 1 < m) {
        have[s[i][j] * 1 + s[i][j + 1] * 2 + s[i + 1][j] * 4 + s[i + 1][j + 1] * 8] = 1;
      }
    }
  }

  int ans = 0;

  for (int ty = 0; ty < 16; ty++) {
    if (!have[ty]) continue;
    for (int x = 0; x <= n; x++) {
      for (int y = 0; y <= m; y++) {
        for (int i = 0; i < n; i++) {
          for (int j = 0; j < m; j++) {
            int id = 0;
            if (i >= x) id |= 2;
            if (j >= y) id |= 1;
            int ex = !!(ty & (1 << id));
            p[i][j] = s[i][j] == ex;
          }
        }

         for (int i = 0; i < n; i++) {
          for (int j = 0; j < m; j++) {
            cur = 0;
            dfs(i, j);
            ans = max(ans, cur);
          }
        }
      }
    }
  }
  printf("%d\n", ans);
}


int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
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
