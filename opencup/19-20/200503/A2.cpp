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

typedef unsigned long long ll;
typedef long double ld;

ll big_bit(ll x) {
  return 1ull << (63u - __builtin_clzll(x));
}

void solve() {
  ll v = 0;
  int n, m;
  scanf("%d%d", &n, &m);
  auto read_vector = [&] (int n){
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
      ll x, y;
      scanf("%llu%llu", &x, &y);
      v ^= x;
      a[i] = x ^ y;
    }
    return a;
  };
  vector<ll> a = read_vector(n);
  vector<ll> b = read_vector(m);

  ll ans = 0;
  for (int i = 0; i < (1 << a.size()); i++) {
    ll cur_ans = numeric_limits<ll>::max();
    ll cur_v = v;
    for (int k = 0; k < n; k++) {
      if (i & (1 << k)) {
        cur_v ^= a[k];
      }
    }
    for (int j = 0; j < (1 << b.size()); j++) {
      ll cur_cur_v = cur_v;
      for (int k = 0; k < m; k++) {
        if (j & (1 << k)) {
          cur_cur_v ^= b[k];
        }
      }
      cur_ans = min(cur_ans, cur_cur_v);
    }
    ans = max(ans, cur_ans);
  }

  printf("%llu\n", ans);
}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    solve();
  }

  return 0;
}
