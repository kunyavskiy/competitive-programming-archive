#include <iostream>
#include <fstream>
#include <assert.h>
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
  int a;
  assert(scanf("%d", &a) == 1);
  int off = 100, size;
  if (a == 20) {
    size = 6;
  } else if (a == 200) {
    size = 15;
  } else {
    eprintf("wtf is a = %d?\n", a);
    assert(0);
  }

  vector<vector<bool>> used(size, vector<bool>(size));
  for (int i = 1; i <= size; i += 3) {
    for (int j = 1; j <= size; j += 3) {
      int cnt = 0;
      while (cnt < 9) {
        printf("%d %d\n", off + i, off + j);
        fflush(stdout);
        int x, y;
        scanf("%d %d", &x, &y);
        if (x == 0 && y == 0) return;
        if (x == -1 && y == -1) return;
        x -= off;
        y -= off;
        if (!used[x][y]) {
          cnt++;
          used[x][y] = true;
        }
      }
    }
  }
}


int main() {
  PreCalc();
  TIMESTAMP(PreCalc);

  char buf[1000];
  int testNum;
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d", &testNum);

  for (int testId = 1; testId <= testNum; testId++) {
    if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
      TIMESTAMPf("Test %d", testId);
    solve();
  }

  TIMESTAMP(end);
  return 0;
}
