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
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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

const int MAXN = 100100;

int n;
int tin[MAXN];
int tout[MAXN];
int h[MAXN];
int depth[MAXN];
vector<int> hv[MAXN];
vector<int> g[MAXN];
int timer;


struct Cleaner {
  ~Cleaner() {
    timer = 0;
    for (int i = 0; i < n; i++) {
      tin[i] = tout[i] = h[i] = depth[i] = 0;
      hv[i].clear();
      g[i].clear();
    }
  }
};

void dfs(int v, int hh = 0) {
  h[v] = hh;
  depth[v] = 0;
  hv[hh].push_back(v);
  tin[v] = ++timer;
  for (int u : g[v]) {
    dfs(u, hh + 1);
    depth[v] = max(depth[v], depth[u] + 1);
  }
  tout[v] = ++timer;
}

struct item {
  int at;
  vector<int> bt;
  int id;
};

vector<int> merge_classes(const vector<int> &a, const vector<int> &b, int ad) {
  if (ad == 0) return b;
  vector<item> v(n);
  for (int i = 0; i < n; i++) {
    v[i].at = a[i];
    v[i].id = i;
    int hh = h[i] + ad;
    if (hh < n) {
      int from = (int) (
          lower_bound(hv[hh].begin(), hv[hh].end(), i, [](int x, int y) -> bool { return tin[x] <= tin[y]; }) -
          hv[hh].begin());
      int to = (int) (
          lower_bound(hv[hh].begin(), hv[hh].end(), i, [](int x, int y) -> bool { return tout[x] <= tout[y]; }) -
          hv[hh].begin());

      for (int j = from; j < to; j++) {
        v[i].bt.push_back(b[hv[hh][j]]);
      }
    }
  }
  sort(v.begin(), v.end(), [](const item& x, const item & y) -> bool {
    if (x.at != y.at) return x.at < y.at;
    return x.bt < y.bt;
  });

  vector<int> res(n);

  int c = -1;
  for (int i = 0; i < n;) {
    int j = i;
    while (j < n && v[i].at == v[j].at && v[i].bt == v[j].bt) {
      j++;
    }
    c++;
    while (i < j) res[v[i++].id] = c;
  }

  return res;
}

const int MAX_LOG = 17;
vector<int> classes[MAX_LOG];

bool good_classes(int d, const vector<int>& c) {
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    a[i] = i;
  }
  sort(a.begin(), a.end(), [&c](int x, int y) -> bool { return c[x] < c[y];});
  for (int i = 0; i < n; ) {
    int j = i;
    int m1 = -1;
    int m2 = -1;
    while (j < n && c[a[i]] == c[a[j]]) {
      int t = depth[a[j]];
      if (m1 < t) swap(m1, t);
      if (m2 < t) swap(m2, t);
      j++;
    }
    if (m2 >= d) return true;
    i = j;
  }
  return false;
}

void solve() {
  Cleaner _;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int k;
    scanf("%d", &k);
    g[i].resize(k);
    for (int j = 0; j < k; j++) {
      scanf("%d", &g[i][j]);
      g[i][j]--;
    }
  }
  dfs(0);
  classes[0] = vector<int>(n, 0);
  for (int i = 0; i < n; i++) {
    classes[0][i] = g[i].size();
  }
  int d;
  for (d = 1; (1 << d) <= n; d++) {
    classes[d] = merge_classes(classes[d - 1], classes[d - 1], 1 << (d - 1));
  }
  vector<int> cur = vector<int>(n, 0);
  int curh = 0;
  for (int i = d - 1; i >= 0; i--) {
    vector<int> ncur = merge_classes(cur, classes[i], curh);
    if (good_classes(curh + (1 << i), ncur)) {
      curh += 1 << i;
      cur = ncur;
    }
  }
  printf("%d\n", curh);
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t --> 0) {
    solve();
  }

  return 0;
}
