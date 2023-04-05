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
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char* what) : what(what){};
  __timestamper(const string& what) : what(what){};
  ~__timestamper(){
    TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

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

const int MAXN = 2100;

int f[MAXN];
int invf[MAXN];
int inv[MAXN];

int n, m, k;

int countp(const vector<int>& v) {
  int ans = f[n];
  for (int i : v) {
    ans = mul(ans, inv[i]);
  }
  for (int i = 0; i < (int)v.size(); ) {
    int j = i;
    for (; j < (int)v.size() && v[i] == v[j]; j++) {}
    ans = mul(ans, invf[j - i]);
    i = j;
  }
//  eprintf("count(");
//  for (int i : v) {
//    eprintf("%d ", i);
//  }
//  eprintf(") = %d\n", ans);
  return ans;
}

int solve(const vector<int>& v, int tot) {
  vector<int> cost(tot + 1);
  for (int i = 1; i <= tot; i++) {
    int g = 0;
    for (int u : v) {
      g += __gcd(u, i);
    }
    cost[i] = mpow(k, g);
  }

  vector<int> dp(tot + 1);
  dp[0] = 1;
  for (int i = 1; i <= tot; i++) {
    for (int j = 1; j <= i; j++) {
      int cur = cost[j];
      cur = mul(cur, f[i - 1]);
      cur = mul(cur, invf[i - j]);
      cur = mul(cur, dp[i - j]);
      add(dp[i], cur);
    }
  }
//  eprintf("solve(");
//  for (int i : v) {
//    eprintf("%d ", i);
//  }
//  eprintf(", %d) = %d\n", tot, dp[tot]);
  return dp[tot];
}

int go(int n, vector<int> &v) {
  if (!n) {
    return mul(countp(v), solve(v, m));
  }
  int res = 0;
  int last = v.empty() ? n : v.back();
  last = min(last, n);
  for (int i = 1; i <= last; i++) {
    v.push_back(i);
    add(res, go(n - i, v));
    v.pop_back();
  }
  return res;
}

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  f[0] = invf[0] = 1;
  for (int i = 1; i < MAXN; i++) {
    f[i] = mul(f[i - 1], i);
    invf[i] = minv(f[i]);
    inv[i] = minv(i);
  }

  scanf("%d%d%d", &n, &m, &k);

  if (n > m) swap(n, m);

  vector<int> tmp;
  int ans = go(n, tmp);

  ans = mul(ans, invf[n]);
  ans = mul(ans, invf[m]);

  printf("%d\n", ans);
  return 0;
}
