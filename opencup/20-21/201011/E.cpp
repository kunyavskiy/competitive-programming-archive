#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx")

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

typedef long long ll;
typedef long double dbl;

struct Node { // Splay tree. Root's pp contains tree's parent.
  Node *p = 0, *pp = 0, *c[2];
  bool flip = 0;
  Node() { c[0] = c[1] = 0; fix(); }
  void fix() {
    if (c[0]) c[0]->p = this;
    if (c[1]) c[1]->p = this;
    // (+ update sum of subtree elements etc. if wanted)
  }
  void pushFlip() {
    if (!flip) return;
    flip = 0; swap(c[0], c[1]);
    if (c[0]) c[0]->flip ^= 1;
    if (c[1]) c[1]->flip ^= 1;
  }
  int up() { return p ? p->c[1] == this : -1; }
  void rot(int i, int b) {
    int h = i ^ b;
    Node *x = c[i], *y = b == 2 ? x : x->c[h], *z = b ? y : x;
    if ((y->p = p)) p->c[up()] = y;
    c[i] = z->c[i ^ 1];
    if (b < 2) {
      x->c[h] = y->c[h ^ 1];
      z->c[h ^ 1] = b ? x : this;
    }
    y->c[i ^ 1] = b ? this : x;
    fix(); x->fix(); y->fix();
    if (p) p->fix();
    swap(pp, y->pp);
  }
  void splay() { /// Splay this up to the root. Always finishes without flip set.
    for (pushFlip(); p; ) {
      if (p->p) p->p->pushFlip();
      p->pushFlip(); pushFlip();
      int c1 = up(), c2 = p->up();
      if (c2 == -1) p->rot(c1, 2);
      else p->p->rot(c2, c1 != c2);
    }
  }
  Node* first() { /// Return the min element of the subtree rooted at this, splayed to the top.
    pushFlip();
    return c[0] ? c[0]->first() : (splay(), this);
  }
};

struct LinkCut {
  vector<Node> node;
  LinkCut(int N) : node(N) {}

  void link(int u, int v) { // add an edge (u, v)
    assert(!connected(u, v));
    makeRoot(&node[u]);
    node[u].pp = &node[v];
  }
  void cut(int u, int v) { // remove an edge (u, v)
    Node *x = &node[u], *top = &node[v];
    makeRoot(top); x->splay();
    assert(top == (x->pp ?: x->c[0]));
    if (x->pp) x->pp = 0;
    else {
      x->c[0] = top->p = 0;
      x->fix();
    }
  }
  bool connected(int u, int v) { // are u, v in the same tree?
    Node* nu = access(&node[u])->first();
    return nu == access(&node[v])->first();
  }
  void makeRoot(Node* u) { /// Move u to root of represented tree.
    access(u);
    u->splay();
    if(u->c[0]) {
      u->c[0]->p = 0;
      u->c[0]->flip ^= 1;
      u->c[0]->pp = u;
      u->c[0] = 0;
      u->fix();
    }
  }
  Node* access(Node* u) { /// Move u to root aux tree. Return the root of the root aux tree.
    u->splay();
    while (Node* pp = u->pp) {
      pp->splay(); u->pp = 0;
      if (pp->c[1]) {
        pp->c[1]->p = 0; pp->c[1]->pp = pp; }
      pp->c[1] = u; pp->fix(); u = pp;
    }
    return u;
  }
};

