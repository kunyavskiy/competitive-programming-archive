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
  freopen("k.in", "r", stdin);
//  freopen("k.out", "w", stdout);
#endif

  int T;
  scanf("%d", &T);
  for (int test = 1; test <= T; test++) {
    int n;
    scanf("%d", &n);
    vector<vector<int>> e(n);
    for (int i = 0; i < n - 1; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      u--; v--;
      e[u].push_back(v);
      e[v].push_back(u);
    }

    struct res {
      int cnt;
      set<int> *st;

      void add(int x) {
        auto it = st->lower_bound(x);
        if (it != st->end() && *it == x + 1) cnt--;
        if (it != st->begin() && *(--it) == x - 1) cnt--;
        st->insert(x);
        cnt++;
      }
    };

    vector<int> ans(n);
    vector<set<int>> sets(n);
    function<res(int, int)> dfs = [&](int v, int pr) {
      res cur;
      cur.cnt = 0;
      cur.st = &sets[v];
      cur.add(v);

      for (int to : e[v]) {
        if (to == pr) continue;
        res nw = dfs(to, v);
        if (nw.st->size() > cur.st->size()) swap(cur, nw);

        for (int x : *nw.st) {
          cur.add(x);
        }
      }
      ans[v] = cur.cnt;

      return cur;
    };
    dfs(0, -1);

    printf("Case #%d:", test);
    for (int x : ans) printf(" %d", x);
    printf("\n");
  }

  return 0;
}
