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
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<set<int>> g(n);
    for (int i = 0; i < m; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      --x, --y;
      g[x].insert(y);
      g[y].insert(x);
    }
    vector<bool> inq(n);
    queue<int> q;
    for (int i = 0; i < n; i++) {
      if (g[i].size() == 2) {
        q.push(i);
        inq[i] = true;
      }
    }

    int done = 0;

    while (!q.empty()) {
      int v = q.front();
      q.pop();
      if (g[v].size() < 2) {
        continue;
      }
      done++;
      assert(g[v].size() == 2);
      int s = *g[v].begin();
      int t = *g[v].rbegin();
      g[s].erase(v);
      g[t].erase(v);
      g[s].insert(t);
      g[t].insert(s);
      if (!inq[s] && g[s].size() == 2) {
        inq[s] = true;
        q.push(s);
      }
      if (!inq[t] && g[t].size() == 2) {
        inq[t] = true;
        q.push(t);
      }
    }

    if (done == n - 2) {
      printf("Yes\n");
    } else {
      printf("No\n");
    }
  }

  return 0;
}
