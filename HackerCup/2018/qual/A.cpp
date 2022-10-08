#include <iostream>
#include <fstream>
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
  int n, k;
  ll v;
  scanf("%d%d%lld", &n, &k, &v);
  vector<string> s;
  for (int i = 0; i < n; i++) {
    static char buf[200];
    scanf("%s", buf);
    s.push_back(buf);
  }
  int l = (k * (v - 1)) % n;
  int r = (k * v) % n;
  if (l < r) {
    for (int i = l; i < r; i++) {
      printf(" %s", s[i].c_str());
    }
    printf("\n");
  } else {
    for (int i = 0; i < r; i++) {
      printf(" %s", s[i].c_str());
    }
    for (int i = l; i < n; i++) {
      printf(" %s", s[i].c_str());
    }
    printf("\n");

  }
}


int main() {
//  freopen("a.in", "r", stdin);
//  freopen("a.out", "w", stdout);

  PreCalc();
  TIMESTAMP(PreCalc);

  char buf[1000];
  int testNum;
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d", &testNum);

  for (int testId = 1; testId <= testNum; testId++) {
    if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
      TIMESTAMPf("Test %d", testId);
    printf("Case #%d:", testId);
    solve();
  }

  TIMESTAMP(end);
  return 0;
}
