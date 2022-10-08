#include <iostream>
#include <fstream>

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

const int MAXN = 510;
const int MAGIC = 40;

int dp[MAXN][MAXN];


void PreCalc() {
  for (int i = 0; i < MAXN; i++) {
    for (int j = 0; j < MAXN; j++) {
      dp[i][j] = -1e9;
    }
  }
  dp[0][0] = 0;

  for (int i = 0; i < MAGIC; i++) {
    for (int j = !i; j < MAGIC; j++) {
      for (int ii = MAXN - 1; ii >= i; ii--) {
        for (int jj = MAXN - 1; jj >= j; jj--) {
          dp[ii][jj] = max(dp[ii][jj], dp[ii - i][jj - j] + 1);
        }
      }
    }
  }

  for (int i = 0; i < MAXN; i++) {
    for (int j = 0; j < MAXN; j++) {
      if (i) dp[i][j] = max(dp[i][j], dp[i - 1][j]);
      if (j) dp[i][j] = max(dp[i][j], dp[i][j - 1]);
//      printf("%d%c", dp[i][j], " \n"[j == MAXN - 1]);
    }
  }
}

void solve() {
  int R, B;
  scanf("%d%d", &R, &B);
  printf("%d\n", dp[R][B]);
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
