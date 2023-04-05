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

int k_est;

vector<vector<int>> get_coloring(const vector<vector<int>> &g) {
  if (g.empty()) return {};
  priority_queue<pair<int, int>> s;
  vector<int> deg(g.size());
  vector<int> order;
  for (int i = 0; i < (int)g.size(); i++) {
    deg[i] = g[i].size();
    s.emplace(-deg[i], i);
  }

  while (!s.empty()) {
    int v = s.top().second;
    int d = -s.top().first;
    s.pop();
    if (deg[v] != d) continue;
    k_est = max(k_est, -s.top().first);
    order.push_back(v);
    deg[v] = -1;
    for (int u : g[v]) {
      if (deg[u] != -1) {
        deg[u]--;
        s.emplace(-deg[u], u);
      }
    }
  }
  reverse(order.begin(), order.end());
  vector<int> c(g.size(), 1e9);
  for (int x : order) {
    vector<bool> used(g[x].size() + 1);
    for (int u : g[x]) {
      if (c[u] < (int) used.size()) {
        used[c[u]] = true;
      }
    }
    c[x] = 0;
    while (used[c[x]]) {
      c[x]++;
    }
  }
  vector<vector<int>> colors(*max_element(c.begin(), c.end()) + 1);
  for (int i = 0; i < (int)g.size(); i++) {
    colors[c[i]].push_back(i);
  }
  return colors;
}

#ifdef LOCAL
vector<pair<int, int>> ans;
#endif

pair<int, int> query(const vector<int>&x) {
  printf("? %d", (int)x.size());
  for (int a : x) {
    printf(" %d", a + 1);
  }
  printf("\n");
  fflush(stdout);
#ifdef LOCAL
  int cnt = 0;
  set<int> s(x.begin(), x.end());
  int ra = -1, rb = -1;
  for (auto [a, b] : ans) {
    if (s.count(a - 1) && s.count(b - 1)) {
      cnt++;
      if (rand() % cnt == 0) {
        ra = a;
        rb = b;
      }
    }
  }
  return {ra, rb};
#else
  int a, b;
  scanf("%d%d",&a, &b);
  return {a, b};
#endif
}

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  int m;
  scanf("%d", &m);
  ans.resize(m);
  for (int i = 0; i < m; i++) {
    scanf("%d%d", &ans[i].first, &ans[i].second);
  }
//  freopen("h.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  vector<vector<int>> g;
  vector<pair<int, int>> es;
  for (int i = 0; i < n; i++) {
    vector<vector<int>> c = get_coloring(g);
    g.emplace_back();
    for (auto x : c) {
      x.push_back(i);
      while (x.size() > 1) {
        static int queries = 0;
        ++queries;
        //assert(queries <= 2 * k_est * n + n);
        auto [a, b] = query(x);
        if (a == -1) {
          break;
        }
        es.emplace_back(a, b);
        --a, --b;
        assert(a == i || b == i);
        int other = a + b - i;
        g[other].push_back(i);
        g[i].push_back(other);
        x.erase(find(x.begin(), x.end(), other));
      }
    }
  }
  printf("! %d\n", (int) es.size());
  for (auto [a, b] : es) {
    printf("%d %d\n", a, b);
  }
  fflush(stdout);

#ifdef LOCAL
  auto norm = [](vector<pair<int, int>> &a) {
    for (auto &x : a) {
      if (x.first > x.second) swap(x.first, x.second);
    }
    sort(a.begin(), a.end());
  };
  norm(ans);
  norm(es);
  assert(ans == es);
#endif
  return 0;
}
