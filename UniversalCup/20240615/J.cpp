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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x)                                                           \
  eprintf("[" #x "] Time : %.3lf s.\n",                                        \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...)                                                     \
  eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__,                            \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y)                                                              \
  cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z)                                                           \
  cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y   \
       << ", " << z << ")\n"
#define dbv(a)                                                                 \
  cerr << #a << " = ";                                                         \
  for (auto xxxx : a)                                                          \
    cerr << xxxx << " ";                                                       \
  cerr << endl

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() { TIMESTAMPf("%s", what.data()); }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

const int MOD = 1000000007;

void add(int &a, int b) {
  if ((a += b) >= MOD)
    a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0)
    a += MOD;
}

int mul(int a, int b) { return (int)((a * 1LL * b) % MOD); }

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1)
      res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) { return mpow(x, MOD - 2); }
int cnk[55][55];


int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif


  cnk[0][0] = 1;
  for (int i = 0; i < 55; i++) {
    for (int j = 0; j < 55; j++) {
      if (i)
        add(cnk[i][j], cnk[i - 1][j]);
      if (i && j)
        add(cnk[i][j], cnk[i - 1][j - 1]);
    }
  }


  int n;
  scanf("%d", &n);
  vector<int> a(n);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  sort(a.rbegin(), a.rend());
  vector<int> atleast(55);
  for (int i = 0; i < 55; i++) {
    for (int x : a) {
      if (x >= i) atleast[i]++;
    }
  }

  vector<unordered_map<ll, int>> ans(55);

  auto calc = [&](auto self, int p, ll B) -> int {
    if (B < 0) return 0;
    if (B >= n * (1LL << p)) return 1;
    auto it = ans[p].find(B);
    if (it != ans[p].end()) return it->second;
    int res = 0;
    if (p != 0) {
      for (int i = 0; i <= atleast[p]; i++) {
        add(res, mul(mul(cnk[atleast[p]][i], minv((1LL << atleast[p]) % MOD)),
                     self(self, p - 1, B - i * (1LL << (p - 1)))));
      }
    } else {
      for (int i = 0; i <= n; i++) {
        if (i > B)
          break;
        int c = mul(cnk[n][i], mpow(B - i, n));
        if (i % 2 == 1) sub(res, c); else add(res, c);
      }
      for (int i = 1; i <= n; i++) {
        res = mul(res, minv(i));
      }
    }
    ans[p][B] = res;
    return res;
  };

  int res = 1;
  for (int i = 0; i < n; i++) {
    sub(res, calc(calc, 50, 1LL << a[i]));
  }

  printf("%d\n", res);

  return 0;
}
