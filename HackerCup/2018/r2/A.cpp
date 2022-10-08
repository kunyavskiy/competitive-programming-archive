#include <iostream>
#include <fstream>

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
  int n, k;
  scanf("%d%d", &n, &k);
  if (n == 2 || k <= 2) {
    printf("0\n%d\n%d %d 1\n", 1, 1, n);
    return;
  }
  int ans = -k;
  int cur = k - 1;
  for (int i = 0; i < n - 1 && cur > 0; i++, cur--) {
    ans += cur;
  }
  printf("%d\n", ans);
  printf("%d\n", n);
  printf("%d %d %d\n", 1, n, k);
  cur = k - 1;
  for (int i = 0; i < n - 1 && cur > 0; i++, cur--) {
    ans += cur;
    printf("%d %d %d\n", i + 1, (cur == 1) ? n : i + 2, cur);
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
