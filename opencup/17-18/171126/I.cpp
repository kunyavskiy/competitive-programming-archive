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
typedef pair<int, int> pii;

const int INF = (1 << 30);

void addEdge(vector<vector<int>> & ed, int u, int v) {
  ed[v].push_back(u);
  eprintf("%d -> %d\n", u, v);
}

void buildRangeTreeGraph(vector<vector<int>> & ed,
                         vector<int> & vnum,
                         int t, int L, int R) {
  if (L == R) {
    vnum[L] = t;
    return;
  }
  int M = (L + R) / 2;
  addEdge(ed, t, 2 * t);
  addEdge(ed, t, 2 * t + 1);
  buildRangeTreeGraph(ed, vnum, 2 * t, L, M);
  buildRangeTreeGraph(ed, vnum, 2 * t + 1, M + 1, R);
}

void addRangeTreeEdges(vector<vector<int>> & ed,
                       int fromV, int L, int R,
                       int t, int LT, int RT) {
  if (RT < L || R < LT) {
    return;
  }
  if (L <= LT && RT <= R) {
    addEdge(ed, fromV, t);
    return;
  }
  int MT = (LT + RT) / 2;
  addRangeTreeEdges(ed, fromV, L, R, 2 * t, LT, MT);
  addRangeTreeEdges(ed, fromV, L, R, 2 * t + 1, MT + 1, RT);
}

void dfs(int s, const vector<vector<int>> & ed, int val, vector<int> & ans) {
  if (ans[s] != -1) {
    return;
  }
  ans[s] = val;
  for (int v : ed[s]) {
    dfs(v, ed, val, ans);
  }
}

vector <int> dijkstra(const vector<vector<int>> & ed,
                      const vector<int> & val) {
  int n = int(ed.size());
  vector<int> ans(n, -1);

  vector <pii> pairs(n);
  for (int i = 0; i < n; ++i) {
    pairs[i] = {val[i], i};
  }
  sort(pairs.begin(), pairs.end(), greater<pii>());
  for (int i = 0; i < n; ++i) {
    dfs(pairs[i].second, ed, pairs[i].first, ans);
  }
  return ans;
}

pii combine(pii x, pii y) {
  return {min(x.first, y.first), max(x.second, y.second)};
}

struct RangeTree {
  int kk;
  vector <pii> b;
  RangeTree(vector<int> & a) {
    vector <pii> aa(a.size());
    for (int i = 0; i < int(a.size()); ++i) {
      aa[i] = {a[i], a[i]};
    }
    build(aa);
  }
  RangeTree(vector<pii> & a) {
    build(a);
  }
  void build(vector<pii> & a) {
    int n = int(a.size());
    kk = 1;
    while (kk < n) {
      kk *= 2;
    }
    b.resize(2 * kk + 10);
    for (int i = 0; i < n; ++i) {
      b[i + kk] = a[i];
    }
    for (int i = kk - 1; i >= 1; --i) {
      update(i);
    }
  }

  pii getMinMax(int L, int R) {
    pii ans(INF, -INF);
    L += kk, R += kk;
    while (L <= R) {
      if (L % 2 == 1) {
        ans = combine(ans, b[L++]);
      }
      if (R % 2 == 0) {
        ans = combine(ans, b[R--]);
      }
      L /= 2, R /= 2;
    }
    return ans;
  }

  void update(int t) {
    b[t] = combine(b[2 * t], b[2 * t + 1]);
  }

};

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  vector <int> p(n);
  vector <int> invP(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &p[i]);
    --p[i];
    invP[p[i]]= i;
  }
  RangeTree tree_invP(invP);
  vector <pii> expand(n);
  for (int i = 0; i < n - 1; ++i) {
    int a = p[i];
    int b = p[i + 1];
    if (a > b) { swap(a, b); }
    expand[i] = tree_invP.getMinMax(a, b);

//    eprintf("i %d -> expand (%d %d)\n", i, expand[i].first, expand[i].second);
  }

  vector <vector<int>> ed(4 * n);
  vector <int> vnum(n - 1);
  buildRangeTreeGraph(ed, vnum, 1, 0, n - 2);
  for (int i = 0; i < n - 1; ++i) {
    addRangeTreeEdges(ed, vnum[i], expand[i].first, expand[i].second - 1, 1, 0, n - 2);
  }

  for (int ii = 0; ii < 2; ++ii) {
    vector <int> val(ed.size(), -1);
    for (int i = 0; i < int(vnum.size()); ++i) {
      val[vnum[i]] = (ii == 0 ? i : 2 * n - i);
    }
    vector<int> zzz = dijkstra(ed, val);
    for (int i = 0; i < int(vnum.size()); ++i) {
      if (ii == 0) {
        expand[i].second = zzz[vnum[i]] + 1;
      } else {
        expand[i].first = 2 * n - zzz[vnum[i]];
      }
    }
  }
//  for (int i = 0; i < int(vnum.size()); ++i) {
//    eprintf("i %d -> expand (%d %d)\n", i, expand[i].first, expand[i].second);
//  }
  RangeTree tree(expand);

  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    int L, R;
    scanf("%d%d", &L, &R);
    --L, --R;
    pii ans = (L == R ? pii({L, R}) : tree.getMinMax(L, R - 1));
    printf("%d %d\n", ans.first + 1, ans.second + 1);
  }

  return 0;
}
