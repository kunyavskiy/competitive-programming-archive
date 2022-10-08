#include <iostream>
#include <fstream>
#include <vector>
#include <set>

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
  int n;
  scanf("%d", &n);
  int trace = 0;
  vector<vector<int>> x(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &x[i][j]);
    }
    trace += x[i][i];
  }

  int r = 0;
  for (int i = 0; i < n; i++) {
    set<int> s;
    for (int j = 0; j < n; j++) {
      if (!s.insert(x[i][j]).second) {
        r++;
        break;
      }
    }
  }

  int c = 0;
  for (int j = 0; j < n; j++) {
    set<int> s;
    for (int i = 0; i < n; i++) {
      if (!s.insert(x[i][j]).second) {
        c++;
        break;
      }
    }
  }

  printf("%d %d %d\n", trace, r, c);

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
