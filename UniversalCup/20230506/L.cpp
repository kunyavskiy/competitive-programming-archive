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

int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
#endif

  int n, q;
  while (scanf("%d%d", &n, &q) == 2) {
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
      scanf("%lld", &a[i]);
    }
    vector<vector<pair<int, ll>>> nxt(n);
    vector<pair<int, ll>> cur;
    for (int i = n - 1; i >= 0; i--) {
      cur.emplace(cur.begin(), i + 1, a[i]);
      for (auto &c : cur) {
        c.second = __gcd(c.second, a[i]);
      }
      int ptr = 0;
      for (int j = 1; j < (int)cur.size(); j++) {
        if (cur[j].second != cur[ptr].second) {
          ptr++;
        }
        cur[ptr] = cur[j];
      }
      cur.resize(ptr + 1);
      nxt[i] = cur;
    }

    auto get = [&](auto get, int l, int r, ll curg, int k) -> ll {
      if (l >= r) return curg;
      if (k == 0) {
        for (auto [pos, g] : nxt[l]) {
          if (pos >= r) return __gcd(curg, g);
        }
        assert(false);
      } else {
        ll ans = get(get, l + 1, r, curg, k - 1);
        for (auto [pos, g] : nxt[l]) {
          ans = max(ans, get(get, pos + 1, r, __gcd(curg, g), k - 1));
        }
        return ans;
      }
    };

    for (int i = 0; i < q; i++) {
      int l, r, k;
      scanf("%d%d%d", &l, &r, &k);
      printf("%lld\n", get(get, l - 1, r, 0, k));
    }

  }
  return 0;
}
