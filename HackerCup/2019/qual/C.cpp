#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>

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

char s[500];
int dp[500][500][4];

int solve(int l, int r, int val) {
  int &ans = dp[l][r][val];
  if (ans != -1) return ans;
  ans = 1 << 30;
  if (r - l == 1) {
    if (s[l] == '1') return ans = (val != 3);
    if (s[l] == '0') return ans = (val != 0);
    if (s[l] == 'x') return ans = (val != 1);
    if (s[l] == 'X') return ans = (val != 2);
  }
  int op = -1;
  int bal = 0;
  for (int i = l; i < r; i++) {
    if (s[i] == '(') bal++;
    else if (s[i] == ')') bal--;
    else if (bal == 0) {
      if (s[i] == '&' || s[i] == '|' || s[i] == '^') {
        assert(op == -1);
        op = i;
      }
    }
  }
  if (op == -1) {
    assert(s[l] == '(' && s[r - 1] == ')');
    return ans = solve(l + 1, r - 1, val);
  }
  for (char real_op : string{"&|^"}) {
    auto do_op = [&](int a, int b) {
      if (real_op == '&') return a & b;
      if (real_op == '|') return a | b;
      if (real_op == '^') return a ^ b;
      assert(0);
    };
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (do_op(i, j) == val) {
          if (s[op] == '&') {
            eprintf("%d[%d] %d[%d] %c\n", i, solve(l, op, i), j, solve(op + 1, r, j), real_op);
          }
          ans = min(ans, solve(l, op, i) + solve(op + 1, r, j) + (s[op] != real_op));
        }
      }
    }
  }
  return ans;
}

void solve() {
  scanf("%s", s);
  memset(dp, -1, sizeof(dp));
  printf("%d\n", min(solve(0, strlen(s), 0), solve(0, strlen(s), 3)));
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
