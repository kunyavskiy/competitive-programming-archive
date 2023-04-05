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

const int INF = 1e9;
const int N = 2048;

vector<vector<int>> solve(vector<vector<char>> ee) {
  int n = ee.size();
  vector<bitset<N>> e(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (ee[i][j] == '1') {
        e[i][j] = 1;
      }
    }
  }
  vector<vector<int>> ans;
  for (int start = 0; start < n; start++) {
    bitset<N> cur;
    for (int i = 0; i < n; i++) cur[i] = 1;
    vector<int> q;
    vector<int> d(n, INF);

    cur[start] = 0;
    d[start] = 0;
    q.push_back(start);
    for (int qq = 0; qq < (int)q.size(); qq++) {
      int v = q[qq];
      bitset<N> t = e[v] & cur;
      for (int to = t._Find_first(); to < N; to = t._Find_next(to)) {
        d[to] = d[v] + 1;
        q.push_back(to);
      }
      cur ^= t;
    }

    int mx = *max_element(d.begin(), d.end());
    assert(mx <= n);
    if (mx + 1 > (int)ans.size()) {
      ans.resize(mx + 1);
      for (auto &v : ans) v.clear();
      for (int i = 0; i < n; i++) {
        ans[d[i]].push_back(i);
      }
    }
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("p5.in", "r", stdin);
  //freopen("p5.out", "w", stdout);
#endif

  int n, k;
  while (scanf("%d%d", &n, &k) == 2) {
    vector<vector<char>> ee(n, vector<char>(n));
    for (int i = 0; i < n; i++) {
      static char buf[99999];
      scanf(" %s", buf);
      for (int j = 0; j < n; j++) {
        ee[i][j] = buf[j];
      }
    }

    vector<vector<int>> ans;
    vector<char> vis(n);
    for (int i = 0; i < n; i++) {
      if (vis[i] != 0) continue;
      vector<int> q;
      q.push_back(i);
      vis[i] = 1;
      for (int qq = 0; qq < (int)q.size(); qq++) {
        int v = q[qq];
        for (int to = 0; to < n; to++) {
          if (ee[v][to] == '1' && !vis[to]) {
            vis[to] = 1;
            q.push_back(to);
          }
        }
      }
      int m = q.size();
      vector<vector<char>> ne(m, vector<char>(m));
      for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
          ne[i][j] = ee[q[i]][q[j]];
        }
      }
      auto nans = solve(ne);
      for (auto vct : nans) {
        for (int &v : vct) {
          v = q[v];
        }
        ans.push_back(vct);
      }
    }


    if ((int)ans.size() < k) {
      printf("Nope\n");
    } else {
      printf("Yep\n");
      while ((int)ans.size() > k) {
        for (int x : ans.back()) ans[k - 1].push_back(x);
        ans.pop_back();
      }
      int sum = 0;
      for (auto v : ans) sum += v.size();
      assert(sum == n);
      for (int i = 0; i < k; i++) {
        assert(!ans[i].empty());
        printf("%d", (int)ans[i].size());
        for (int v : ans[i]) printf(" %d", v + 1);
        printf("\n");
      }
    }
  }

  return 0;
}
