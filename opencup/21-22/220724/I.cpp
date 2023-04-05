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
#include <numeric>
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

struct item {
  int w, c, id;
};

struct BIT {
  int n;
  vector<long long> v;
  long long total = 0;
  explicit BIT(int n) : n(n), v(n) {}
  void add(int x, long long val) {
    eprintf("%p: %d %+lld\n", this, x, val);
    total += val;
    while (x < n) {
      v[x] += val;
      x = x | (x + 1);
    }
  }
  long long get(int x) {
    long long ans = 0;
    while (x >= 0) {
      ans += v[x];
      x = (x & (x + 1)) - 1;
    }
    return ans;
  }
};

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  vector<item> v(n + m + 1);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &v[i].c);
  }
  for (int i = 0; i <= n; i++) {
    if (i != 0) {
      scanf("%d", &v[i].w);
    } else {
      scanf("%*d");
    }
  }
  for (int i = 0; i <= n; i++) {
    if (i == 0) {
      scanf("%d", &v[i].w);
    } else {
      scanf("%*d");
    }
  }
  vector<int> cur_id(n + 1);
  std::iota(cur_id.begin(), cur_id.end(), 0);
  vector<int> disabled(m);
  for (int i = 0; i < m; i++) {
    int ty, x;
    scanf("%d%d", &ty, &x);
    int nid = n + i + 1;
    v[nid] = v[cur_id[x]];
    if (ty == 1) {
      int l, r;
      scanf("%d%d", &l, &r);
      int w = (x == 0) ? r : l;
      v[nid].w = w;
    } else {
      int c;
      scanf("%d", &c);
      v[nid].c = c;
    }
    disabled[i] = cur_id[x];
    cur_id[x] = nid;
  }
  for (int i = 0; i < (int) v.size(); i++) {
    v[i].id = i;
  }
  sort(v.begin(), v.end(), [](const item &a, const item &b) { return a.c < b.c; });
  BIT ws(v.size()), cs(v.size());
  vector<int> rid(v.size());
  auto add = [&](int i, int cf) {
    ws.add(i, cf * v[i].w);
    cs.add(i, cf * 1LL * v[i].w * 1LL * v[i].c);
  };
  for (int i = 0; i < (int) v.size(); i++) {
    if (v[i].id <= n) {
      add(i, 1);
    }
    rid[v[i].id] = i;
  }

  long long w0 = v[rid[0]].w;
  int cur0id = 0;
  auto solve = [&] {
    int l = 0;
    int r = v.size() - 1;
    while (r - l > 1) {
      int mid = (l + r) / 2;
      long long cb = cs.total - cs.get(mid);
      long long wb = ws.total - ws.get(mid);
      if ((cb + 0) > v[mid].c * (wb + w0)) {
        l = mid;
      } else {
        r = mid;
      }
    }
    long long cb = cs.total - cs.get(l);
    long long wb = ws.total - ws.get(l);
    long long num = cb + 0;
    long long den = wb + w0;
    eprintf("r = %d, %lld/%lld, [%lld, %lld, %lld, %lld]\n", r, num, den, wb, cb, w0, 0LL);
    if (den == 0) {
      assert(num == 0);
      den = 1;
    }
    long long g = __gcd(num, den);
    printf("%lld/%lld\n", num / g, den / g);
  };

  solve();
  for (int i = 0; i < m; i++) {
    add(rid[disabled[i]], -1);
    int enabled = rid[i + n + 1];
    add(enabled, 1);
    if (disabled[i] == cur0id) {
      w0 = v[enabled].w;
      cur0id = i + n + 1;
    }
    solve();
  }

  return 0;
}
