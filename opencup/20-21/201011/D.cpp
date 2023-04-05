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

struct dsu {
  vector<int> p, sz;
  explicit dsu(int n) : p(n), sz(n, 1) {
    for (int i = 0; i < n; i++) p[i] = i;
  }

  int get(int x) {
    if (x == p[x]) return x;
    return p[x] = get(p[x]);
  }

  ll join(int a, int b) {
    a = get(a);
    b = get(b);
    if (a == b) return 0;
    if (sz[a] > sz[b]) swap(a, b);
    ll ans = sz[a] * 1LL * sz[b];
    p[a] = b;
    sz[b] += sz[a];
    return ans;
  }
};

struct edge {
  int a, b, w;
};

void solve(int n,int m) {
  vector<edge> es(m);
  for (auto &e : es) {
    scanf("%d%d%d", &e.a, &e.b, &e.w);
    --e.a, --e.b;
  }
  sort(es.begin(), es.end(), [](const edge &a, const edge &b) { return a.w > b.w; });
  dsu d(n);
  ll ans = 0;
  vector<edge> tr;
  for (int i = 0; i < m;) {
    int j = i;
    for (; j < m && es[i].w == es[j].w; j++) {}
    for (int k = i; k < j; k++) {
      if (d.get(es[k].a) == d.get(es[k].b)) {
        printf("-1\n");
        return;
      }
    }
    for (int k = i; k < j; k++) {
      ans += d.join(es[k].a, es[k].b) * es[k].w;
    }
    i = j;
  }
//  d = dsu(n);
//  reverse(tr.begin(), tr.end());
//  for (auto e : tr) {
//    ans += d.join(e.a, e.b) * e.w;
//  }
  for (int i = 0; i < n; i++) {
    ans += d.join(0, i);
  }
  printf("%lld\n", ans);
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    solve(n, m);
  }



  return 0;
}
