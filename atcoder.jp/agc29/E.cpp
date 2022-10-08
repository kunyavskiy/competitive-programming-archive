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
  vector<int> p;
  vector<int> size;
  dsu(int n) : p(n), size(n) {
    for (int i = 0; i < n; i++) {
      p[i] = i;
      size[i] = 1;
    }
  }

  int get(int v) {
    if (v == p[v]) return v;
    return p[v] = get(p[v]);
  }

  void join(int a, int b) {
    a = get(a);
    b = get(b);
    if (a == b) return;
    if (size[a] > size[b]) swap(a, b);
    p[a] = b;
    size[b] += size[a];
  }

  int is_same(int a, int b) {
    return get(a) == get(b);
  }

  int get_size(int a) {
    return size[get(a)];
  }
};

vector<vector<int>> g;
dsu d(0);
vector<int> ans, maxv;

int find_less(int u, int p, int lim) {
  if (u > lim) {
    return 0;
  }
  int ans = 1;
  for (int v : g[u]) {
    if (v != p && v < lim && d.is_same(v, u)) {
      ans += find_less(v, u, lim);
    }
  }
  return ans;
}

void set_ans(int u, int p, int a, int m) {
  ans[u] = a;
  maxv[u] = m;
  for (int v : g[u]) {
    if (v != p && d.is_same(v, u)) {
      set_ans(v, u, a, m);
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  g = vector<vector<int>> (n);
  d = dsu(n);

  ans = vector<int> (n, -1);
  maxv = vector<int> (n, -1);

  for (int i = 0; i < n - 1; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  ans[0] = 0;
  maxv[0] = 0;

  for (int v = 1; v < n; v++) {
    int up = -1;
    for (int u : g[v]) {
      if (ans[u] != -1) {
        assert(up == -1);
        up = u;
      }
    }
    if (up != -1) {
      int m = maxv[up];
      ans[v] = ans[up] + 1;
      maxv[v] = v;
      for (int u : g[v]) {
        if (u < v && u != up) {
          ans[u] = find_less(u, -1, m);
          ans[v] += ans[u];
        }
      }
      for (int u : g[v]) {
        if (u < v && u != up) {
          set_ans(u, -1, ans[v] + d.get_size(u) - ans[u], v);
        }
      }
    }
    for (int u : g[v]) {
      if (u < v) {
        d.join(u, v);
      }
    }
  }

  for (int i = 1; i < n; i++) {
    printf("%d ", ans[i]);
  }
  printf("\n");

  return 0;
}
