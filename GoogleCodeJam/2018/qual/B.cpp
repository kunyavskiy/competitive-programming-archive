#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

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
  int n;
  scanf("%d", &n);
  vector<int> a[2];
  for (int i = 0; i < n; i++) {
    int x;
    scanf("%d", &x);
    a[i % 2].push_back(x);
  }
  sort(a[0].begin(), a[0].end());
  sort(a[1].begin(), a[1].end());
  vector<int> v;
  for (int i = 0; i < n; i++) {
    v.push_back(a[i % 2][i / 2]);
  }
  for (int i = 0; i + 1 < n; i++) {
    if (v[i] > v[i + 1]) {
      printf("%d\n", i);
      return;;
    }
  }
  printf("OK\n");
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
