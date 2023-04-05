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

const pair<int, int> dirs[] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

struct query {
  int i, j, p;
  ll a, b, c;
};

struct point {
  ll x, y;
  int hpl() const {
    if (y > 0 || (y == 0 && x > 0)) return 0;
    return 1;
  }
  bool operator==(const point &rhs) const {
    return std::tie(x, y) == std::tie(rhs.x, rhs.y);
  }
  bool operator!=(const point &rhs) const {
    return !(rhs == *this);
  }
};

point operator-(const point& a, const point &b) {
  return {a.x - b.x, a.y - b.y};
}

ll operator*(const point& a, const point &b) {
  return a.x * b.y - a.y * b.x;
}



struct Hull {
  vector<point> v;
  vector<point> diffs;
  void add(ll x, ll y) {
    v.push_back({x, y});
  }
  void build() {
    iter_swap(v.begin(), min_element(v.begin(), v.end(), [](const point &a, const point&b) {
                return tie(a.y, a.x) < tie(b.y, b.x);
              }));
    sort(v.begin() + 1, v.end(), [&](const point& a, const point& b) {
      ll x = (a - v[0]) * (b - v[0]);
      if (x != 0) return x > 0;
      return abs((a - v[0]).x) < abs((b - v[0]).x);
    });
    vector<point> res;
    auto good = [](const point& a, const point& b, const point& c) {
      return (c - a) * (c - b) > 0;
    };
    for (auto p : v) {
      while (res.size() >= 2 && !good(res[res.size() - 2], res[res.size() - 1], p)) {
        res.pop_back();
      }
      res.push_back(p);
    }
    v = std::move(res);
    v.push_back(v[0]);
    v.erase(unique(v.begin(), v.end()), v.end());
    for (int i = 1; i < (int)v.size(); i++) {
      diffs.push_back(v[i] - v[i - 1]);
    }
  }

  ll get(ll a, ll b) const {
    if (diffs.size() == 1) {
      return v[0].x * a + v[0].y * b;
    }
    if (a == 0 && b == 0) return 0;
    int pos = upper_bound(diffs.begin(), diffs.end(), point{-b, a}, [](const point& a, const point& b) {
      if (a.hpl() != b.hpl()) {
        return a.hpl() < b.hpl();
      }
      return a * b > 0;
    }) - diffs.begin();
    return v[pos].x * a + v[pos].y * b;
  }
};

#ifdef LOCAL
//#define TEST
#endif

struct Solver {
  map<ll, Hull> w;
#ifdef TEST
  vector<pair<ll, ll>> stupid;
#endif
  void add(ll v, ll l) {
    w[l].add(v, v * l);
#ifdef TEST
    stupid.emplace_back(v, l);
#endif
  }
  void build() {
    for (auto &[l, h] : w) {
      h.build();
    }
  }
  ll get(ll a, ll b, ll c) const {
    ll ans = numeric_limits<ll>::min();
    for (const auto &[l, h] : w) {
      ans = max(ans, h.get(a, c) + b * l);
    }
#ifdef TEST
    ll ans2 = numeric_limits<ll>::min();
    for (const auto &[v, l] : stupid) {
      ans2 = max(ans2, v * a + l * b + v * l * c);
    }
    assert(ans == ans2);
#endif
    return ans;
  }
};

void solve() {
  int n;
  scanf("%d", &n);
  vector<vector<int>> cur(n, vector<int>(n));
  vector<vector<int>> v(n, vector<int>(n));
  vector<ll> curv(n * n), curl(n * n), cnt(n * n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &v[i][j]);
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &cur[i][j]);
      curv[cur[i][j]] += v[i][j];
      cnt[cur[i][j]]++;
    }
  }

  auto inside = [&](int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
  };

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (auto [dx, dy] : dirs) {
        int ni = i + dx;
        int nj = j + dy;
        if (inside(ni, nj) && cur[i][j] != cur[ni][nj]) {
          curl[cur[i][j]]++;
        }
      }
    }
  }

  int q;
  scanf("%d", &q);
  vector<query> qs(q);
  for (int i = 0; i < q; i++) {
    scanf("%d%d%d%lld%lld%lld", &qs[i].i, &qs[i].j, &qs[i].p, &qs[i].a, &qs[i].b, &qs[i].c);
    --qs[i].i, --qs[i].j;
  }

  const int BLOCK = sqrt( 6 * q);
  eprintf("BLOCK = %d\n", BLOCK);

  for (int st = 0; st < q; st += BLOCK) {
    vector<int> changes;
    vector<bool> have_changes(n * n);
    int en = min(q, st + BLOCK);
    for (int op = st; op < en; op++) {
      have_changes[cur[qs[op].i][qs[op].j]] = true;
      have_changes[qs[op].p] = true;
      for (auto [dx, dy] : dirs) {
        int ni = qs[op].i + dx;
        int nj = qs[op].j + dy;
        if (inside(ni, nj)) {
          have_changes[cur[ni][nj]] = true;
        }
      }
    }
    Solver sol;
    for (int i = 0; i < n * n; i++) {
      if (cnt[i] > 0 && !have_changes[i]) {
        sol.add(curv[i], curl[i]);
      } else if (have_changes[i]) {
        changes.push_back(i);
      }
    }
    sol.build();

    for (int op = st; op < en; op++) {
      int i = qs[op].i;
      int j = qs[op].j;
      curv[cur[i][j]] -= v[i][j];
      curv[qs[op].p] += v[i][j];
      cnt[cur[i][j]]--;
      cnt[qs[op].p]++;
      for (auto [dx, dy] : dirs) {
        int ni = qs[op].i + dx;
        int nj = qs[op].j + dy;
        if (inside(ni, nj)) {
          if (cur[ni][nj] != cur[i][j]) {
            curl[cur[i][j]]--;
            curl[cur[ni][nj]]--;
          }
          if (cur[ni][nj] != qs[op].p) {
            curl[qs[op].p]++;
            curl[cur[ni][nj]]++;
          }
        }
      }
      cur[i][j] = qs[op].p;
      long long ans = sol.get(qs[op].a, qs[op].b, qs[op].c);
      for (int c : changes) {
        if (cnt[c]) {
          ans = max(ans, qs[op].a * curv[c] + qs[op].b * curl[c] + qs[op].c * curv[c] * curl[c]);
        }
      }
      printf("%lld ", ans);
    }
  }
  printf("\n");
}

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int z;
  scanf("%d", &z);
  while (z-->0) {
    solve();
  }

  return 0;
}
