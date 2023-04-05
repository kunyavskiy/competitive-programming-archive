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
  int n;
  vector<int> p;
  vector<int> cnt;

  dsu(int _n) {
    n = _n;
    p.resize(n);
    cnt.assign(n, 1);
    iota(p.begin(), p.end(), 0);
  }

  int get(int x) {
    return x == p[x] ? x : p[x] = get(p[x]);
  }

  void uni(int u, int v) {
    u = get(u);
    v = get(v);
    if (u == v) return;
    if (cnt[u] < cnt[v]) swap(u, v);
    p[v] = u;
    cnt[u] += cnt[v];
  }
};

const int dx[3] = {1, 0, 0};
const int dy[3] = {0, -1, 1};

int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
//  freopen("l.out", "w", stdout);
#endif

  int n, m, t;
  while (cin >> n >> m >> t) {
    vector<string> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];


    auto get_id = [&](int x, int y) {
      if (x < 0 || y < 0 || x >= n || y >= m) return -1;
      if (a[x][y] == '#') return -1;
      return x * m + y;
    };

    dsu d(n * m);
    int ans = -1;
    for (int i = n - 1; i >= 0; i--) {
      for (int j = 0; j < m; j++) {
        for (int k = 0; k < 3; k++) {
          int u = get_id(i, j);
          int v = get_id(i + dx[k], j + dy[k]);
          if ((u != -1 || v != -1) && t == 1) {
            ans = i + 1;
          }
          if (u == -1 || v == -1) continue;
          d.uni(u, v);
          if (d.cnt[d.get(u)] >= t) {
            ans = i + 1;
          }
        }
      }
      if (ans != -1) break;
    }
    cout << ans << endl;
  }

  return 0;
}
