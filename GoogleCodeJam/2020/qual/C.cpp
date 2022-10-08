#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
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

void solve() {
  int n;
  scanf("%d", &n);
  vector<int> s(n), e(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &s[i], &e[i]);
  }
  string ans(n, ' ');
  vector<int> order(n);
  std::iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int x, int y) {
    return s[x] < s[y];
  });

  int l1, l2;
  l1 = l2 = 0;

  for (int t : order) {
    if (s[t] >= l1) {
      l1 = e[t];
      ans[t] = 'C';
    } else if (s[t] >= l2) {
      l2 = e[t];
      ans[t] = 'J';
    } else {
      printf("IMPOSSIBLE\n");
      return;
    }
  }
  printf("%s\n", ans.c_str());
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
