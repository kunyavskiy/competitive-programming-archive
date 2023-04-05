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

namespace mod {
  typedef long long ll;
  const int MOD = 998244353;

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
}
using namespace mod;

vector<int> gauss(vector<vector<int>> a) {
  int n = a.size();
  int m = a[0].size() - 1;
  vector<int> wh(m, -1);
  for (int col = 0, row = 0; col < m && row < n; col++) {
    int id = -1;
    for (int i = row; i < n; i++) {
      if (a[i][col] != 0) {
        id = i;
        break;
      }
    }
    if (id == -1) {
      if (a[row][m] != 0) return vector<int>();
      continue;
    }
    swap(a[row], a[id]);
    wh[col] = row;

    int x = inv(a[row][col]);
    for (int j = 0; j <= m; j++) {
      a[row][j] = mul(a[row][j], x);
    }

    for (int i = 0; i < n; i++) {
      if (i == row) continue;
      int coef = a[i][col];
      for (int j = 0; j <= m; j++) {
        add(a[i][j], -1LL * coef * a[row][j] % MOD + MOD);
      }
    }
    row++;
  }
  for (int i = 0; i < n; i++) {
    bool fail = 1;
    for (int j = 0; j < m; j++) fail &= a[i][j] == 0;
    fail &= a[i][m] != 0;
    if (fail) return vector<int>();
  }
  vector<int> ans(m, -1);
  for (int i = 0; i < m; i++) {
    if (wh[i] != -1) {
      ans[i] = a[wh[i]][m];
    }
  }
  return ans;
}

namespace linear_rec_coef {
  // O(n^3)
  vector<int> find_gauss(vector<int> s) {
    int m = s.size() / 2;
    int n = s.size() - m;
    vector<vector<int>> a(n, vector<int>(m + 1));
    for (int i = 0; i < n; i++) {
      a[i][m] = s[m + i];
      for (int j = 0; j < m; j++) {
        a[i][j] = s[m + i - 1 - j];
      }
    }
    auto res = gauss(a);
    assert(res.size() > 0);
    return res;
  }


  vector<int> find_berlekamp(vector<int> s) {
    int l = 0;
    vector<int> la(1, 1);
    vector<int> b(1, 1);
    for (int r = 1; r <= (int)s.size(); r++) {
      int delta = 0;
      for (int j = 0; j <= l; j++) {
        delta = (delta + 1LL * s[r - 1 - j] * la[j]) % MOD;
      }
      b.insert(b.begin(), 0);
      if (delta != 0) {
        vector<int> t(max(la.size(), b.size()));
        for (int i = 0; i < (int)t.size(); i++) {
          if (i < (int)la.size()) t[i] = (t[i] + la[i]) % MOD;
          if (i < (int)b.size()) t[i] = (t[i] - 1LL * delta * b[i] % MOD + MOD) % MOD;
        }
        if (2 * l <= r - 1) {
          b = la;
          int od = inv(delta);
          for (int &x : b) x = 1LL * x * od % MOD;
          l = r - l;
        }
        la = t;
      }
    }
    assert((int)la.size() == l + 1);
    la.erase(la.begin());
    for (int &x : la) x = (MOD - x) % MOD;
    //assert(la.size() * 2 <= s.size());
    return la;
  }
}


void solve(int n, vector<pair<int, int>> a) {
  n = 400;
  vector<vector<int>> b(n, vector<int>(n));

  int prob = inv(a.size());

  b[0][0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (auto o : a) {
        int x = i + o.first, y = j + o.second;
        if (x >= n || y >= n) continue;
        b[x][y] = (b[x][y] + 1LL * b[i][j] * prob) % MOD;
      }
    }
  }

  vector<int> v;
  for (int i = 0; i < n; i++) v.push_back(b[i][i]);

  auto r = linear_rec_coef::find_berlekamp(v);

  cerr << r.size() << endl;
}

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int n, k;
  while (scanf("%d%d", &n, &k) == 2) {
    vector<pair<int, int>> a;
    for (int i = 0; i < k; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      if (x + y > 0) a.push_back({x, y});
    }

    solve(n, a);
  }

  return 0;
}
