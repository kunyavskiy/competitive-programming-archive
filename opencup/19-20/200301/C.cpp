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
typedef long double dbl;

struct circle {
  int x, y;
  int r;
  int id;
};

//const dbl EPS = 0;
const dbl EPS = 1e-9;

int x;
struct arc {
  circle c;
  int dir;

  dbl y() const {
    dbl dy = sqrt(1LL * c.r * c.r - 1LL * (c.x - x) * (c.x - x)) + EPS;
    return c.y + dy * dir;
  }

  bool operator< (const arc &a) const {
    return y() < a.y();
  }
};

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
//  freopen("c.out", "w", stdout);
#endif

  int n, q;
  while (scanf("%d%d", &n, &q) == 2) {
    int m = n + q + 1;

    vector<circle> a(m);
    a[0] = circle{0, 0, (int)1e9, 0};
    for (int i = 1; i < m; i++) {
      scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].r);
      a[i].id = i;
    }

    auto is_query = [&](int v) {
      return v > n;
    };

    vector<pair<int, int>> ev;
    for (int i = 1; i < m; i++) {
      ev.push_back({a[i].x - a[i].r, i});
      ev.push_back({a[i].x + a[i].r, ~i});
    }

    set<arc> st;
    x = -1e8;
    st.insert({a[0], -1});
    st.insert({a[0], +1});

    sort(ev.begin(), ev.end());
    vector<int> p(m);

    for (auto o : ev) {
      x = o.first;

      int id = o.second >= 0 ? o.second : ~o.second;
      arc up{a[id], +1};
      arc down{a[id], -1};

      if (o.second >= 0) {
        auto it = st.lower_bound(up);
        assert(it != st.end());
        if (it->dir == +1) {
          p[id] = it->c.id;
        } else {
          p[id] = p[it->c.id];
        }
        st.insert(up);
        st.insert(down);
      } else {
        st.erase(up);
        st.erase(down);
      }
    }

    vector<vector<int>> e(m);
//    db(m);
//    dbv(p);
    for (int i = 1; i < m; i++) {
      e[p[i]].push_back(i);
    }

    vector<vector<int>> dp(m, vector<int>(2));
    function<void(int)> dfs = [&](int v) {
      for (int to : e[v]) dfs(to);

      for (int c = 0; c < 2; c++) {
        dp[v][c] = c;
        for (int to : e[v]) {
          int cur = 0;
          if (is_query(to)) {
            cur = dp[to][c];
            if (c == 1) cur--;
          } else {
            cur = dp[to][0];
            if (c == 0) cur = max(cur, dp[to][1]);
          }
          dp[v][c] += cur;
        }
      }
    };
    dfs(0);
    for (int i = 0; i < q; i++) {
      printf("%d\n", max(dp[n + 1 + i][0], dp[n + 1 + i][1]));
    }
  }

  return 0;
}
