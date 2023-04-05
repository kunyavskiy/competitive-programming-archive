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

#ifdef LOCAL
const int MAXN = 100100;
#else
const int MAXN = 10000100;
#endif

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

int f[MAXN];
int invv[MAXN];
int invf[MAXN];

int mind[MAXN];
int phi[MAXN];

void gen_primes(int n) {
  vector<int> primes;
  mind[1] = 1;
  phi[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (mind[i] == 0) {
      mind[i] = i;
      primes.push_back(i);
    }
    int x = i;
    x /= mind[i];
    phi[i] = mind[i] - 1;
    while (x % mind[i] == 0) {
      x /= mind[i];
      phi[i] *= mind[i];
    }
    phi[i] *= phi[x];
    for (int j : primes) {
      if (j > mind[i] || i * j > n) break;
      mind[i * j] = j;
    }
  }
}

int cnk(int n, int k) {
  if (n < k) return 0;
  return mul(f[n], mul(invf[k], invf[n - k]));
}

vector<int> gen_divisors(int n) {
  vector<int> d;
  d.push_back(1);

  while (n != 1) {
    int x = mind[n];
    int cnt = 0;
    while (n % x == 0) {
      cnt++;
      n /= x;
    }

    int sz = d.size();
    for (int i = 0; i < sz * cnt; i++) {
      d.push_back(d[i] * x);
    }
  }
  return d;
}

int splits(int n, int m) {
  if (m > n) return 0;
  return cnk(n - 1, m - 1);
}

int solve_big(int n, int m) {
  int big = (n + 1) / 2;
  n -= big - 1;

  int ans = splits(n, m);

  if (m % 2 == 1) {
    for (int o1 = 0; o1 < 2; o1++) {
      if ((n + o1) % 2 == 0) {
        add(ans, splits((n + o1) / 2, m / 2 + 1));
      }
    }
  } else {
    for (int o1 = 0; o1 < 2; o1++) {
      for (int o2 = 0; o2 < 2; o2++) {
        if ((n + o1 + o2) % 2 == 0) {
          add(ans, splits((n + o1 + o2) / 2, m / 2 + 1));
        }
      }
    }
  }

  return mul(ans, minv(2));
}

int solve_stupid(int n, int m) {
  set<vector<int>> s;
  vector<int> cur;

  auto canon = [](vector<int> v) {
    vector<int> ans = v;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < (int)v.size(); j++) {
        rotate(v.begin(), v.begin() + 1, v.end());
        ans = min(ans, v);
      }
      reverse(v.begin(), v.end());
    }
    return ans;
  };

  function<void(int, int)> go = [&](int x, int y) {
    if (x < y) return;
    if (x == 0) {
      s.insert(canon(cur));
      return;
    }
    if (y == 0) return;
    for (int i = 1; i <= x && 2 * i < n; i++) {
      cur.push_back(i);
      go(x - i, y - 1);
      cur.pop_back();
    }
  };

  go(n, m);
  return s.size();
}

void solve(int n, int m) {

  int ans = 0;

  if (n % 2 == 1) {
    // sym, 1 stable point
    add(ans, mul(n, cnk(n / 2, m / 2)));
  } else {
    if (m % 2 == 0) {
      // sym, 0 stable points
      add(ans, mul(n / 2, cnk(n / 2, m / 2)));
      // sym, 2 stable points
      add(ans, mul(n / 2, cnk(n / 2 - 1, m / 2 - 1)));
      add(ans, mul(n / 2, cnk(n / 2 - 1, m / 2)));
    } else {
      // sym, 2 stable points
      add(ans, mul(n / 2 * 2, cnk(n / 2 - 1, m / 2)));
    }
  }

  vector<int> divisors = gen_divisors(n);
  for (int d : divisors) {
    int cnt = phi[d];
    if (m % d == 0) {
      add(ans, mul(cnt, cnk(n / d, m / d)));
    }
  }

  ans = mul(ans, minv(2 * n));
  eprintf("ans before = %d\n", ans);
  sub(ans, solve_big(n, m));
#ifdef LOCAL
  int ans2 = solve_stupid(n, m);
  if (ans != ans2) {
    eprintf("%d %d %d %d\n", n, m, ans, ans2);
    assert(0);
  }
#endif
  printf("%d\n", ans);
}

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  gen_primes(MAXN);

  invv[1] = 1;
  for (int i = 2; i < MAXN; i++) {
    invv[i] = mul(MOD - invv[MOD % i], MOD / i);
    assert(mul(i, invv[i]) == 1);
  }

  f[0] = invf[0] = 1;
  for (int i = 1; i < MAXN; i++) {
    f[i] = mul(f[i - 1], i);
    invf[i] = mul(invf[i - 1], invv[i]);
  }


  int t;
  scanf("%d", &t);
  while (t-->0) {
    int n, m;
    scanf("%d%d", &n, &m);
    solve(n, m);
  }

#ifdef LOCAL
  for (int i = 3; i <= 10; i++) {
    for (int j = 3; j <= i; j++) {
      solve(i, j);
    }
  }
#endif

  return 0;
}
