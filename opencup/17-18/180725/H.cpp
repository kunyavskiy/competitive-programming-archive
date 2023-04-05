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

const int MAXN = 1e6 + 10;

typedef pair<int ,int > pii;

int n, a[MAXN];
int invv[MAXN];
int f[MAXN];
int invf[MAXN];
pii t[2 * MAXN];

int get( int l, int r ) {
  pii p(-1e9, 0);
  for (l += n, r += n; l < r; l /= 2, r /= 2) {
    if (l % 2 == 1) p = max(p, t[l++]);
    if (r % 2 == 1) p = max(p, t[--r]);
  }
  return -p.second;
}
int solve(int l, int r) {
  if (l == r) {
    return 1;
  }
  int id = get(l, r);//max_element(a + l, a + r) - a;
  int ans = 1;
  ans = mul(ans, solve(l, id));
  ans = mul(ans, solve(id + 1, r));
  ans = mul(ans, f[r - l - 1]);
  ans = mul(ans, invf[id - l]);
  ans = mul(ans, invf[r - id - 1]);
  return ans;
}

void solve() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    t[i + n] = {a[i], -i};
  }
  for (int i = n - 1; i > 0; i--)
    t[i] = max(t[2 * i], t[2 * i + 1]);

  int res = solve(0, n);
  res = mul(res, invf[n]);
  res = mul(res, n);
  res = mul(res, invv[2]);
  printf("%d\n", res);
}

int main() {
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
  while (t-->0)
    solve();
}
