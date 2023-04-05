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

#define stack stack_aaaa

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

const int MAXN = 210000;

vector<pair<int, int>> g[MAXN];
pair<int, int> es[MAXN];
bool bad[MAXN];

vector<int> g2[MAXN];
int color[MAXN];

int tin[MAXN];
int tup[MAXN];
int used[MAXN];
vector<int> stack;
int timer;

int cs[2];

bool dfs_bip(int v, int c) {
  if (color[v] != -1) {
    return color[v] == c;
  }
  cs[c]++;
  color[v] = c;
  for (int u : g2[v]) {
    if (!dfs_bip(u, 1 - c)) {
      return false;
    }
  }
  return true;
}

void dfs(int v, int p = -1) {
  used[v] = 1;
  tup[v] = tin[v] = timer++;
  for (auto x : g[v]) {
    int to = x.first;
    int id = x.second;
    if (used[to] == 2 || to == p) {
      continue;
    }
    if (used[to] == 1) {
      tup[v] = min(tup[v], tin[to]);
      stack.push_back(id);
      continue;
    }
    stack.push_back(id);
    dfs(to, v);
    tup[v] = min(tup[v], tup[to]);

    if (tup[to] >= tin[v]) {
      vector<int> vs;
      vector<int> ges;

      eprintf("====\n");

      while (true) {
        int sid = stack.back();
        stack.pop_back();

        ges.push_back(sid);

        int a = es[sid].first;
        int b = es[sid].second;

        eprintf("%d %d\n", a, b);

        vs.push_back(a);
        vs.push_back(b);

        g2[a].push_back(b);
        g2[b].push_back(a);

        if (sid == id) break;
      }
      for (int i : vs) {
        color[i] = -1;
      }

      if (!dfs_bip(vs[0], 0)) {
        for (int eid : ges) {
          bad[eid] = 1;
        }
      }

      for (int i : vs) {
        g2[i].clear();
      }
    }
  }
  used[v] = 2;
}

ll odd, even;

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    es[i] = {a, b};
    g[a].push_back({b, i});
    g[b].push_back({a, i});
  }

  dfs(0);

  for (int i = 0; i < m; i++) {
    if (!bad[i]) {
      g2[es[i].first].push_back(es[i].second);
      g2[es[i].second].push_back(es[i].first);
    }
  }

  memset(color, -1, sizeof(color));

  for (int i = 0; i < n; i++) {
    if (color[i] == -1) {
      cs[0] = cs[1] = 0;
      assert(dfs_bip(i, 0));
      odd += cs[0] * 1LL * cs[1];
      even += cs[0] * 1LL * (cs[0] - 1) / 2 + cs[1] * 1LL * (cs[1] - 1) / 2;
    }
  }

  printf("%lld %lld\n", even, odd);

  return 0;
}
