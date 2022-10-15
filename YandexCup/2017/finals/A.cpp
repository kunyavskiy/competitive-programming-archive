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

struct edge {
  int u, v, dh;
};

const int MAXN = 100100;
int h[MAXN];
int ans[MAXN];
int res[MAXN];

vector<int> g[MAXN];

struct hcomp {
  bool operator()(int a, int b) {
    return h[a] > h[b];
  }
};

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int n, m, s, t;
  scanf("%d%d%d%d", &n, &m, &s, &t);
  --s, --t;

  for (int i = 0; i < n; i++) {
    scanf("%d", &h[i]);
  }

  vector<edge> es(m);
  for (auto& x : es) {
    scanf("%d%d", &x.u, &x.v);
    x.u--, x.v--;
    x.dh = h[x.u] - h[x.v];
    assert(x.dh > 0);
  }

  sort(es.begin(), es.end(), [](const edge& a, const edge& b) {return a.dh > b.dh;});

  vector<int> hord(n);
  for (int i = 0; i < n; i++) {
    hord[i] = i;
  }
  sort(hord.begin(), hord.end(), hcomp());

  memset(ans, -1, sizeof(ans));
  memset(res, -1, sizeof(res));
  ans[s] = 0;

  int ptr = 1;

  for (int i = 0; i < m;) {
    int j = i;
    while (j < m && es[j].dh == es[i].dh) j++;

    set<int, hcomp> upd;

    for (int k = i; k < j; k++) {
      if (ans[es[k].u] != -1) {
        upd.insert(es[k].u);
      }
      g[es[k].u].push_back(es[k].v);
    }

    //sort(upd.begin(), upd.end(), hcomp());

    if (es[i].dh >= 5000) {
      int upd_ptr = 0;
      while (!upd.empty()) {
        int u = *upd.begin();
        upd.erase(upd.begin());
        for (int v : g[u]) {
          if (ans[v] < ans[u] + 1) {
            ans[v] = ans[u] + 1;
            upd.insert(v);
          }
        }
      }
    } else {
      for (int u : hord) {
        if (ans[u] == -1) continue;
        for (int v : g[u]) {
          ans[v] = max(ans[v], ans[u] + 1);
        }
      }
    }

    while (ptr <= ans[t]) {
      res[ptr] = es[i].dh;
      ptr++;
    }
    i = j;
  }

  for (int i = 1; i < n; i++) {
    printf("%d\n", res[i]);
  }



  return 0;
}
