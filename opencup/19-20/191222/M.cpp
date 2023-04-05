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

ll solve(vector<int> a, vector<int> b) {
  int n = a.size();
  ll ans = 0;
  for (int mask = 0; mask < (2 << n); mask += 2) {
    ll res = 0;
    for (int i = 1; i <= n; i++) {
      if (mask & (1 << i)) {
        res += a[i - 1];
        for (int j = 2 * i; j <= n; j += i) {
          if (mask & (1 << j)) {
            res -= b[j - 1];
          }
        }
      }
    }
    ans = max(ans, res);
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("m.in", "r", stdin);
  freopen("m.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> a(n + 1);
    vector<int> b(n + 1);
    for (int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d", &b[i]);
    }
    ll ans = a[1];
    vector<bool> used(n + 1);
    for (int i = 2; i <= n; i++) {
      if (used[i]) continue;
      vector<int> as, bs;
      for (ll j = i; j <= n; j *= i) {
        as.push_back(a[j]);
        bs.push_back(b[j]);
        assert(!used[j]);
        used[j] = true;
      }
      ans += solve(as, bs);
    }
    printf("%lld\n", ans);
  }

  return 0;
}