ll solve(vector<vector<int>> e) {
  int n = e.size();
  for (int i = 0; i < n; i++) sort(e[i].begin(), e[i].end());

  map<pair<int, int>, int> mp;
  for (int v = 0; v < n; v++) {
    int j = lower_bound(e[v].begin(), e[v].end(), v) - e[v].begin();
    for (int i = -2; i <= 1; i++) {
      if (0 <= j + i && j + i < (int)e[v].size()) {
        int u = e[v][j + i];
        int mn = min(v, u);
        int mx = max(v, u);
        mp[{mn, mx}]++;
      }
    }
  }
  e.assign(n, vector<int>());
  for (auto o : mp) {
    if (o.second == 2) {
      auto ed = o.first;
      int u = ed.first, v = ed.second;
      e[v].push_back(u);
      e[u].push_back(v);
    }
  }

  static constexpr int k = 70;
  struct sqrtdec {
    int n;
    vector<int> b;
    vector<unordered_map<int, int>> sorted;
    vector<int> added;

    void sort(int l, int r) {
      auto &m = sorted[l / k];
      m.clear();
      m.rehash(r - l);
      for (int i = l; i < r; i++) {
        assert(b[i] + added[i] <= 250000);
        m[b[i]]++;
      }
    }

    explicit sqrtdec(vector<int> vals) {
      n = vals.size();
//      k = sqrt(n);
      b = std::move(vals);
      b.resize((b.size() + k - 1) / k * k);
      sorted.resize((b.size() + k - 1) / k);
      added.resize(b.size() / k);
      for (int i = 0; i < (int)sorted.size(); i += k) {
        sort(i, i + k);
      }
    }

    void add(int l, int r, int x) {
      r++;
      int b1 = l / k;
      int b2 = (r - 1) / k;
      while (l % k && l < r) {
        b[l++] += x;
      }
      while (r % k && l < r) {
        b[--r] += x;
      }
      l /= k;
      r /= k;
      for (int i = l; i < r; i++) {
        added[i] += x;
      }
      sort(b1 * k, b1 * k + k);
      if (b1 != b2) {
        sort(b2 * k, b2 * k + k);
      }
    }

    int cnt(int l, int r, int x) {
      int ans = 0;
      r++;
      int b1 = l / k;
      int b2 = (r - 1) / k;
      while (l % k && l < r) {
        if (b[l++] + added[b1] == x) ans++;
      }
      while (r % k && l < r) {
        if (b[--r] + added[b2] == x) ans++;
      }
      l /= k;
      r /= k;
      for (int i = l; i < r; i++) {
        auto it = sorted[i].find(x - added[i]);
        if (it != sorted[i].end()) {
          ans += it->second;
        }
      }
      return ans;
    }
  };

  vector<int> ss(n);
  for (int i = 0; i < n; i++) ss[i] = -i;
  sqrtdec s(ss);

  int L = 0, R = 1, Ri = 0;

  vector<int> deg(n);
  LinkCut lc(n);

  auto can_add = [&](int u, int v) {
    assert(v == R);
    if (u < L || u > R) return true;

    return deg[u] < 2 && deg[v] < 2 && !lc.connected(u, v);
  };
  auto add = [&](int u, int v) {
    assert(v == R);
    if (u < L || u > R) return;

    deg[u]++;
    deg[v]++;
    lc.link(u, v);
  };
  auto del = [&](int u, int v) {
    assert(v == L);
    if (u < L || u > R) return;
    if (lc.connected(u, v)) {
      deg[u]--;
      deg[v]--;
      lc.cut(u, v);
    }
  };
  auto enable_edge = [&]( int v, int delta) {
    s.add(v, n - 1, delta);
  };

  ll ans = 0;
  for (L = 0; L < n; L++) {
    while (R < n) {
      if (Ri == (int)e[R].size()) {
        int cnt = 0;
        for (int u : e[R]) {
          if (L <= u && u <= R) {
            cnt++;
          }
        }
        enable_edge(R, cnt);
        Ri = 0;
        R++;
        continue;
      }
      if (can_add(e[R][Ri], R)) {
        add(e[R][Ri], R);
        Ri++;
      } else break;
    }

    ans += s.cnt(L, R - 1, 0);

    for (int u : e[L]) {
      if (L <= u && u < R) {
        enable_edge(u, -1);
      }
      del(u, L);
    }
    s.add(0, n - 1, +1);
  }
  return ans;
}

void test(int n) {
  vector<vector<int>> e(n);
  for (int i = 0; i < n; i++) {
    int j = (i + 1) % n;
    e[i].push_back(j);
    e[j].push_back(i);
  }
  ll res = solve(e);
  printf("%lld\n", res);
  exit(0);
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
#endif
    test(2.5e5);

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<vector<int>> e(n);
    for (int i = 0; i < m; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      u--; v--;
      e[u].push_back(v);
      e[v].push_back(u);
    }

    printf("%lld\n", solve(e));
  }

  return 0;
}
