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
  static char s[10000];
  scanf("%s", s);
  int cnt_b = 0;
  int cnt_dot = 0;
  for (int i = 0; s[i]; i++) {
    if (s[i] == 'B') cnt_b++;
    else if (s[i] == '.') cnt_dot++;
  }
  if (cnt_b >= cnt_dot && cnt_dot != 0) {
    printf("Y\n");
  } else {
    printf("N\n");
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
