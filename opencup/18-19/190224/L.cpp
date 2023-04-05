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

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


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

int MOD;

namespace mod {
  typedef long long ll;
//  const int MOD = 998244353;

  void add(int &a, ll b) {
    a = (a + b) % MOD;
  }

  int mul(int a, int b) {
    return 1LL * a * b % MOD;
  }

  int bin(int a, ll n) {
    int res = 1;
    while (n) {
      if (n & 1) res = 1LL * res * a % MOD;
      a = 1LL * a * a % MOD;
      n >>= 1;
    }
    return res;
  }

  int inv(int x) {
    return bin(x, MOD - 2);
  }

  vector<int> fct, ofct, rev;

  void ensureFact(int n) {
    if ((int)fct.size() > n) return;
    int old = fct.size();
    fct.resize(n + 1);
    ofct.resize(n + 1);
    rev.resize(n + 1);
    if (old == 0) {
      fct[0] = ofct[0] = 1;
      rev[0] = 0;
      old++;
    }
    for (int i = old; i <= n; i++) {
      fct[i] = mul(fct[i - 1], i);
      if (i == 1) rev[i] = 1;
      else rev[i] = (MOD - mul(MOD / i, rev[MOD % i])) % MOD;
      ofct[i] = mul(ofct[i - 1], rev[i]);
    }
  }

  int getC(int n, int k) {
    if (n < k || k < 0) return 0;
    ensureFact(n);
    return mul(fct[n], mul(ofct[k], ofct[n - k]));
  }

  void clear() {
    fct.clear();
    ofct.clear();
    rev.clear();
  }
}
using namespace mod;

int solve(int n, int _MOD) {
  MOD = _MOD;
//  double st = clock() / (double)CLOCKS_PER_SEC;
  clear();
  vector<vector<int>> num(n + 1, vector<int>(n + 1));
  vector<vector<int>> sum(n + 1, vector<int>(n + 1));
  num[1][1] = 1;

  //vector<int> pw2_1(n + 1);
  //for (int i = 0; i <= n; i++) pw2_1[i] = bin(2, i);
  vector<vector<int>> pw2_1(n + 1, vector<int>(n + 1));
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      pw2_1[i][j] = bin((bin(2, i) - 1 + MOD) % MOD, j);
    }
  }

  vector<int> pw2_2(n + 1);
  for (int i = 0; i <= n; i++) pw2_2[i] = bin(2, 1LL * i * (i - 1) / 2);

  for (int vert = 1; vert < n; vert++) {
    for (int last = 1; last <= vert; last++) {
      if (num[vert][last] == 0) continue;
      for (int nw = 1; vert + nw <= n; nw++) {
        int coef = 1;
        coef = 1LL * coef * getC(n - vert, nw) % MOD;
        //coef = 1LL * coef * bin((bin(2, last) - 1 + MOD) % MOD, nw) % MOD;
        //coef = 1LL * coef * bin(2, 1LL * nw * (nw - 1) / 2) % MOD;
        //coef = 1LL * coef * bin((pw2_1[last] - 1 + MOD) % MOD, nw) % MOD;
        coef = 1LL * coef * pw2_1[last][nw] % MOD;
        coef = 1LL * coef * pw2_2[nw] % MOD;

        num[vert + nw][nw] = (num[vert + nw][nw] + 1LL * num[vert][last] * coef) % MOD;
        sum[vert + nw][nw] = (sum[vert + nw][nw] + 1LL * sum[vert][last] * coef + 1LL * num[vert][last] * coef % MOD * (n - vert)) % MOD;
      }
    }
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    ans = (ans + sum[n][i]) % MOD;
  }
  ans = 1LL * ans * inv(n - 1) % MOD;
//  cerr << clock() / (double)CLOCKS_PER_SEC - st << endl;
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  //freopen("l.out", "w", stdout);
#endif

//  cout << solve(400, 1e9 + 9) << endl;
//  return 0;

  int n;
  while (scanf("%d%d", &n, &MOD) == 2) {
    cout << solve(n, MOD) << endl;
  }

  return 0;
}
