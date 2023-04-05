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

int mpow(int a, ll b) {
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

int get_split(ll n, int not_empty, int maybe_empty) {
  int ans = 0;
  int all = (1 << not_empty) - 1;
  for (int i = 0; i < (1 << not_empty); i++) {
    ll cur = mpow(__builtin_popcount(i) + maybe_empty, n);
    if (__builtin_parity(all ^ i)) {
      sub(ans, cur);
    } else {
      add(ans, cur);
    }
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);

  vector<map<int, int>> ans(7);
  for (int m = 2; m <= 6; m++) {
    vector<vector<int>> idx(m, vector<int>(m, -1));
    int es = 0;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < m; j++) {
        if (j != 0 && i != m - 1 && i != j) {
          idx[i][j] = es++;
        }
      }
    }

    int always = 1 << idx[0][m - 1];
    for (int i = 1; i < m - 1; i++) {
      always |= 1 << idx[0][i];
      always |= 1 << idx[i][m - 1];
    }

    auto have = [&](int mask, int i, int j) {
      return idx[i][j] != -1 && ((mask & (1 << idx[i][j])) != 0);
    };

    auto check_mask = [&](int mask) {
      if (!have(mask, 0, m - 1)) return false;
      for (int i = 1; i < m - 1; i++) {
        if (!have(mask, 0, i) || !have(mask, i, m - 1)) {
          return false;
        }
      }
      for (int i = 1; i < m - 1; i++) {
        for (int j = 1; j < m - 1; j++) {
          if (i == j) continue;
          if (have(mask, i, j) && have(mask, j, i)) {
            return false;
          }
          for (int k = 1; k < m - 1; k++) {
            if (i == k || j == k) continue;
            if (have(mask, i, j) && have(mask, j, k) && !have(mask, i, k)) {
              return false;
            }
          }
        }
      }
      return true;
    };

    for (int mask = always; mask < (1 << es); mask = ((mask + 1) | always)) {
      if (!check_mask(mask)) continue;
      int normed_mask = mask;
      for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
          if (i == j) continue;
          for (int k = 0; k < m; k++) {
            if (i == k || j == k) continue;
            if (have(mask, i, j) && have(mask, j, k)) {
              normed_mask &= ~(1 << idx[i][k]);
            }
          }
        }
      }

      bool failed = false;

      for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
          if (i == j) continue;
          if (!have(mask, i, j) && !have(mask, j, i)) {
            int ok = 0;
            for (int k = 0; k < m; k++) {
              if (have(normed_mask, k, i) && have(normed_mask, k, j)) {
                ok++;
              }
            }
            if (ok != 1) {
              failed = true;
            }
            ok = 0;
            for (int k = 0; k < m; k++) {
              if (have(normed_mask, i, k) && have(normed_mask, j, k)) {
                ok++;
              }
            }
            if (ok != 1) {
              failed = true;
            }
          }
        }
      }

      if (failed) continue;

      vector<int> degs(m + 1);
      for (int i = 0; i < m; i++) {
        int deg = 0;
        for (int j = 0; j < m; j++) {
          if (have(normed_mask, i, j)) {
            deg++;
          }
        }
        degs[deg]++;
      }

      if (degs[0] + degs[1] + degs[2] != m) {
        continue;
      }
      //      eprintf("===== mask = %d\n", mask);
      //      dump(mask);
      //      dump(normed_mask);

      assert(degs[0] == 1);

      ans[m][degs[1]]++;
    }
    if (m == 6) {
      ans[m][3] += 24;
    }
  }

  while (t-->0) {
    ll n; int m;
    scanf("%lld%d", &n, &m);

    int res = 0;
    for (auto [k, cnt] : ans[m]) {
      add(res, mul(cnt, get_split(n, k, 0)));
    }
    res = mul(res, m);
    res = mul(res, m - 1);

    printf("%d\n", res);
  }

  return 0;
}
