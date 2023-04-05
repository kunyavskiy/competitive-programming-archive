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

constexpr int MOD = 998244353;

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

struct item {
  int c0;
//  int c1;

  friend item operator+(item a, const item &b) {
    add(a.c0, b.c0);
//    add(a.c1, b.c1);
    return a;
  }
  friend item operator*(const item &a, const item &b) {
    return item{mul(a.c0, b.c0)};
    /*item res{0, 0};
    add(res.c0, mul(a.c0, b.c0));
    add(res.c0, mul(3, mul(a.c1, b.c1)));

    add(res.c1, mul(a.c1, b.c0));
    add(res.c1, mul(a.c0, b.c1));
    return res;*/
  }

  friend item operator^(item a, ll deg) {
    item res{1};
    while (deg) {
      if (deg & 1) res = res * a;
      a = a * a;
      deg /= 2;
    }
    return res;
  }
  bool operator==(const item &rhs) const {
    return std::tie(c0) == std::tie(rhs.c0);
  }
  bool operator!=(const item &rhs) const {
    return !(rhs == *this);
  }
};

void fft(const item &g, item& a0, item &a1, item &a2, item& a3, item &a4, item &a5, item& a6) {
  item values[7]{a0, a1, a2, a3, a4, a5, a6};
  item res[7]{};

  item base{1};
  for (auto &a : res) {
    for (int j = 6; j >= 0; j--) {
      a = a * base + values[j];
    }
    base = base * g;
  }


  a0 = res[0];
  a1 = res[1];
  a2 = res[2];
  a3 = res[3];
  a4 = res[4];
  a5 = res[5];
  a6 = res[6];
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  item g{1};

  constexpr long long size = MOD;
  static_assert(size % 7 == 1);

  do {
    g.c0++;
  } while ((g ^ ((size - 1) / 7)) == item{1});

  g = g ^ ((size - 1) / 7);
  item ONE{1};
  assert((g ^ 7) == ONE);

  const int D = 7;
  const int S = 7 * 7 * 7 * 7 * 7 * 7 * 7;
  vector<int> d7(D);
  d7[0] = 1;
  for (int i = 1; i < D; i++) {
    d7[i] = d7[i - 1] * 7;
  }


  vector<item> dp(S);
  int n;
  long long k;
  scanf("%d%lld", &n, &k);
  for (int i = 0; i < n; i++) {
    int a;
    scanf("%d", &a);
    int b = 0;
    for (int j = 0; j < D; j++) {
      if (a & (1 << j)) {
        b += d7[j];
      }
    }
    dp[b] = ONE;
  }

  for (int i = 0; i < D; i++) {
    for (int j = 0; j < S; j++) {
      if (j / d7[i] % 7 == 0) {
        fft(g,
            dp[j + 0 * d7[i]], dp[j + 1 * d7[i]], dp[j + 2 * d7[i]],
            dp[j + 3 * d7[i]], dp[j + 4 * d7[i]], dp[j + 5 * d7[i]],
            dp[j + 6 * d7[i]]);
      }
    }
  }

  for (auto &x : dp) {
    x = x ^ k;
  }

  auto g_inv = g ^ (MOD * 1LL * MOD - 2);
  assert(g_inv * g == ONE);

  item inv7{minv(7)};

  for (int i = 0; i < D; i++) {
    for (int j = 0; j < S; j++) {
      if (j / d7[i] % 7 == 0) {
        fft(g_inv,
            dp[j + 0 * d7[i]], dp[j + 1 * d7[i]], dp[j + 2 * d7[i]],
            dp[j + 3 * d7[i]], dp[j + 4 * d7[i]], dp[j + 5 * d7[i]],
            dp[j + 6 * d7[i]]);
        for (int t = 0; t < 7; t++) {
          dp[j + t * d7[i]] = dp[j + t * d7[i]] * inv7;
        }
      }
    }
  }

  printf("%d\n", dp[0].c0);
  return 0;
}
