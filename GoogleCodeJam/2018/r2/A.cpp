#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

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
  vector<int> b(n);
  for (int &x : b) {
    scanf("%d", &x);
  }

  if (!b[0]|| !b.back()) {
    printf("IMPOSSIBLE\n");
    return;
  }

  vector<int> shift(n);
  int ptr = 0;
  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < b[i]; j++) {
      shift[ptr] = ptr - i;
      ans = max(ans, abs(shift[ptr]));
      ptr++;
    }
  }

  assert(shift[0] == 0 && shift[n - 1] == 0);
  ans++;

  vector<string> res(ans, string(n, '.'));

  for (int i = 0; i < n; i++) {
    if (shift[i] < 0) {
      for (int j = 0; j < -shift[i]; j++) {
        res[j][i + j] = '\\';
      }
    } else if (shift[i] > 0) {
      for (int j = 0; j < shift[i]; j++) {
        res[j][i - j] = '/';
      }
    }
  }

  printf("%d\n", ans);
  for (int i = 0; i < ans; i++) {
    printf("%s\n", res[i].c_str());
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
