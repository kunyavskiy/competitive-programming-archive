#include <cstdio>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

#define MOD 1000000007
#define MIN_INT -2147483648
#define MAX_INT 2147483647
#define MIN_LONG -9223372036854775808L
#define MAX_LONG 9223372036854775807L
#define PI 3.141592653589793238462643383279502884L

#define long long long int

using std::vector;
using std::map;
using std::set;
using std::string;
using std::pair;
using std::cin;
using std::cout;
using std::cerr;

// @author: pashka

vector<vector<pair<int, long>>> g;
vector<bool> z;

int size(int x, int p) {
  int res = 1;
  for (auto y : g[x]) {
    if (y.first != p && !z[y.first]) {
      res += size(y.first, x);
    }
  }
  return res;
}

int centroid;

int find_centroid(int x, int p, int n) {
  int res = 1;
  bool ok = true;
  for (auto y : g[x]) {
    if (y.first != p && !z[y.first]) {
      int s = find_centroid(y.first, x, n);
      if (s > n / 2) ok = false;
      res += s;
    }
  }
  if (res < n / 2) ok = false;
  if (ok) {
    centroid = x;
  }
  return res;
}

vector<vector<pair<int, long>>> up; // pairs (centroid, distance), from top

void add_dist(int x, int p, int c, long d) {
  up[x].push_back({c, d});
  for (auto y : g[x]) {
    if (y.first != p && !z[y.first]) {
      add_dist(y.first, x, c, d + y.second);
    }
  }
}

void build_centroid(int x, int p) {
  int n = size(x, p);
  find_centroid(x, p, n);

  x = centroid;

  add_dist(x, -1, x, 0);

  z[x] = true;

  for (auto y : g[x]) {
    if (!z[y.first]) {
      build_centroid(y.first, x);
    }
  }
}

struct Fen {
  vector<long> x;
  vector<int> f;

  Fen() { }

  void init() {
    f.assign(x.size() + 1, 0);
  }

  long sum(int r) { // exclusive
    if (r == 0)
      return 0;
    r--;
    long result = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1)
      result += f[r];
    return result;
  }

  void inc(int i, int d) {
    for (; i < f.size(); i = (i | (i + 1)))
      f[i] += d;
  }

  int sum(int l, int r) {
    return (r - l + 1) - (sum(r) - sum(l - 1));
  }
};

vector<Fen> all;
vector<Fen> mine;

void add(int i, int d) { // updates sum for all centroids above
  for (int j = 0; j < up[i].size(); j++) {
    auto p = up[i][j];
    int x = std::lower_bound(all[p.first].x.begin(), all[p.first].x.end(), p.second) - all[p.first].x.begin();
    all[p.first].inc(x, d);
    if (j < up[i].size() - 1) {
      auto pp = up[i][j + 1];
      int x = std::lower_bound(mine[pp.first].x.begin(), mine[pp.first].x.end(), p.second) - mine[pp.first].x.begin();
      mine[pp.first].inc(x, d);
    }
  }
}

long L;

int calc(int i) {
  int res = 0;
  for (int j = 0; j < up[i].size(); j++) {
    auto p = up[i][j];
    // d <= L - p.second
    int x = std::upper_bound(all[p.first].x.begin(), all[p.first].x.end(), L - p.second) - all[p.first].x.begin();
    res += all[p.first].sum(x);
    if (j < up[i].size() - 1) {
      auto pp = up[i][j + 1];
      int x = std::upper_bound(mine[pp.first].x.begin(), mine[pp.first].x.end(), L - p.second) - mine[pp.first].x.begin();
      res -= mine[pp.first].sum(x);
    }
  }
  return res;
}

vector<pair<long, int>> dd;
vector<pair<long, int>> stack;
vector<int> up2;

void calc_dist(int x, int p, long d) {
  dd.push_back({d, x});
  stack.push_back({d, x});
  for (auto y : g[x]) {
    if (y.first != p) {
      calc_dist(y.first, x, d + y.second);
    }
  }
  int l = -1;
  int r = stack.size() - 1;
  while (r > l + 1) {
    int m = (l + r) / 2;
    if (d - stack[m].first > L) {
      l = m;
    } else {
      r = m;
    }
  }
  up2[x] = stack[r].second;
  stack.pop_back();
}

vector<long> fact(100005);
vector<long> invFact(100005);

long pow(long a, long b) {
  long res = 1;
  while (b > 0) {
    if (b % 2 == 1) {
      res = (res * a) % MOD;
    }
    a = (a * a) % MOD;
    b /= 2;
  }
  return res;
}

long calc_c(int n, int k) {
  long res = fact[n];
  res = (res * invFact[k]) % MOD;
  res = (res * invFact[n - k]) % MOD;
  return res;
}


int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
#endif
  std::ios::sync_with_stdio(false);

  int n, k;
  cin >> n >> k >> L;

  fact[0] = invFact[0] = 1;
  for (int i = 1; i <= n; i++) {
    fact[i] = (fact[i - 1] * i) % MOD;
    invFact[i] = pow(fact[i], MOD - 2);
  }

//    c.resize(n);

  g.resize(n);
  for (int i = 0; i < n - 1; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    x--;
    y--;
    g[x].push_back({y, w});
    g[y].push_back({x, w});
  }
  z.resize(n);
  up.resize(n);
  build_centroid(0, -1);


  all.resize(n);
  mine.resize(n);
  up2.resize(n);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < up[i].size(); j++) {
      auto p = up[i][j];
      all[p.first].x.push_back(p.second);
      if (j < up[i].size() - 1) {
        auto pp = up[i][j + 1];
        mine[pp.first].x.push_back(p.second);
      }
    }
  }

  for (int i = 0; i < n; i++) {
    std::sort(all[i].x.begin(), all[i].x.end());
    all[i].init();
    std::sort(mine[i].x.begin(), mine[i].x.end());
    mine[i].init();
  }

  for (int i = 0; i < n; i++) {
    add(i, 1);
  }

  calc_dist(0, -1, 0);
  std::sort(dd.begin(), dd.end());

  int res = 0;

  for (int i = n - 1; i >= 0; i--) {
    int v = dd[i].second;
    add(v, -1);
    int c = up2[v];
    int q = calc(c);
    fprintf(stderr, "v = %d, c = %d, q = %d, k = %d\n", v, c, q, k);
    if (q >= k - 1) {
      res += calc_c(q, k - 1);
      res %= MOD;
    }
  }

  res = (res * fact[k]) % MOD;

  cout << res;


  return 0;
}