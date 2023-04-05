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

const int MAXN = 110000;

vector<int> p[MAXN];
vector<int> g[MAXN];

bool mark[MAXN];
set<int> s[MAXN];


void go(int v, int par = -1) {
  for (int u : p[v]) {
    if (!s[v].insert(u).second) {
      mark[v] = true;
    }
  }
  for (int u : g[v]) {
    if (u == par) continue;
    go(u, v);
    if (s[v].size() < s[u].size()) {
      s[v].swap(s[u]);
    }
    for (int x : s[u]) {
      if (!s[v].insert(x).second) {
        mark[v] = true;
      }
    }
  }
  if (mark[v]) {
    s[v].clear();
  }
}

int main() {
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);

  int n;
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  int m;
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    p[a].push_back(i);
    p[b].push_back(i);
  }

  go(0);

  int ans = 0;
  for (int i = 0; i < n; i++) {
    ans += mark[i];
  }

  printf("%d\n", ans);
  for (int i = 0; i < n; i++) {
    if (mark[i]) {
      printf("%d ", i + 1);
    }
  }
  printf("\n");
  return 0;
}
