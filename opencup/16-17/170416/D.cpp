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
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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

const int MAXN = 200100;

multiset<int> s[MAXN];

int cost[MAXN];

vector<int> g[MAXN];


void dfs(int v) {
  for (int u : g[v]) {
    dfs(u);
    if (s[u].size() > s[v].size()) {
      s[u].swap(s[v]);
    }
    for (int x : s[u]) {
      s[v].insert(x);
    }
    s[u].clear();
  }
  auto it = s[v].lower_bound(cost[v]);
  if (it != s[v].end()) {
    s[v].erase(it);
  }
  s[v].insert(cost[v]);
}


int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    int p;
    scanf("%d%d", &cost[i], &p);
    --p;

    if (p != -1) {
      g[p].push_back(i);
    }
  }

  dfs(0);

  printf("%d\n", (int)s[0].size());
  return 0;
}
