#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

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
  vector<int> v;
  vector<int> mn;
  explicit dsu(int n) :v(n) {
    std::iota(v.begin(),  v.end(), 0);
    mn = v;
  }
  int get(int a) {
    return a == v[a] ? a : (v[a] = get(v[a]));
  }

  void join(int a, int b) {
    a = get(a);
    b = get(b);
    assert(a != b);
    v[a] = b;
    mn[b] = min(mn[a], mn[b]);
  }
};

struct edge {
  int u, v, w;
};

vector<tuple<int, int, int>> read_tree(int n) {
  vector<edge> es(n - 1);
  for (edge &e : es) {
    scanf("%d%d%d", &e.u, &e.v, &e.w);
    --e.u, --e.v;
  }
  sort(es.begin(), es.end(), [](const edge& a, const edge& b) {
    return a.w > b.w;
  });
  dsu d(n);
  vector<tuple<int, int, int>> r;
  for (int i = 0; i < (int)es.size();) {
    int w = es[i].w;
    int j;
    vector<int> mns;
    for (j = i; j < (int)es.size() && es[j].w == es[i].w; j++) {
      mns.push_back(d.mn[d.get(es[j].u)]);
      mns.push_back(d.mn[d.get(es[j].v)]);
    }
    sort(mns.begin(), mns.end());
    mns.erase(unique(mns.begin(),  mns.end()), mns.end());
    for (;i < j; i++) {
      d.join(es[i].u, es[i].v);
    }
    for (int x : mns) {
      int y = d.mn[d.get(x)];
      if (x != y) {
        r.emplace_back(min(x, y), max(x, y), w);
      }
    }
  }
  sort(r.begin(), r.end());
  return r;
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int d, n;
  while (scanf("%d%d", &d, &n) == 2) {
    vector<vector<tuple<int, int, int>>> trees(d);
    for (int i = 0; i < d; i++) {
      trees[i] = read_tree(n);
    }
    vector<int> a(d);
    std::iota(a.begin(), a.end(), 0);
    stable_sort(a.begin(), a.end(), [&](int x, int y) {
      return trees[x] < trees[y];
    });
    vector<int> ans(d);
    for (int i = 0; i < d; i++) {
      if (i != 0 && trees[a[i]] == trees[a[i - 1]]) {
        ans[a[i]] = ans[a[i-1]];
      } else {
        ans[a[i]] = a[i];
      }
    }
    for (int i = 0; i < d; i++) {
      printf("%d ", ans[i] + 1);
    }
    printf("\n");
  }

  return 0;
}
