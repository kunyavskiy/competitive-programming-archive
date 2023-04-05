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
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a, --b;
      g[a].push_back(b);
      g[b].push_back(a);
    }
    vector<int> col(n);
    vector<int> deg(n);
    set<pair<int, int>> s;
    int total_deg = 0;
    for (int i = 0; i < n; i++) {
      s.emplace(deg[i] = g[i].size(), i);
      total_deg += deg[i];
    }
    assert(!s.empty());
    int nn = n;
    assert(total_deg >= 4 * k * nn);
    while (s.begin()->first <= 2 * k) {
      int id = s.begin()->second;
      eprintf("drop %d\n", id);
      s.erase(s.begin());
      col[id] = 2;
      for (int i : g[id]) {
        if (col[i] == 0) {
          s.erase({deg[i], i});
          deg[i]--;
          s.insert({deg[i], i});
        }
      }
      total_deg -= 2 * deg[id];
      nn--;
      assert(total_deg >= 4 * k * nn);
      assert(!s.empty());
    }
    eprintf("done droping\n");
    for (int i = 0; i < n; i++) {
      if (col[i] == 2) {
        g[i].clear();
      } else {
        g[i].erase(remove_if(g[i].begin(), g[i].end(), [&](int x) { return col[x] == 2; }), g[i].end());
        assert((int)g[i].size() == deg[i]);
        assert(deg[i] > 2 * k);
      }
    }
    vector<int> deg2(n);
    s.clear();
    for (int i = 0; i < n; i++) {
      if (col[i] != 2) {
        s.emplace(0, i);
      }
    }

    int total_deg2 = 0;
    while (s.begin()->first <= k) {
      int id = s.begin()->second;
      s.erase(s.begin());
      assert(deg2[id] <= k);
      eprintf("total = %d, move %d, deg %d -> %d\n", total_deg2, id, deg2[id], deg[id] - deg2[id]);
      total_deg2 -= deg2[id];
      deg2[id] = deg[id] - deg2[id];
      total_deg2 += deg2[id];
      s.emplace(deg2[id], id);
      for (int i : g[id]) {
        s.erase({deg2[i], i});
        if (col[i] == col[id]) {
          total_deg2++;
          deg2[i]++;
        } else {
          total_deg2--;
          deg2[i]--;
        }
        s.insert({deg2[i], i});
      }
      col[id] = 1 - col[id];
    }
    vector<int> r, b;
    for (int i = 0; i < n; i++) {
      if (col[i] == 0) r.push_back(i);
      else if (col[i] == 1) b.push_back(i);
    }
    for (auto x : {r, b}) {
      printf("%d", (int)x.size());
      for (int i : x)
          printf(" %d", i + 1);
      printf("\n");
    }
  }

  return 0;
}
