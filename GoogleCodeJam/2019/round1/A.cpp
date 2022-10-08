#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

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
  int n, q;
  scanf("%d%d", &n, &q);
  vector<int> xv(q + 1), yv(q + 1);
  for (int i = 0; i < n; i++) {
    int x, y;
    char c;
    scanf("%d%d %c", &x, &y, &c);
    switch (c) {
      case 'N': {
        yv[y + 1]++;
        break;
      }
      case 'S': {
        yv[y]--;
        yv[0]++;
        break;
      }
      case 'E': {
        xv[x + 1]++;
        break;
      }
      case 'W': {
        xv[x]--;
        xv[0]++;
        break;
      }
    }
  }
  for (int i = 1; i <= q; i++) {
    xv[i] += xv[i - 1];
    yv[i] += yv[i - 1];
  }
  int x = max_element(xv.begin(), xv.end()) - xv.begin();
  int y = max_element(yv.begin(), yv.end()) - yv.begin();
  printf("%d %d\n", x, y);
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
