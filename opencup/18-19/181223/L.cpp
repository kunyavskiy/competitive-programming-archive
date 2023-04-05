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

int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  //freopen("l.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }

    vector<vector<int>> e(n);
    for (int i = 0; i < m; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      u--; v--;
      e[u].push_back(v);
      e[v].push_back(u);
    }

    vector<int> d(n, 2);
    for (int i = 0; i < n; i++) {
      sort(e[i].begin(), e[i].end());
      e[i].resize(unique(e[i].begin(), e[i].end()) - e[i].begin());

      for (int to : e[i]) {
        if (a[to] != a[i]) {
          d[i] = 1;
        }
      }
    }

    vector<int> cnt(2);
    for (int x : a) cnt[x]++;

    vector<int> sum(2);
    for (int i = 0; i < n; i++) sum[a[i]] += d[i];

    vector<int> p(n);
    for (int i = 0; i < n; i++) p[i] = i;
    function<int(int)> get = [&](int x) {
      if (x == p[x]) return x;
      return p[x] = get(p[x]);
    };
    auto uni = [&](int u, int v) {
      u = get(u);
      v = get(v);
      if (u == v) return;
      p[v] = u;
    };

    for (int u = 0; u < n; u++) for (int to : e[u]) uni(u, to);

    vector<vector<int>> cc(n, vector<int>(2));
    for (int i = 0; i < n; i++) cc[get(i)][a[i]]++;


    for (int i = 0; i < n; i++) {
      int cost = 0;
      cost += cnt[a[i]] - 1;
      //cost += sum[a[i] ^ 1];

      int oth = cnt[a[i] ^ 1];
      /*for (int to : e[i]) {
        if (a[to] != a[i]) {
          oth--;
          cost -= d[to];
          cost += 1;
        }
      }
      cost += oth;*/
      int neib = 0;
      for (int to : e[i]) if (a[to] != a[i]) neib++;

      if (neib) {
        cost += neib + 2 * (oth - neib);
      } else {
        cost += oth + sum[a[i] ^ 1];
      }

      //if (!any) cost += oth;

      printf("%d%c", cost, " \n"[i + 1 == n]);
    }
  }

  return 0;
}
