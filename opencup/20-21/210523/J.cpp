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

vector<int> solve(vector<vector<int>> g, vector<int> val) {
  int n = g.size();
  int id = min_element(val.begin(), val.end()) - val.begin();
  if (val[id] == 0) {
    vector<int> res;
    res.push_back(id);
    for (int i = 0; i < n; i++) {
      if (i != id) res.push_back(i);
    }
    return res;
  }

  int id2 = min_element(val.begin() + id + 1, val.end()) - val.begin();
  vector<vector<int>> parts;

  auto dfs = [&](int v, int p, int d, vector<int>& to, auto dfs) {
    if (d == 0) {
      to.push_back(v);
      return;
    }
    for (int u : g[v]) {
      if (u != p) {
        dfs(u, v, d - 1, to, dfs);
      }
    }
  };

  int D;
  if (id2 == n || val[id2] > val[id]) {
    D = 2 * val[id];
    parts.resize(g[id].size());
    for (int i = 0; i < (int)g[id].size(); i++) {
      dfs(g[id][i], id, val[id] - 1, parts[i], dfs);
    }
  } else {
    D = 2 * val[id] - 1;
    parts.resize(2);
    dfs(id, id2, val[id] - 1, parts[0], dfs);
    dfs(id2, id, val[id] - 1, parts[1], dfs);
  }
  vector<pair<int, int>> ans(n);
  for (int i = 0; i < n; i++) {
    ans[i].second = i;
    if (val[i] == D) {
      ans[i].first = -1;
    } else if (val[i] < D) {
      ans[i].first = n + 1;
    } else {
      ans[i].first = n + 2;
    }
  }
  for (const auto& p : parts) {
    for (int x : p) {
      assert(ans[x].first == -1);
      ans[x].first = p.size();
    }
  }
  sort(ans.begin(), ans.end());
  vector<int> res(n);
  for (int i = 0; i < n; i++) {
    assert(ans[i].first != -1);
    res[i] = ans[i].second;
  }
  return res;
}

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a, --b;
      g[a].push_back(b);
      g[b].push_back(a);
    }
    vector<int> val(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &val[i]);
    }
    auto res = solve(g, val);
    for (auto x : res) printf("%d ", x + 1);
    printf("\n");
  }

  return 0;
}
