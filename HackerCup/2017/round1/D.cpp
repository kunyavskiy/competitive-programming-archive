//#include <iostream>
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
#include <stdarg.h>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if (_WIN32 || __WIN32__)
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "D"

typedef long long ll;
typedef long double ld;

const int MAXN = 2010;
const int MOD = 1000000007;

int mul(int a, int b) {
  return (int)((a * 1LL * b) % MOD);
}

void add(int& a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

int pow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) {
      res = mul(res, a);
    }
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int inv(int a) {
  return pow(a, MOD - 2);
}

int cnk[MAXN][MAXN];
int f[MAXN];

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<int> r(n);
  int sum = 0;
  for (int& x : r) {
    scanf("%d", &x);
    sum += x;
  }

  if (n == 1) {
    printf("%d\n", m);
    return;
  }

  int ans = 0;

  vector<int> cs(2 * sum + 1);

  int min_ok = sum;
  int val = m - min_ok + n - 1;
  assert(val < MOD);
  if (val >= n) {
    cs[min_ok] = 1;
    for (int i = 1; i <= n; i++) {
      cs[min_ok] = mul(cs[min_ok], val - i + 1);
      cs[min_ok] = mul(cs[min_ok], inv(i));
    }

    // c(x, n) = x!/(x-n)!/n! -> c(x-1, n) = (x-1)!/
    for (int i = min_ok + 1; i < (int)cs.size() && --val >= n; i++) {
      cs[i] = cs[i-1];
      cs[i] = mul(cs[i], inv(val + 1));
      cs[i] = mul(cs[i], val + 1 - n);
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      int cur = f[n - 2];
      int tot_used = 2*sum - r[i] - r[j];
      assert(tot_used >= min_ok);
      int tot_free = m - tot_used + n - 1;
      if (tot_free < n) continue;
      //assert(tot_free <= MAXN);
      //assert(cnk[tot_free][n] == cs[tot_used]);
      cur = mul(cur, cs[tot_used]);
      add(ans, cur);
    }
  }

  printf("%d\n", ans);
}

int main() {
  freopen(TASKNAME".in", "r", stdin);
  freopen(TASKNAME".out", "w", stdout);

  f[0] = 1;
  for (int i = 1; i < MAXN; i++) {
    f[i] = mul(f[i - 1], i);
  }
  for (int i = 0; i < MAXN; i++) {
    cnk[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      cnk[i][j] = cnk[i-1][j];
      add(cnk[i][j], cnk[i-1][j-1]);
    }
  }

  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    fprintf(stderr, "Case #%d\n", i);
    printf("Case #%d: ", i);
    solve();
  }

  return 0;
}
