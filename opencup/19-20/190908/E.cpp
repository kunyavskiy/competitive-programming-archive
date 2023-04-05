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

struct item {
  __uint128_t mask;
  __uint128_t cons;
  int w;
  int bit;
};

__uint128_t bit(int x) {
  return __uint128_t(1) << x;
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n, q;

  while (scanf("%d%d", &n, &q) == 2) {
    vector<item> items;
    ll ans = 0;
    for (int _ = 0; _ < q; _++) {
      int u, v, w;
      ll a;
      scanf("%d%d%lld%d", &u, &v, &a, &w);
      --u, --v;
      __uint128_t mask = (__uint128_t(a) << n) | bit(u) | bit(v);
      __uint128_t cons = bit(items.size());
      for (int i = 0; i < (int)items.size(); i++) {
        if (mask & bit(items[i].bit)) {
          mask ^= items[i].mask;
          cons ^= items[i].cons;
        }
      }
      if (mask) {
        int b = 0;
        for (int i = 0;; i++) {
          if (mask & bit(i)) {
            b = i;
            break;
          }
        }
        for (auto &x : items) {
          if (x.mask & bit(b)) {
            x.mask ^= mask;
            assert(x.mask);
            x.cons ^= cons;
          }
        }
        items.push_back({mask, cons, w, b});
        ans += w;
      } else {
        int to_change = -1;
        for (int i = 0; i < (int)items.size(); i++) {
          if ((cons & bit(i)) && items[i].w < w) {
            if (to_change == -1 || items[to_change].w > items[i].w) {
              to_change = i;
            }
          }
        }
        if (to_change != -1) {
          ans += w - items[to_change].w;
          cons ^= bit(to_change) ^ bit(items.size());
          for (auto &item : items) {
            if (item.cons & bit(to_change)) {
              item.cons ^= cons;
            }
          }
          items[to_change].w = w;
        }
      }
      printf("%lld\n", ans);
    }
  }


  return 0;
}
