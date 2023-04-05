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
const int N = 105;
const ll INF = 8e18;

ll dp[N][N * 2][N * 2];

void upd(ll &x, ll y) {
  x = min(x, y);
}

ll sum(ll n) {
  return n * (n + 1) / 2;
}

ll sum(ll l, ll r) {
  return sum(r) - sum(l - 1);
}

ll solve(ll h1, ll h2, ll h3, ll a1, ll a2, ll a3) {
//  for (int i = 0; i < N; i++) for (int j = 0; j < N * 2; j++) for (int k = 0; k < N * 2; k++) dp[i][j][k] = INF;
  memset(dp, 63, sizeof(dp));

  dp[0][0][0] = 0;
  for (int i = 0; i < N - 1; i++) {
    for (int d1 = 0; d1 < N * 2; d1++) {
      for (int d2 = 0; d2 < N * 2; d2++) {
        if (dp[i][d1][d2] > 4e18) continue;

        ll d3 = 1LL * i * (i + 1) / 2 - d1 - d2;

        int alive1 = d1 < h1;
        int alive2 = d2 < h2;
        int alive3 = d3 < h3;

        ll cost = dp[i][d1][d2];
        cost += alive1 * a1 + alive2 * a2 + alive3 * a3;

        upd(dp[i + 1][min(d1 + i + 1LL, 2LL * N - 1)][d2], cost);
        upd(dp[i + 1][d1][min(d2 + i + 1LL, 2LL * N - 1)], cost);
        upd(dp[i + 1][d1][d2], cost);
      }
    }
  }

  vector<ll> aa({a1, a2, a3});

  ll ans = INF;
  int i = N - 1;
  for (int d1 = 0; d1 < N * 2; d1++) {
    for (int d2 = 0; d2 < N * 2; d2++) {
      if (dp[i][d1][d2] > 4e18) continue;

      ll d3 = 1LL * i * (i + 1) / 2 - d1 - d2;

      vector<ll> left(3);
      left[0] = h1 - d1;
      left[1] = h2 - d2;
      left[2] = h3 - d3;

      vector<int> p(3);
      for (int j = 0; j < 3; j++) p[j] = j;

      do {
        ll curcost = dp[i][d1][d2];

        ll attack = a1 + a2 + a3;
        ll curtime = i;
        for (int j = 0; j < 3; j++) {
          ll L = curtime - 1;
          ll R = 2e9;
          if (left[p[j]] < i) {
            R = curtime;
            if (left[p[j]] > 0) R++;
          } else {
            while (R - L > 1) {
              ll M = (L + R) >> 1;
              ll damage = sum(curtime + 1, M);
              if (damage >= left[p[j]]) {
                R = M;
              } else {
                L = M;
              }
            }
          }
          curcost += attack * (R - curtime);
          attack -= aa[p[j]];
          curtime = R;
        }
        ans = min(ans, curcost);
      } while (next_permutation(p.begin(), p.end()));
    }
  }
  return ans;
}

void test() {
  for (int i = 0; i < 50; i++) {
    cout << solve(100, 100, 1e18, 1e9, 1e9, 1e9) << endl;
  }
  exit(0);
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
//  freopen("f.out", "w", stdout);
#endif
//  test();

  int T;
  scanf("%d", &T);
  while (T--) {
    ll h1, h2, h3, a1, a2, a3;
    scanf("%lld%lld%lld%lld%lld%lld", &h1, &h2, &h3, &a1, &a2, &a3);

    printf("%lld\n", solve(h1, h2, h3, a1, a2, a3));
  }

  return 0;
}
