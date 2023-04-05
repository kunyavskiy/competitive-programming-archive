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
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


using namespace std;

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");

#else
struct __timestamper {};
#endif

const int MOD = 1000000007;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) {
  return mpow(x, MOD - 2);
}

typedef long long ll;
typedef long double ld;

vector<int> min_out;
vector<vector<int>> g;
vector<vector<int>> gr;
vector<char> z;

void dfs(int x) {
  if (z[x]) return;
  z[x] = true;
  for (int y : gr[x]) {
    dfs(y);
  }
}

void solve_test() {
  int n, m;
  scanf("%d%d", &n, &m);
  min_out.assign(n, 10);
  g.assign(n, vector<int>(0));
  gr.assign(n, vector<int>(0));

  vector<int> x(m), y(m), w(m);
  for (int i = 0; i < m; i++) {
    scanf("%d%d%d", &x[i], &y[i], &w[i]);
    gr[y[i]].push_back(x[i]);
  }

  z.clear();
  z.resize(n);
  dfs(1);

  assert(z[0]);

  for (int i = 0; i < m; i++) {
    if (!z[y[i]]) continue;
    if (w[i] < min_out[x[i]]) {
      min_out[x[i]] = w[i];
      g[x[i]].clear();
    }
    if (w[i] == min_out[x[i]]) {
      g[x[i]].push_back(y[i]);
    }
  }

  vector<char> s;
  vector<int> cur = {0};
  vector<int> next;
  vector<int> last(n, -1);
  for (int i = 0; i < 3 * n; i++) {
    int q = 10;
    for (int x : cur) {
      q = min(q, min_out[x]);
    }
    s.push_back(q);
    next.clear();
    for (int x : cur) {
      if (min_out[x] == q) {
        for (int y : g[x]) {
          if (last[y] != i) {
            last[y] = i;
            next.push_back(y);
          }
        }
      }
    }

    if (last[1] == i) {
      int res = 0;
      int p = 1;
      int i10 = minv(10);
      for (int q : s) {
        p = mul(p, i10);
        add(res, mul(p, q));
      }
      cout << res << "\n";
      return;
    }

    next.swap(cur);
  }

  int p;
  for (p = 1; ; p++) {
    assert(p <= n);
    bool ok = true;
    for (int i = n; i + p < (int)s.size(); i++) {
      if (s[i] != s[i + p]) ok = false;
    }
    if (ok) break;
  }

//  for (int q : s) {
//    cerr << q;
//  }
//  cerr << "\n";
//  cerr << p << "\n";

  int res = 0;
  int pp = 1;
  int i10 = minv(10);
  for (int i = 0; i < n; i++) {
    int q = s[i];
    pp = mul(pp, i10);
    add(res, mul(pp, q));
  }
  int ps = 0;
  int qq = 1;
  for (int i = n; i < n + p; i++) {
    int q = s[i];
    qq = mul(qq, i10);
    pp = mul(pp, i10);
    add(ps, mul(pp, q));
  }
  int e = 1;
  sub(e, qq);

  add(res, mul(ps, minv(e)));
  cout << res << "\n";
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    cout << "Case #" << (i + 1) << ": ";
    solve_test();
  }

  return 0;
}
