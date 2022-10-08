#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
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

const int MOD = 1000000007;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) {
  return mpow(x, MOD - 2);
}

string out(int x) {
  for (int i = 1; i < 100; i++) {
    if (mul(x, i) <= 100) {
      return to_string(mul(x, i)) + "/" + to_string(i);
    }
  }
  return "???[" + to_string(x) + "]";
}

const int MAXC = 1100;
int cnk[MAXC][MAXC];
int facs[MAXC];

void PreCalc() {
  cnk[0][0] = 1;
  for (int i = 0; i < MAXC; i++) {
    for (int j = 0; j < MAXC; j++) {
      if (i) add(cnk[i][j], cnk[i - 1][j]);
      if (i && j) add(cnk[i][j], cnk[i - 1][j - 1]);
    }
  }
  facs[0] = 1;
  for (int i = 1; i < MAXC; i++) {
    facs[i] = mul(facs[i - 1], i);
  }
}

void solve() {
  int n;
  scanf("%d", &n);
  vector<int> d(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &d[i]);
    d[i] = 30 - d[i];
  }
  d.push_back(100);

  vector<int> as, ps;
  int prev_large = 0;
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    if (d[i] > d[prev_large]) {
      as.push_back(d[prev_large] * (i - prev_large - 1) - sum);
      ps.push_back(i - prev_large);
      prev_large = i;
      sum = 0;
    } else {
      sum += d[i];
    }
  }
  ps[0]++;
  ps.back()--;
  int maxs = accumulate(as.begin(), as.end(), 0);
  assert(accumulate(ps.begin(), ps.end(), 0) == n);
  for (int &p : ps) {
    p = mul(p, minv(n));
  }
  reverse(as.begin(), as.end());
  reverse(ps.begin(), ps.end());

  vector<vector<int>> dp(maxs + 1, vector<int>(maxs + 1, 0));
  dp[0][0] = 1;
  int tot_ps = 1;
  for (int i = 0; i < (int) as.size(); i++) {
    vector<vector<int>> ndp(maxs + 1, vector<int>(maxs + 1, 0));
    sub(tot_ps, ps[i]);
    for (int a = 0; a <= maxs; a++) {
      for (int b = 0; b <= a; b++) {
        if (!dp[a][b]) continue;
        for (int c = 0; a + c <= maxs; c++) {
          int go = dp[a][b];
          go = mul(go, cnk[a + c][c]);
          go = mul(go, mpow(ps[i], c));
          add(ndp[a + c][max(0, b + c - as[i])], go);
        }
      }
    }
    dp = std::move(ndp);
  }
  int ans = 0;
  for (int s = 0; s <= maxs; s++) {
    add(ans, dp[s][0]);
  }
  printf("%d\n", ans);
}


int main() {
#ifdef LOCAL
//  freopen("c.in", "r", stdin);
//  freopen("c.out", "w", stdout);
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
