#include <cassert>
#include <fstream>
#include <iostream>
#include <utility>
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

const int MAXN = 510;

int cnk[MAXN][MAXN];

void add(int& x, int y) {
  x += y;
  if (x >= 1e9) {
    x = 1e9 + 1;
  }
}

void PreCalc() {
  cnk[0][0] = 1;
  for (int i = 0; i < MAXN; i++) {
    for (int j = 0; j < MAXN; j++) {
      if (i)
        add(cnk[i][j], cnk[i - 1][j]);
      if (i && j)
        add(cnk[i][j], cnk[i - 1][j - 1]);
    }
  }
}

void solve() {
  int n;
  scanf("%d",&n);
  vector<pair<int, int>> ans;

  auto push = [&](int a, int b) {
    n -= cnk[a][b];
    ans.emplace_back(a, b);
  };

  if (n <= 100) {
    int m = n;
    for (int i = 0; i < m; i++) {
      push(i, 0);
    }
  } else {
    int upto = 30;
    int m = n - upto;
    bool rev = false;
    for (int i = 0; i < upto; i++) {
      if (m & (1ll << i)) {
        for (int j = 0; j <= i; j++) {
          push(i, rev ? i - j : j);
        }
        rev = !rev;
        upto++;
      } else {
        push(i, rev ? i : 0);
      }
    }
  }
  assert(n == 0);
  assert(ans.size() <= 500);
  for (auto x : ans) {
    printf("%d %d\n", x.first + 1, x.second + 1);
  }
  //fprintf(stderr, "%zd\n", ans.size());
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
    printf("Case #%d:\n", testId);
    solve();
  }

  TIMESTAMP(end);
  return 0;
}
