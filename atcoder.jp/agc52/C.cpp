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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

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

bool is_good(vector<int> v, int p) {
  sort(v.begin(), v.end());
  do {
    bool ok = true;
    int sum = 0;
    for (int x : v) {
      sum += x;
      if (sum % p == 0) ok = false;
    }
    if (ok) return true;
  } while (next_permutation(v.begin(), v.end()));
  return false;
}

int bads = 0;

void check_all(int n, int p, vector<int> &v) {
  if ((int)v.size() == n) {
    if (!is_good(v, p)) {
      bads++;
      /*if (accumulate(v.begin(), v.end(), 0) % p == 0) {
        return;
      }
      for (int x : v) {
        eprintf("%d ", x);
      }
      eprintf("\n");*/
    }
    return;
  }
  v.push_back(1);
  while (v.back() < p) {
    check_all(n, p, v);
    v.back()++;
  }
  v.pop_back();
}

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

int minv(int x) {
  return mpow(x, MOD - 2);
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, p;
  while (scanf("%d%d", &n, &p) == 2) {
    int ans = mpow(p - 1, n);
    {
      int cntz = 1, cntnz = 0;
      for (int i = 0; i < n; i++) {
        int ncntz = cntnz;
        int ncntnz = mul(cntz, p - 1);
        add(ncntnz, mul(cntnz, p - 2));
        cntz = ncntz;
        cntnz = ncntnz;
      }
      sub(ans, cntz);
    }

    vector<int> fs(2 * n + 1);
    vector<int> ifs(2 * n + 1);
    fs[0] = ifs[0] = 1;
    for (int i = 1; i < (int)fs.size(); i++) {
      fs[i] = mul(fs[i - 1], i);
      ifs[i] = minv(fs[i]);
    }
    auto cnk = [&](int n, int k) {
      assert(0 <= k && k <= n && n < (int) fs.size());
      return mul(fs[n], mul(ifs[k], ifs[n - k]));
    };
    vector<vector<int>> splits_dp;
    if (p - 2 < n) {
      splits_dp = vector<vector<int>>(n + 1, vector<int>(n + 1));
      splits_dp[0][0] = 1;
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          int from = j + 1;
          int to = min(n + 1, j + p - 1);
          if (from < to) {
            add(splits_dp[i + 1][from], splits_dp[i][j]);
            if (to < n + 1) {
              sub(splits_dp[i + 1][to], splits_dp[i][j]);
            }
          }
        }
        for (int j = 1; j <= n; j++) {
          add(splits_dp[i + 1][j], splits_dp[i + 1][j - 1]);
        }
      }
    }
    auto splits = [&](int sum, int cnt) {
      if (cnt == 0) {
        return sum ? 0 : 1;
      }
      if (p - 2 >= sum) {
        if (sum < cnt) return 0;
        return cnk(sum - 1, cnt - 1);
      }
      return splits_dp[cnt][sum];
    };
    for (int cnt = (n + 1) / 2; cnt <= n; cnt++) {
      for (int sum_other = 0; sum_other < (cnt - p); sum_other++) {
        if ((cnt - sum_other) % p == 0) continue;
        int cur = cnk(n, cnt);
        cur = mul(cur, p - 1);
        cur = mul(cur, splits(sum_other, n - cnt));
        sub(ans, cur);
      }
    }
    printf("%d\n", ans);
#ifdef LOCAL
    bads = 0;
    if (0 && pow(p - 1, n) <= 1e8) {
      vector<int> v;
      check_all(n, p, v);
      int ans2 = mpow(p - 1, n);
      sub(ans2, bads);
      if (ans != ans2) {
        eprintf("%d != %d: %d %d\n", ans, ans2, p, n);
        assert(0);
      } else {
        eprintf("%d == %d: %d %d\n", ans, ans2, p, n);
      }
    }
#endif
  }




  return 0;
}
