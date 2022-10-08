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

const int MOD = 998244353;

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

const int MAXN = 2100;

int f[MAXN];
int invf[MAXN];

int cnk(int n, int k) {
  return mul(f[n], mul(invf[k], invf[n - k]));
}

int dp[11][MAXN];
int ndp[11][MAXN];

vector<vector<int>> calc(vector<int> v) {
  int n = v.size();
  for (int i = 0; i < 11; i++) {
    memset(dp[i], 0, sizeof(int) * (n + 1));
  }
  dp[0][0] = 1;
  for (int it = 0; it < n; it++) {
    for (int i = 0; i < 11; i++) {
      memset(ndp[i], 0, sizeof(int) * (n + 1));
    }

    for (int i = 0; i < 11; i++) {
      for (int j = 0; j <= it; j++) {
        add(ndp[(i + v[it]) % 11][j], dp[i][j]);
        add(ndp[(i + 11 - v[it]) % 11][j + 1], dp[i][j]);
      }
    }

    for (int i = 0; i < 11; i++) {
      memcpy(dp[i], ndp[i], sizeof(int) * (n + 1));
    }
  }
  vector<vector<int>> res;
  for (int i = 0; i < 11; i++) {
    res.push_back(vector<int>(dp[i], dp[i] + n + 1));
  }
  return res;
}

void solve() {
  int n;
  scanf("%d", &n);
  vector<pair<int, int>> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i].first);
    a[i].second = i;
  }
  sort(a.begin(), a.end());
  int ans = 0;
  do {
    int val = 0;
    int coef = 1;
    for (int i = 0; i < n; i++) {
      int b = a[i].first;
      while (b) {
        val = (val + coef * (b % 10)) % 11;
        coef = (coef * 10) % 11;
        b /= 10;
      }
    }
    if (val == 0) {
      ans++;
    }
  } while (next_permutation(a.begin(), a.end()));
  printf("%d\n", ans);
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.a", "w", stdout);
#endif

  f[0] = invf[0] = 1;
  for (int i = 1; i < MAXN; i++) {
    f[i] = mul(f[i-1], i);
    invf[i] = mpow(f[i], MOD - 2);
  }

  int t;
  scanf("%d", &t);
  while (t --> 0)
    solve();

  return 0;
}
