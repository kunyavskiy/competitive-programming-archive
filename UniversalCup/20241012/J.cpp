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
#include <numeric>
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
#include <optional>

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

const int MOD1 = 1000000007;
const int MOD2 = 1000000009;

struct HV {
  int f, s;

  bool operator<(const HV &rhs) const {
    if (f != rhs.f)
      return f < rhs.f;
    return s < rhs.s;
  }

  bool operator==(const HV &x) const { return f == x.f && s == x.s; }
};

HV operator+(const HV &a, const HV &b) {
  return {(a.f + b.f) % MOD1, (a.s + b.s) % MOD2};
}

HV operator-(const HV &a, const HV &b) {
  return {(a.f - b.f + MOD1) % MOD1, (a.s - b.s + MOD2) % MOD2};
}

HV operator*(const HV &a, const HV &b) {
  return {(int)((a.f * 1LL * b.f) % MOD1), (int)((a.s * 1LL * b.s) % MOD2)};
}

const int MAXN = 210'000;

HV pw[MAXN];

struct Tree {
  vector<int> parent;
  vector<vector<int>> g;
  explicit Tree(int n) : parent(n) {
    if (n >= 1) parent[0] = -1;
  }
  void buildg() {
    assert(parent.size() > 0);
    assert(parent[0] == -1);
    g.clear();
    g.resize(parent.size());
    for (int i = 1; i < (int)parent.size(); i++) {
      g[parent[i]].push_back(i);
    }
  }
};

Tree readTree(int n) {
  Tree res(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &res.parent[i]);
    --res.parent[i];
  }
  res.buildg();
  return res;
}

Tree mul(Tree a, const Tree& b) {
  int asz = a.parent.size();
  a.parent.resize(a.parent.size() * b.parent.size());
  for (int v = 0; v < asz; v++) {
    int shift = asz + v * ((int)b.parent.size() - 1) - 1;
    for (int i = 1; i < (int)b.parent.size(); i++) {
      a.parent.at(i + shift) = (b.parent[i] ? b.parent[i] + shift : v);
    }
  }
  a.buildg();
  return a;
}

Tree subtree(const Tree &a, int r) {
  Tree t(0);
  auto dfs = [&](auto self, int v, int p) -> void {
    int my_id = t.parent.size();
    t.parent.push_back(p);
    for (int u : a.g[v]) {
      self(self, u, my_id);
    }
  };
  dfs(dfs, r, -1);
  t.buildg();
  return t;
}

void print(const Tree&g, const Tree& g2) {
  printf("%d %d\n", (int)g.parent.size(), (int)g2.parent.size());
  for (int i = 0; i < (int)g.parent.size(); i++) {
    printf("%d%c", g.parent[i]+1, " \n"[i == (int)g.parent.size() - 1]);
  }
  for (int i = 0; i < (int)g2.parent.size(); i++) {
    printf("%d%c", g2.parent[i]+1, " \n"[i == (int)g2.parent.size() - 1]);
  }
}

vector<int> heights(const Tree&g) {
  vector<int> h(g.parent.size());
  for (int i = 1; i < (int)g.parent.size(); i++) {
    h[i] = h[g.parent[i]] + 1;
  }
  return h;
}

vector<HV> hashes(const Tree& a) {
  vector<HV> v(a.parent.size());
  vector<int> len(a.parent.size());
  auto combine = [](HV a, int l1, HV b, int l2) {
    return pair{a + b * pw[l1], l1 + l2};
  };
  for (int i = a.parent.size() - 1; i >= 0; i--) {
    vector<pair<HV, int>> ch;
    ch.reserve(a.g[i].size());
    for (int x : a.g[i]) {
      ch.emplace_back(v[x], len[x]);
    }
    sort(ch.begin(), ch.end());
    pair<HV, int> cur = {HV{1, 1}, 1};
    for (auto x : ch) {
      cur = combine(cur.first, cur.second, x.first, x.second);
    }
    cur = combine(cur.first, cur.second, HV{2,2}, 1);
    v[i] = cur.first;
    len[i] = cur.second;
  }
  return v;
}

std::optional<Tree> subtract(const Tree& a, const Tree& b) {
  vector<HV> ha = hashes(a);
  vector<HV> hb = hashes(b);
  map<HV, vector<int>> m;
  for (auto u : a.g[0]) {
    m[ha[u]].push_back(u);
  }
  for (auto v : b.g[0]) {
    auto& x = m[hb[v]];
    if (x.empty()) {
      return nullopt;
    }
    x.pop_back();
  }

  Tree t(1);
  t.parent[0] = -1;
  auto dfs = [&](auto self, int v, int p) -> void {
    int my_id = t.parent.size();
    t.parent.push_back(p);
    for (int u : a.g[v]) {
      self(self, u, my_id);
    }
  };
  for (const auto & [_, x]: m) {
    for (auto y : x) {
      dfs(dfs, y, 0);
    }
  }
  t.buildg();
  return t;
}

std::optional<pair<Tree, Tree>> decompose(const Tree &a, const Tree& c) {
  auto ha = heights(a);
  auto hc = heights(c);
  int max_ha = *max_element(ha.begin(), ha.end());
  int max_hc_v = max_element(hc.begin(), hc.end()) - hc.begin();
  int max_hc = hc[max_hc_v];
  if (max_hc < max_ha) return nullopt;
  if (max_hc == max_ha) {
    auto x = Tree(1);
    x.buildg();
    std::optional<Tree> d = subtract(c, a);
    if (d.has_value()) return {{x, *d}};
    return nullopt;
  }
  int rx = max_hc_v;
  for (int i = 0; i < max_hc - max_ha; i++) {
    rx = c.parent[rx];
  }
  Tree x = subtree(c, rx);
  if (x.parent.size() * a.parent.size() > c.parent.size()) return std::nullopt;
  auto d = subtract(c, mul(a, x));
  if (d.has_value()) return {{x, *d}};
  return nullopt;
}

std::optional<pair<Tree, Tree>> solve(Tree a, Tree b, Tree c) {
  auto r1 = decompose(a, c);
  if (!r1.has_value()) return nullopt;
  auto r2 = decompose(b, r1->second);
  if (!r2.has_value()) return nullopt;
  if (r2->second.parent.size() != 1) return nullopt;
  return {{r1->first, r2->first}};
}

void solve() {
  int na, nb, nc;
  scanf("%d%d%d", &na, &nb, &nc);
  auto a = readTree(na);
  auto b = readTree(nb);
  auto c = readTree(nc);

  auto r1 = solve(a, b, c);
  if (r1.has_value()) {
    print(r1->first, r1->second);
    return;
  }
  auto r2 = solve(b, a, c);
  if (r2.has_value()) {
    print(r2->second, r2->first);
    return;
  }
  printf("Impossible\n");
}

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  pw[0] = {1,1};
  for (int i = 1; i < MAXN; i++) {
    pw[i] = pw[i - 1] * HV{1000003, 1000033};
  }

  int t;
  scanf("%d", &t);
  while (t-->0) solve();
  return 0;
}
