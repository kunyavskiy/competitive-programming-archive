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

//#define int long long
typedef long long ll;
typedef long double ld;

void print(vector<ll> a) {
  if (a.empty()) printf("%d\n", -1);
  else {
    for (int i = 0; i < (int)a.size(); i++) printf("%lld\n", a[i]);
  }
}

const int INF = (int)1e9;

vector<ll> solve(vector<vector<ll>> b) {
  int m = b.size();

  vector<ll> a, c;
  for (int i = 0; i < (int)b.size(); i++) {
    for (ll x : b[i]) {
      a.push_back(x);
      c.push_back(i);
    }
  }
  int n = a.size();

  vector<int> taken(n);
  while (1) {
    vector<int> basis;
    vector<int> bid(n, -1);

    vector<int> usedColor(m);
    for (int i = 0; i < n; i++) {
      if (taken[i]) {
        usedColor[c[i]] = 1;
        bid[i] = basis.size();
        basis.push_back(i);
        //db(i);
      }
    }

    vector<pair<ll, ll>> t;
    //db("");
    for (int i = 0; i < (int)basis.size(); i++) {
      t.push_back({a[basis[i]], 1LL << i});
      //db2(t[i].first, t[i].second);
    }

    int k = t.size();
    vector<ll> h(k);
    for (int i = 0; i < k; i++) {
      int id = max_element(t.begin() + i, t.end()) - t.begin();
      swap(t[id], t[i]);
      assert(t[id].first != 0);
      int f = -1;
      for (int j = 60; j >= 0; j--) {
        if (t[i].first & (1LL << j)) {
          f = j;
          break;
        }
      }
      assert(f != -1);
      h[i] = f;
      for (int j = i + 1; j < k; j++) {
        if (t[j].first & (1LL << f)) {
          t[j].first ^= t[i].first;
          t[j].second ^= t[i].second;
        }
      }
    }


    // drop y, add z
    auto can = [&](int remove, int add) {
      ll y = a[add];
      ll x = 0;
      for (int i = 0; i < (int)t.size(); i++) {
        if (y & (1LL << h[i])) {
          y ^= t[i].first;
          x ^= t[i].second;
        }
      }
      if (y != 0) {
        return 1;
      }
      if (remove == -1) {
        return 0;
      }
      if (x & (1LL << bid[remove])) {
        return 1;
      }
      return 0;
    };

    // first -- colors
    // second -- independent

    vector<vector<int>> e(n);
    /*for (int y = 0; y < n; y++) {
      if (!taken[y]) continue;
      for (int z = 0; z < n; z++) {
        if (taken[z]) continue;
        if (!usedColor[c[z]] || c[y] == c[z]) {
          e[y].push_back(z);
          //db3(1, y, z);
        }
      }
    }
    for (int y = 0; y < n; y++) {
      if (!taken[y]) continue;
      for (int z = 0; z < n; z++) {
        if (taken[z]) continue;
        if (can(y, z)) {
          e[z].push_back(y);
          //db3(2, z, y);
        }
      }
    }*/

    ///db("");
    /*for (int i = 0; i < n; i++) {
      dbv(e[i]);
    }*/

    vector<int> x1(n), x2(n);
    for (int i = 0; i < n; i++) {
      if (!usedColor[c[i]]) {
        x1[i] = 1;
      }
      if (can(-1, i)) {
        x2[i] = 1;
      }
      if (taken[i]) {
        x1[i] = x2[i] = 0;
      }
    }
    //dbv(x1);
    //dbv(x2);
    vector<int> d(n, INF), pr(n, -1);
    vector<int> q;
    for (int i = 0; i < n; i++) {
      if (x1[i]) {
        d[i] = 0;
        q.push_back(i);
      }
    }
    int nw = -1;
    for (int qq = 0; qq < (int)q.size(); qq++) {
      int v = q[qq];
      if (x2[v]) {
        nw = v;
        break;
      }
      //for (int to : e[v]) {
      for (int to = 0; to < n; to++) {
        bool edge = 0;

        if (taken[v] && !taken[to]) {
          edge = !usedColor[c[to]] || c[v] == c[to];
        }
        if (!taken[v] && taken[to]) {
          edge = can(to, v);
        }

        if (edge && d[to] > d[v] + 1) {
          d[to] = d[v] + 1;
          pr[to] = v;
          q.push_back(to);
        }
      }
    }
    if (nw == -1) break;
    vector<int> vert;
    for (int v = nw; v != -1; v = pr[v]) {
      vert.push_back(v);
    }
    assert(vert.size() % 2 == 1);
    int dif = 0;
    for (int v : vert) {
      dif += taken[v] == 0;
      dif -= taken[v] == 1;
      taken[v] ^= 1;
    }
    assert(dif == 1);
  }
  vector<ll> ans;
  for (int i = 0; i < n; i++) if (taken[i]) ans.push_back(a[i]);

  if ((int)ans.size() != m) {
    return vector<ll>();
  }
  return ans;
}

int ok(vector<ll> a) {
  int n = a.size();
  for (int mask = 1; mask < (1 << n); mask++) {
    ll xr = 0;
    for (int i = 0; i < n; i++) if (mask & (1 << i)) xr ^= a[i];
    if (xr == 0) return 0;
  }
  return 1;
}

vector<ll> slow(vector<vector<ll>> a) {
  int n = a.size();
  vector<ll> b(n);
  function<int(int)> rec = [&](int x) {
    if (x == (int)n) {
      return ok(b);
    }
    for (ll y : a[x]) {
      b[x] = y;
      if (rec(x + 1)) return 1;
    }
    return 0;
  };
  if (rec(0)) return b;
  return vector<ll>();
}

void stress() {
  for (int it = 0;; it++) {
    cerr << it << endl;
    srand(it);

    int n = rand() % 20 + 1;
    vector<vector<ll>> a(n);
    for (int i = 0; i < n; i++) {
      int k = rand() % 2 + 1;
      for (int j = 0; j < k; j++) {
        a[i].push_back((rand() % (1 << (n)) + 1) * (1LL << 40));
      }
    }
    auto ans1 = solve(a);
    auto ans2 = slow(a);
    db2(ans1.size(), ans2.size());
    assert(ans1.empty() == ans2.empty());
    assert(ok(ans1));
  }
}

void test() {
  int n = 60;
  vector<vector<ll>> a(n);

  mt19937_64 rnd;
  for (int i = 0; i < n; i++) {
    int k = 5000 / n;
    for (int j = 0; j < k; j++) {
      a[i].push_back(rnd() % (1LL << 60));
    }
  }
  solve(a);
  exit(0);
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  //freopen("d.out", "w", stdout);
#endif
  //stress();
  //test();

  bool first = 1;
  int n;
  while (scanf("%d", &n) == 1) {
    if (first) first = 0;
    else printf("\n");

    vector<vector<ll>> a(n);
    for (int i = 0; i < n; i++) {
      ll x;
      scanf("%lld", &x);
      a[i].push_back(x);
    }
    int m;
    scanf("%d", &m);
    m += n;
    a.resize(m);
    for (int i = n; i < m; i++) {
      int k;
      scanf("%d", &k);
      a[i].resize(k);
      for (int j = 0; j < k; j++) {
        scanf("%lld", &a[i][j]);
      }
    }

    auto ans = solve(a);
    if (!ans.empty()) {
      vector<ll> nans;
      for (int i = n; i < m; i++) nans.push_back(ans[i]);
      ans = nans;
    }
    print(ans);
  }

  return 0;
}
