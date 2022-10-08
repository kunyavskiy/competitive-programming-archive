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

//#define STRESS

void solve() {
  static char s[100'100];
  scanf(" %s", s);
  int n = strlen(s);
  int d;
  scanf("%d", &d);
//  eprintf("s = |%s|, d = %d\n", s, d);
#ifdef STRESS
  int ans_stress = 0;
  for (int i = 0; i < (1 << (n - 1)); i++) {
    int cur = 0;
    bool last_ok = true;
    bool ok = true;
    for (int j = 0; j < n; j++) {
      cur = (cur * 10 + s[j] - '0') % d;
      if (i & (1 << j)) {
        if (cur % d == 0) {
          last_ok = true;
        } else {
          if (!last_ok) ok = false;
          last_ok = false;
        }
        cur = 0;
      }
    }
    if (!last_ok && cur % d != 0) ok = false;
    if (ok) { ans_stress++;}
  }
  eprintf("%d\n", ans_stress);
#endif

  int d25 = 1;
  int l2 = 0, l5 = 0;
  while (d % 2 == 0) d /= 2, d25 *= 2, l2++;
  while (d % 5 == 0) d /= 5, d25 *= 5, l5++;
  int l = max(l2, l5);
  vector<int> sum(n + 1);
  vector<vector<int>> poss(d);
  int deg = 1;
  for (int i = n - 1; i >= 0; i--) {
    sum[i] = (sum[i + 1] + (s[i] - '0') * 1LL * deg) % d;
    deg = (deg * 10LL) % d;
  }
  for (int i = 0; i <= n; i++) {
    poss[sum[i]].push_back(i);
  }

  auto eval = [](int from, int to, int d) {
    long long x = 0;
    for (int i = from; i < to; i++) {
      x = (x * 10 + s[i] - '0') % d;
    }
    return x % d;
  };

  vector<int> dp_good(n + 1);
  vector<int> dp_any(n + 1);
  dp_good[0] = 1;
  dp_any[0] = 1;
  vector<int> dp_good_psum(n + 1);
  dp_good_psum[0] = 1;
  vector<int> dp_good_s_psum(d), dp_any_s_psum(d), dp_s_ptr(d);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i && j <= l; j++) {
      int v = eval(i - j, i, d * d25);
      if (v % d || v % d25) continue;
      add(dp_good[i], dp_any[i - j]);
      sub(dp_any[i], dp_good[i - j]);
    }
    if (i >= l && eval(i - l, i, d25) == 0) {
      int &good_psum = dp_good_s_psum[sum[i]];
      int &any_psum = dp_any_s_psum[sum[i]];
      int &ptr = dp_s_ptr[sum[i]];
      auto &pos = poss[sum[i]];
      while (pos[ptr] < i - l) {
        add(good_psum, dp_good[pos[ptr]]);
        add(any_psum, dp_any[pos[ptr]]);
        ptr++;
      }
      add(dp_good[i], any_psum);
      sub(dp_any[i], good_psum);
    }
    dp_good_psum[i] = dp_good_psum[i - 1];
    add(dp_good_psum[i], dp_good[i]);
    add(dp_any[i], dp_good_psum[i]);
//    eprintf("%d %d\n", dp_good[i], dp_any[i]);
  }
  printf("%d\n", dp_any[n]);
#ifdef STRESS
  assert(dp_any[n] == ans_stress);
#endif
}


int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
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
