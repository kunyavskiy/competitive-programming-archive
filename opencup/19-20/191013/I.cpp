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

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

struct second_max {
  ll a = 0;
  ll b = 0;
  void feed(ll c) {
    if (a < c) swap(a, c);
    if (b < c) swap(b, c);
  }
};

pair<ll, int> get_far(const vector<vector<pair<int, int>>> &t, int s) {
  static vector<int> q;
  q.reserve(t.size());
  q.clear();
  static vector<ll> d;
  d.resize(t.size());
  fill(d.begin(), d.end(), 1e16);
  d[s] = 0;
  q.push_back(s);
  for (int i = 0; i < (int)q.size(); i++) {
    int v = q[i];
    for (const auto &u : t[v]) {
      if (d[u.first] > d[v] + u.second) {
        d[u.first] = d[v] + u.second;
        q.push_back(u.first);
      }
    }
  }
  pair<ll, int> ans;
  for (int i = 0; i < (int)t.size(); i++) {
    ans = max(ans, pair<ll, int>(d[i], i));
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<vector<ll>> g(n, vector<ll>(n, 1e16));
    vector<vector<int>> p(n, vector<int>(n, -1));
    vector<vector<pii>> ed(n);
    for (int i = 0; i < n; i++) {
      g[i][i] = 0;
      for (int j = 0; j < n; j++) {
        p[i][j] = i;
      }
      p[i][i] = -1;
    }
    for (int i = 0; i < m; i++) {
      int a, b, w;
      scanf("%d%d%d", &a, &b, &w);
      --a, --b;
      w *= 2;
      g[a][b] = g[b][a] = w;
      ed[a].emplace_back(b, w);
    }
    for (int i = 0; i < n; i++) {
      g[i][i] = 0;
    }
    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if (g[i][j] > g[i][k] + g[k][j]) {
            g[i][j] = g[i][k] + g[k][j];
            p[i][j] = p[k][j];
          }
        }
      }
    }

    ll best = 1e16;
    int best_u1 = -1, best_u2 = -1;
    ll best_x = -1, best_w = -1;
    for (int u1 = 0; u1 < n; ++u1) {
      vector<int> vs(n);
      for (int i = 0; i < n; ++i) {
        vs[i] = i;
      }
      sort(vs.begin(), vs.end(), [&](int v1, int v2) { return g[u1][v1] < g[u1][v2];});
      for (const auto &e : ed[u1]) {
        int u2 = e.first;
        ll w = e.second;
        vector<int> st;
        for (int v : vs) {
          while (!st.empty() && g[u2][st.back()] <= g[u2][v]) {
            st.pop_back();
          }
          st.push_back(v);
        }
        auto update = [&](ll val, int x) {
          if (0 <= x && x <= w) {
            if (best > val) {
              best = val;
              best_u1 = u1;
              best_u2 = u2;
              best_x = x;
              best_w = w;
            }
          }
        };
        update(g[u1][st.back()], 0);
        update(g[u2][st[0]], w);
        for (int i = 1; i < int(st.size()); ++i) {
          ll a = g[u1][st[i - 1]];
          ll b = g[u2][st[i]];
          ll x = (b - a + w) / 2;
          ll val = a + x;
          update(val, x);
        }
      }
    }

    printf("%lld\n", best);
    printf("%d %d\n", best_u1 + 1, best_u2 + 1);
    for (int v = 0; v < n; v++) {
      if (v == best_u1 || v == best_u2) { continue; }
      int pp;
      if (g[best_u1][v] + best_x <= g[best_u2][v] + best_w - best_x) {
        pp = p[best_u1][v];
      } else {
        pp = p[best_u2][v];
      }
      printf("%d %d\n", pp + 1, v + 1);
    }
  }

  return 0;
}
