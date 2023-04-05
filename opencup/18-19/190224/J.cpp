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

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<vector<ll>> a(n, vector<ll>(m, 0));
    vector<vector<ll>> b(n, vector<ll>(m, 0));
    vector<int> t(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &t[i]);
    }
    for (auto& x : a) for (ll &y : x) scanf("%lld", &y);
    for (auto& x : b) for (ll &y : x) scanf("%lld", &y);


    int bads = 0;
    for (int mask = 0; mask < (1 << m); mask++) {
      bool win = false;
      ll trumps = 0;
      ll outs = 0;
      for (int i = 0; i < n; i++) {
        ll out = 0;
        ll cnt = 0;
        for (int j = m - 1; j >= 0; j--) {
          if (mask & (1 << j)) {
            cnt -= a[i][j];
            if (cnt < 0) {
              out -= cnt;
              cnt = 0;
            }
            cnt += b[i][j];
          }
        }
        if (t[i]) {
          trumps += cnt;
        }
        if (out) {
          if (t[i]) {
            win = true;
          } else {
            outs += out;
          }
        }
      }
      if (outs > trumps) {
        win = true;
      }
      if (!win) {
        bads |= mask;
      }
    }

    ll ans = 0;

    for (int j = 0; j < m; j++) {
      if (bads & (1 << j)) continue;
      for (int i = 0; i < n; i++) {
        ans += a[i][j];
      }
    }

    printf("%lld\n", ans);
  }

  return 0;
}
