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

bool solve(int n, int m) {
  vector<vector<int>> g(n);
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  for (int i = 0; i < n; i++) {
    if (g[i].size() % 2) {
      return false;
    }
  }
  vector<int> big;
  for (int i = 0; i < n; i++) {
    if (g[i].size() >= 6) {
      return true;
    }
    if (g[i].size() == 4) {
      big.push_back(i);
    }
  }
  if (big.size() <= 1) return false;

  for (int i = 0; i < n; i++) {
    if (g[i].size() == 2) {
      int a = g[i][0];
      int b = g[i][1];
      *find(g[a].begin(), g[a].end(), i) = b;
      *find(g[b].begin(), g[b].end(), i) = a;
    }
  }

  for (int v : big) {
    if (find(g[v].begin(), g[v].end(), v) != g[v].end()) {
      return true;
    }
    if (big.size() > 2) {
      sort(g[v].begin(), g[v].end());
      if (unique(g[v].begin(), g[v].end()) != g[v].end()) {
        return true;
      }
    }
  }

  if (big.size() == 2) {
    return false;
  }

  vector<int> d(n, -1);
  vector<int> p(n, -1);
  queue<int> q;
  d[big[0]] = 0;
  q.push(big[0]);

  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int to : g[v]) {
      if (d[to] == -1) {
        d[to] = d[v] + 1;
        q.push(to);
      } else if (to != p[v] && d[to] + d[v] + 1 < (int)big.size()) {
        return true;
      }
    }
  }

  return false;
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    if (solve(n, m)) {
      printf("Yes\n");
    } else {
      printf("No\n");
    }
  }
  return 0;
}
