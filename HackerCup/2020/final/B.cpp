#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>


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

void solve() {
  int n;
  scanf("%d", &n);
  vector<vector<int>> g(n);
  vector<int> p(n);
  p[0] = -1;
  for (int i = 1; i < n; i++) {
    scanf("%d", &p[i]);
    --p[i];
    g[p[i]].push_back(i);
  }
  vector<int> lp(n, 0);
  vector<int> lp2(n, 0);
  auto upd = [&](int pos, int val) {
    if (lp[pos] < val) swap(lp[pos], val);
    if (lp2[pos] < val) swap(lp2[pos], val);
  };
  for (int i = n - 1; i >= 0; i--) {
    for (int j : g[i]) {
      upd(i, lp[j] + 1);
    }
  }

  vector<int> lpr(n);
  vector<int> dr(n);
  for (int i = 0; i < n; i++) {
    for (int j : g[i]) {
      dr[j] = dr[i] + 1;
      if (lp[j] == lp[i] - 1) {
        lpr[j] = max(lpr[i], lp2[i] + dr[i]);
      } else {
        lpr[j] = max(lpr[i], lp[i] + dr[i]);
      }
    }
  }

  vector<int> ans(n, 0);
  vector<int> ans2(n, numeric_limits<int>::min() / 2);
  auto upd_ans = [&](int pos, int val) {
    if (ans[pos] < val) swap(ans[pos], val);
    if (ans2[pos] < val) swap(ans2[pos], val);
  };

  upd_ans(0, lp[0]);
  upd_ans(0, lp2[0]);
  for (int i = 1; i < n; i++) {
    upd_ans(i, lp[i] + lpr[i] + 1);
    upd_ans(i, lp2[i] + lpr[i] + 1);
    if (p[i] == 0) {
      if (lp[0] == lp[i] + 1) {
        upd_ans(i, 1 + lp2[0]);
      } else {
        upd_ans(i, 1 + lp[0]);
      }
      continue;
    }
    if (ans[p[i]] == (lp[i] + 1) + lpr[p[i]] + 1) {
      upd_ans(i, ans2[p[i]] + 1);
    } else {
      upd_ans(i, ans[p[i]] + 1);
    }
  }

  int res = 1;
  for (int x : ans) {
//    eprintf("%d ", x);
    res = mul(res, x);
  }
//  eprintf("\n");
  printf("%d\n", res);
}


int main() {
#ifdef LOCAL
//  freopen("b.in", "r", stdin);
//  freopen("b.out", "w", stdout);
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
