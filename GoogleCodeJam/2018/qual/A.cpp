#include <iostream>
#include <fstream>
#include <cstring>

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

char P[40];

void solve() {
  int d;
  scanf("%d %s", &d, P);

  int ans = 0;
  int n = strlen(P);

  while (true) {
    ll cur = 1;
    ll curd = 0;
    for (int i = 0; i < n; i++) {
      if (P[i] == 'C') {
        cur *= 2;
      } else {
        curd += cur;
      }
    }
    if (curd <= d) {
      printf("%d\n", ans);
      return;
    }
    ans++;
    for (int i = n - 2; i >= -1; i--) {
      if (i == -1) {
        printf("IMPOSSIBLE\n");
        return;
      }
      if (P[i] == 'C' && P[i + 1] != 'C') {
        swap(P[i], P[i + 1]);
        break;
      }
    }
  }
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
