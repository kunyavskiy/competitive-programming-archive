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

void solve() {
  int n;
  scanf("%d", &n);
  vector<int> a(n), b(n), c(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d%d", &a[i], &b[i], &c[i]);
  }

  int maxd = 0;
  int maxtot = 0;

  vector<vector<ll>> dp(1, vector<ll>(1, 0));
  for (int i = n - 1; i >= 0; i--) {
    int nmaxd = maxd + 1;
    int nmaxtot = maxtot + maxd + 1;

    vector<vector<ll>> ndp(nmaxd + 1, vector<ll>(nmaxtot + 1, 0));

    for (int x = 0; x <= maxd; x++) {
      for (int y = 0; y <= maxtot; y++) {
        ndp[x + 1][y + x + 1] = max(ndp[x + 1][y + x + 1], dp[x][y] + a[i]);
        ndp[x][y + x] = max(ndp[x][y + x], dp[x][y] + b[i] * 1LL * y);
        ndp[x][y + x] = max(ndp[x][y + x], dp[x][y] + c[i] * 1LL * x);
      }
    }

    dp = ndp;
    maxd = nmaxd;
    maxtot = nmaxtot;
  }

  ll ans = 0;

  for (const auto& x : dp) {
    ans = max(ans, *max_element(x.begin(), x.end()));
  }

  printf("%lld\n", ans);
}

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    solve();
  }

  return 0;
}
