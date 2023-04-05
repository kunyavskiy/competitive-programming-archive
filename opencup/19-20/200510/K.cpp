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

int solve() {
  int n, x;
  scanf("%d%d", &n, &x);
  vector<int> p(n);
  vector<vector<int>> sons(n);
  vector<int> d(n);
  vector<int> rx(n);
  vector<int> cx(n);
  vector<int> cp(n);
  vector<int> cip(n);

  for (int i = 0; i < n; i++) {
    rx[i] = cx[i] = 1;
    scanf("%d", &d[i]);
    sub(d[i], x);
  }
  for (int i = 1; i < n; i++) {
    scanf("%d%d%d", &p[i], &cp[i], &cip[i]);
    sub(cip[i], x);
    sub(cp[i], x);
    --p[i];
    sons[p[i]].push_back(i);
  }

  int swaps = 1;
  for (int it = 0; it < 2; it++) {
    for (int i = n - 1; i > 0; i--) {
      if (d[i] == 0) {
        if (cip[i] == 0) {
          continue;
        }
        int inv = minv(cip[i]);
        for (int son : sons[p[i]]) {
          if (son < i) {
            int coef = mul(cip[son], inv);
            sub(cip[son], mul(coef, cip[i]));
            assert(cip[son] == 0);
            sub(cx[son], mul(coef, cx[i]));
          }
        }
        if (p[i] != 0) {
          int coef = mul(cp[p[i]], inv);
          sub(cp[p[i]], mul(coef, cip[i]));
          assert(cp[p[i]] == 0);
          sub(cx[p[p[i]]], mul(coef, cx[i]));
        }
        swap(rx[i], rx[p[i]]);
        swap(d[p[i]], cp[i]);
        swap(d[i], cip[i]);
        swaps = -swaps;
      }
      {
        int coef = mul(cip[i], minv(d[i]));
        sub(rx[p[i]], mul(rx[i], coef));
        sub(d[p[i]], mul(cp[i], coef));
        sub(cip[i], mul(d[i], coef));
      }
      {
        int coef = mul(cp[i], minv(d[i]));
        sub(cx[p[i]], mul(cx[i], coef));
        sub(cp[i], mul(d[i], coef));
      }
      assert(cip[i] == 0);
    }

    for (int i = n - 1; i > 0; i--) {
      if (cp[i] != 0) {
        assert(d[i] == 0);
        if (d[p[i]] == 0) {
          return 0;
        }
        int coef = mul(cp[i], minv(d[p[i]]));
        sub(rx[i], mul(rx[p[i]], coef));
        sub(cp[i], mul(d[p[i]], coef));
        assert(cp[i] == 0);
      }
    }

    if (it == 0) {
      for (int i = 1; i < n; i++) {
        int coef = mul(rx[i], minv(rx[0]));
        sub(rx[i], mul(rx[0], coef));
        sub(d[i], mul(mul(x, mul(rx[0], cx[0])), coef));
        sub(cp[i], mul(d[0], coef));
        p[i] = 0;
        cip[i] = mul(cx[0], mul(rx[0], x));
      }
      add(d[0], mul(mul(rx[0], cx[0]), x));
      cx[0] = 0;
    }
  }

  int ans = swaps == 1 ? 1 : (MOD - 1);
  for (int i = 0; i < n; i++) {
    ans = mul(ans, d[i]);
  }

  return ans;
}

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    printf("%d\n", solve());
  }

  return 0;
}
