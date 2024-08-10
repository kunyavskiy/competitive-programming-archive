#pragma GCC optimize "-O3"

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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x)                                                           \
  eprintf("[" #x "] Time : %.3lf s.\n",                                        \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...)                                                     \
  eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__,                            \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() { TIMESTAMPf("%s", what.data()); }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

vector<pair<int, int>> find_comps(int n, int m) {
  vector<vector<int>> gid(n);
  vector<int> a(m), b(m);
  for (int i = 0; i < m; i++) {
    scanf("%d%d", &a[i], &b[i]);
    --a[i], --b[i];
    gid[a[i]].push_back(i);
    gid[b[i]].push_back(i);
  }
  vector<pair<int, int>> comps;

  vector<int> used(n);
  vector<int> stack;
  vector<int> tin(n);
  vector<int> tup(n);
  int timer = 0;
  auto dfs = [&](auto self, int v, int peid) -> void {
    tin[v] = tup[v] = timer++;
    used[v] = 1;
    for (int eid : gid[v]) {
      if (eid == peid)
        continue;
      int u = a[eid] + b[eid] - v;
      if (used[u] == 1) {
        stack.push_back(eid);
        tup[v] = min(tup[v], tin[u]);
        continue;
      }
      if (used[u] == 2) {
        continue;
      }
      stack.push_back(eid);
      self(self, u, eid);
      tup[v] = min(tup[v], tup[u]);
      if (tup[u] >= tin[v]) {
        vector<int> vs;
        int ecnt = 0;
        while (true) {
          int seid = stack.back();
          stack.pop_back();
          vs.push_back(a[seid]);
          vs.push_back(b[seid]);
          ecnt++;
          if (seid == eid) {
            break;
          }
        }
        sort(vs.begin(), vs.end());
        int vcnt = unique(vs.begin(), vs.end()) - vs.begin();
        comps.emplace_back(vcnt, ecnt);
      }
    }
    used[v] = 2;
  };

  dfs(dfs, 0, -1);
  return comps;
}

#ifdef LOCAL
//#define TEST
#endif

const int MAXN = 510000;

ll ax[MAXN];
ll bx[MAXN];
int nnext[MAXN];
int pprev[MAXN];
vector<int> events[MAXN];

void add_sq(vector<ll> &ans, int lim, ll coef) {
#ifdef TEST
  vector<ll> ans2 = ans;
  int nn = ans2.size();
  for (int i = nn - 1; i >= 0; i--) {
    for (int j = max(i - lim, 0); j < i; j++) {
      ans2[i] = min(ans2[i], ans2[j] + coef * (i - j) * (i - j));
    }
  }
#endif

  int n = ans.size();
  for (int i = 0; i < n; i++) {
    ax[i] = ans[i] + coef * i * i;
    bx[i] = -2 * coef * i;
  }

  for (int i = 0; i < n; i++) {
    nnext[i] = i + 1;
    pprev[i] = i - 1;
  }
  int first = 0;
  for (int i = 0; i < n; i++) {
    events[i].clear();
  }

  auto get_time = [&](int p1, int p2) {
    ll db = bx[p1] - bx[p2];
    assert(db > 0);
    ll da = ax[p2] - ax[p1];
    if (da < 0) return 0LL;
    return (da + db - 1) / db;
  };

  auto add_event = [&](int at, int curt) {
    int nxt = nnext[at];
    if (nxt >= n) return;
    ll tm = max<ll>(curt, get_time(at, nxt));
    tm = min<ll>(tm, at + lim + 1);
    if (tm >= n) return;
    events[tm].push_back(at);
  };

  for (int i = 0; i < n; i++) {
    if (i > 0) add_event(i - 1, i);
    for (int pt = 0; pt < (int)events[i].size(); pt++) {
      int x = events[i][pt];
      if (nnext[x] == -1) {
        continue;
      }
      if (pprev[x] == -1) {
        first = nnext[x];
      } else {
        nnext[pprev[x]] = nnext[x];
        add_event(pprev[x], i);
      }
      pprev[nnext[x]] = pprev[x];
      pprev[x] = nnext[x] = -1;
    }
#ifdef TEST
    ll r = std::numeric_limits<ll>::max();
    for (int j = max(i - lim, 0); j <= i; j++) {
      r = min(r, ax[j] + bx[j] * i);
    }
    assert(ax[first] + bx[first] * i == r);
#endif
    ans[i] = ax[first] + bx[first] * i + coef * i * i;
  }

#ifdef TEST
  assert(ans == ans2);
#endif
}

void solve(int n, int m, int k, int l) {
  vector comps = find_comps(n, m);

  for (auto &[x, y] : comps) {
    x--;
  }

  constexpr long long int INF = std::numeric_limits<ll>::max() / 2;

  while (true) {
    sort(comps.begin(), comps.end());
    vector<pair<int, int>> merged;
    for (int i = 0; i < (int)comps.size(); ) {
      int j = i;
      while (j < (int)comps.size() && comps[i] == comps[j])
        j++;
      int cnt = j - i;
      while (cnt >= 3) {
        merged.emplace_back(comps[i].first * 2, comps[i].second * 2);
        cnt -= 2;
      }
      while (cnt > 0) {
        merged.push_back(comps[i]);
        cnt--;
      }
      i = j;
    }
    if (merged.size() == comps.size())
      break;
    comps = std::move(merged);
  }

  eprintf("comps = %d\n", (int)comps.size());

  vector<ll> ans(k + 1, INF);
  ans[0] = 0;
  for (int i = 0; i < (int)comps.size(); ) {
    int j = i;
    while (j < (int)comps.size() && comps[i].first == comps[j].first) j++;
    if (comps[i].first <= k) {
      for (int shift = 0; shift < comps[i].first; shift++) {
        vector<ll> sub((k - shift) / comps[i].first + 1, -1);
        for (int x = shift; x <= k; x += comps[i].first) {
          sub.at((x - shift) / comps[i].first) = ans[x];
        }
        assert(sub.back() != -1);
        for (int x = i; x < j; x++) {
          add_sq(sub, l, comps[x].second);
        }
        for (int x = shift; x <= k; x += comps[i].first) {
          ans[x] = sub[(x - shift) / comps[i].first];
        }
      }
    }
    i = j;
  }
  for (int i = 0; i <= k; i++) {
    if (ans[i] == INF) ans[i] = -1;
    printf("%lld ", ans[i]);
  }
  printf("\n");
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  int n, m, k, l;
  while (scanf("%d%d%d%d", &n, &m, &k, &l) == 4) {
    solve(n, m, k, l);
  }

  return 0;
}
