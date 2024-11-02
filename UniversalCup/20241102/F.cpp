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
#include <numeric>
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

ld solve_n3(vector<int> a, int m) {
  int n = a.size();
  vector<vector<ld>> dp(m + 1, vector<ld>(n + 1, 1e100));
  vector<ll> sum(n + 1);
  for (int i = 0; i < n; i++) {
    sum[i + 1] = sum[i] + a[i];
  }
  dp[0][0] = 0;
  for (int cnt = 1; cnt <= m; cnt++) {
    for (int p = 0; p <= n; p++) {
      for (int split = 0; split < p; split++) {
        dp[cnt][p] = min(dp[cnt][p], dp[cnt - 1][split] + sqrt((sum[p] - sum[split]) * (p - split)));
      }
    }
  }
  return dp[m][n];
}

using item = pair<ld, int>;
item operator+(const item& a, const item& b) {
  return {a.first + b.first, a.second + b.second};
}

template<typename T>
item magic(int N, T w) {
  vector<item> dp(N+1); dp[0] = {0, 0};

  vector<pair<int, int> > v; // start pos, best-k
  v.push_back(make_pair(0, 0));

  for (int x=1; x <= N; x++) {
    // Find the value of dp[x]
    int k = (--lower_bound(v.begin(), v.end(), make_pair(x+1, 0)))->second;
    dp[x] = dp[k] + w(k, x);

    // Update the segments
    for (int i = v.size()-1; i >= 0; i--) {
      int y = v[i].first, oldk = v[i].second;
      // Case 1
      if (y > x && dp[x] + w(x, y) < dp[oldk] + w(oldk, y))
        v.pop_back();
      // Case 2
      else {
        int lo = y+1, hi = N+1;
        while(lo < hi) {
          int mid = (lo+hi)/2;
          if (dp[x] + w(x, mid) <= dp[oldk] + w(oldk, mid))
            hi = mid;
          else
            lo = mid+1;
        }
        if (hi != N+1) v.push_back(make_pair(hi, x));
        break;
      }
    }
    if (v.size() == 0)
      v.push_back(make_pair(0, x));
  }
  return dp[N];
}



ld solve_n2log(vector<int> a, int m) {
  int n = a.size();
  vector<ll> sum(n + 1);
  for (int i = 0; i < n; i++) {
    sum[i + 1] = sum[i] + a[i];
  }
  ld l = -1e10, r = 1e10;
  ld ans = -1.0;
  for (int it = 0; it < 100; it++) {
    ld lambda = (l + r) / 2;
    auto w = [&](int split, int p) {
      return pair{sqrt((sum[p] - sum[split]) * (p - split)) - lambda, 1};
    };
    item res = magic(n, w);
    ans = res.first + lambda * m;
    if (res.second < m) {
      l = lambda;
    } else {
      r = lambda;
    }
  }
  return ans;
}

ld solve(vector<int> a, int m) {
#ifdef LOCAL
  ld res3 = solve_n3(a, m);
#endif
  ld res = solve_n2log(a, m);
#ifdef LOCAL
  assert(abs(res - res3) < 1e-9);
#endif
  return res;
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<int> a(n);
    for (int& x : a) scanf("%d", &x);
    sort(a.begin(), a.end());
    printf("%.10lf\n", (double)solve(a, m));
  }

  return 0;
}
