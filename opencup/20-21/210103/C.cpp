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

struct dsu {
  vector<int> p;
  vector<int> size;
  explicit dsu(int n = 0) : p(n), size(n){
    for (int i = 0; i < n; i++) {
      p[i] = i;
      size[i] = 1;
    }
  }

  int get(int x) {
    if (x == p[x]) return x;
    return p[x] = get(p[x]);
  }

  void join(int a, int b) {
    a = get(a);
    b = get(b);
    if (a == b) return;
    if (a > b) swap(a, b);
    p[b] = a;
    size[a] += size[b];
  }

  dsu cut(int nsize) {
    dsu n(0);
    n.p = vector<int>(p.begin(), p.begin() + nsize);
    n.size = vector<int>(size.begin(), size.begin() + nsize);
    return n;
  }

  void merge(const dsu& other) {
    int old_size = p.size();
    p.resize(old_size + other.p.size());
    size.resize(old_size + other.p.size());
    for (int i = 0; i < (int)other.p.size(); i++) {
      p[old_size + i] = other.p[i] + old_size;
      size[old_size + i] = other.size[i];
    }
  }

  bool has_size(int need_size) {
    return find(size.begin(), size.end(), need_size) != size.end();
  }
};

vector<int> solve_one(vector<vector<char>> v) {
  int n = v.size();
  int m = v[0].size();
  vector<dsu> lf(m), rg(m);
  auto encode = [&](int i, int j) {
    return j * n + i;
  };
  auto empty = [&](int i, int j) {
    return 0 <= i && i < n && 0 <= j && j < m && v[i][j] == '.';
  };
  vector<int> res;
  int need_cnt = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (empty(i, j)) {
        need_cnt++;
      }
    }
  }

  for (int it = 0; it < 2; it++) {
    dsu d(v.size() * v[0].size());
    auto try_join = [&](int x1, int y1, int x2, int y2) {
      if (empty(x1, y1) && empty(x2, y2)) {
        d.join(encode(x1, y1), encode(x2, y2));
      }
    };
    for (int i = 0; i < n; i++) {
      try_join(i, 0, i + 1, 0);
    }
    lf[0] = d.cut(n);
    for (int j = 1; j < m; j++) {
      for (int i = 0; i < n; i++) {
        try_join(i, j, i, j - 1);
        try_join(i, j, i + 1, j);
      }
      lf[j] = d.cut(n);
    }
    for (auto &x : v) {
      reverse(x.begin(), x.end());
    }
    lf.swap(rg);
    if (it == 0 && d.has_size(need_cnt)) {
      res.push_back(0);
    }
  }


  for (int j = 0; j < m - 1; j++) {
    dsu d = lf[j];
    d.merge(rg[m - j - 2]);
    for (int i = 0; i < n; i++) {
      if (empty(i, 0) && empty(i, m - 1)) {
        d.join(i, i + n);
      }
    }
    if (d.has_size(need_cnt)) {
      res.push_back(j + 1);
    }
  }
  return res;
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<vector<char>> v(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        scanf(" %c", &v[i][j]);
      }
    }

    vector<pair<int, int>> ans;
    for (int i = 0; i < n; i++) {
      auto res = solve_one(v);
      for (int a : res) {
        ans.emplace_back(i, a);
      }
      auto x = v[0];
      v.erase(v.begin());
      v.push_back(x);
    }
    printf("%zd\n", ans.size());
    for (auto [a, b] : ans) {
      printf("%d %d\n", a, b);
    }
  }

  return 0;
}
