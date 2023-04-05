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
#include <numeric>
#include <random>

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
const ll INF = 1e18;

ll fast(vector<vector<int>> e, vector<int> a, int k) {
  int n = a.size();

  auto upd_min = [&](ll &x, ll y) {
    x = min(x, y);
  };

  // {day_enter}
  vector<ll> dp_return(n, INF), dp_remain(n, INF);
  vector<int> sz(n);
  function<void(int, int)> dfs = [&](int v, int pr) {
    vector<int> ch;
    for (int to : e[v]) {
      if (to == pr) continue;
      dfs(to, v);
      ch.push_back(to);
    }
    sort(ch.begin(), ch.end(), [&](int u1, int u2) {
      return dp_return[u1] + 2 * sz[u1] < dp_return[u2] + 2 * sz[u2];
    });

    dp_return[v] = a[v];
    for (int to : ch) {
      upd_min(dp_return[v], dp_return[to] - 2 * sz[v] - 1);
      sz[v] += sz[to];
    }
    upd_min(dp_return[v], a[v] + k - 2 * sz[v] - 2);
    sz[v]++;


    int m = ch.size();
    vector<ll> suf(m + 1);
    suf[m] = INF;
    for (int i = m - 1; i >= 0; i--) {
      int to = ch[i];
      suf[i] = min(suf[i + 1] - 2 * sz[to], dp_return[to] - 1);
    }

    dp_remain[v] = m == 0 ? a[v] : -1;
    int csz = 0;
    ll cans = a[v];
    for (int i = 0; i < m; i++) {
      int to = ch[i];

      ll cand = cans;
      cand = min(cand, suf[i + 1] - 2 * csz);
      int before = sz[v] - 1 - sz[to];
      upd_min(cand, dp_remain[to] - 2 * before - 1);
      upd_min(cand, a[v] + k - 2 * before - 2);
      dp_remain[v] = max(dp_remain[v], cand);

      upd_min(cans, dp_return[to] - 2 * csz - 1);
      csz += sz[to];
    }
  };
  dfs(0, -1);
//  dbv(dp_return);
//  dbv(dp_remain);
  return max(-1LL, dp_remain[0]);
}

ll slow(vector<vector<int>> e, vector<int> a, int k) {
  int n = a.size();
  vector<int> p(n);
  iota(p.begin(), p.end(), 0);

  vector<vector<vector<int>>> path(n, vector<vector<int>>(n));
  for (int s = 0; s < n; s++) {
    path[s][s].push_back(s);
    vector<int> q;
    q.push_back(s);
    for (int i = 0; i < (int)q.size(); i++) {
      int v = q[i];
      for (int to : e[v]) {
        if (path[s][to].empty()) {
          path[s][to] = path[s][v];
          path[s][to].push_back(to);
          q.push_back(to);
        }
      }
    }
  }

  ll ans = -1;
  do {
    vector<int> pp;
    pp.push_back(p[0]);
    for (int i = 1; i < n; i++) {
      for (int j = 1; j < (int)path[p[i - 1]][p[i]].size(); j++) {
        pp.push_back(path[p[i - 1]][p[i]][j]);
      }
    }
    map<pair<int, int>, int> mp;
//    dbv(pp);

    ll res = a[0];
    auto ca = a;

    vector<int> was(n);
    for (int i = 0; i < (int)pp.size() - 1; i++) {
      int v = pp[i];
      int to = pp[i + 1];
      pair<int, int> o = make_pair(v, to);
      if (o.first > o.second) swap(o.first, o.second);
      mp[o]++;

      if (!was[v]) {
        ca[v] += k;
        was[v] = 1;
      }
      for (int &x : ca) {
        x--;
      }
      res = min(res, (ll)ca[v] - 1);
      res = min(res, (ll)ca[to]);
    }
    bool ok = 1;
    for (auto it : mp) if (it.second > 2) ok = 0;
    if (ok) ans = max(ans, res);
  } while (next_permutation(p.begin() + 1, p.end()));
  return ans;
}

void stress() {
  for (int it = 388;; it++ ){
    db(it);
    mt19937 rnd(it);

    int n = rnd() % 7 + 2;
    vector<vector<int>> e(n);
    for (int i = 1; i < n; i++) {
      int p = rnd() % i;
      e[p].push_back(i);
      e[i].push_back(p);
    }
    int k = rnd() % (4 * n) + 1;
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = rnd() % (2 * n);

    auto ans1 = fast(e, a, k);
    auto ans2 = slow(e, a, k);
    if (ans1 != ans2) {
      db2(ans1, ans2);
      db2(n, k);
      for (int i = 0; i < n; i++) {
        for (int to : e[i]) {
          if (i < to) {
            db2(i, to);
          }
        }
      }
      dbv(a);
      exit(0);
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
//  freopen("d.out", "w", stdout);
#endif
//  stress();

  int n, k;
  while (scanf("%d%d", &n, &k) == 2) {
    vector<vector<int>> e(n);
    for (int i = 0; i < n - 1; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      u--; v--;
      e[u].push_back(v);
      e[v].push_back(u);
    }
    vector<int> a(n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    cout << fast(e, a, k) << endl;
  }

  return 0;
}
