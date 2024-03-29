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

int MOD = 1000000007;

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

int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
#endif

  int n;
  while (scanf("%d%d", &n, &MOD) == 2) {
    vector<int> f(n + 1);
    vector<int> invf(n + 1);

    vector<int> invv(n + 1);

    invv[1] = 1;
    for (int i = 2; i <= n; i++) {
      invv[i] = mul(MOD - invv[MOD % i], MOD / i);
      assert(mul(i, invv[i]) == 1);
    }

    f[0] = invf[0] = 1;
    for (int i = 1; i <= n; i++) {
      f[i] = mul(f[i - 1], i);
      invf[i] = mul(invf[i - 1], invv[i]);
    }

    auto cnk = [&](int n, int k) {
      if (k > n) return 0;
      return mul(f[n], mul(invf[k], invf[n - k]));
    };

    auto kely = [](int n, int k) {
      if (n == k) return 1;
      return mul(k, mpow(n, n - k - 1));
    };

    int ans = mpow(n, n - 2);
    int lim = (n + 1) / 2;
    for (int i = lim + 1; i < n; i++) {
      int cur = cnk(n - 1, i);
      cur = mul(cur, n);
      cur = mul(cur, kely(n - 1, i));
      sub(ans, cur);
    }

    printf("%d\n", ans);
  }

  return 0;
}
