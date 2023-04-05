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

struct Edge {
  int u, v, w, num;
};

vector <vector<Edge>> ed;

void addEdge(int u, int v, int w, int num) {
  eprintf("%d %d %d %d\n", u, v, w, num);
  ed[u].push_back({u, v, w, num});
  ed[v].push_back({v, u, w, num});
}

bool dfs(int s, int curC, vector<int> & col, vector<bool> &useE) {
  assert(col[s] == -1);
  col[s] = curC;
  eprintf("col[%d] = %d\n", s, curC);
  bool ok = true;
  for (const auto & e : ed[s]) {
    int v = e.v;
    int w = e.w;
    if (col[v] == -1) {
      useE[e.num] = true;
      ok &= dfs(v, curC ^ w, col, useE);
    } else {
      eprintf("col[%d] == %d?\n", v, curC ^ w);
      ok &= (col[v] == (curC ^ w));
    }
  }
  return ok;
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n, m;
  scanf("%d%d", &n, &m);
  ++n;
  ed.resize(n);
  static char s[20];
  for (int i = 0; i < m; ++i) {
    int a;
    scanf(" %s%d", s, &a);
    if (!strcmp(s, "hor")) {
      addEdge(a, 0, 0, i);
    } else if (!strcmp(s, "vert")) {
      addEdge(a, 0, 1, i);
    } else if (!strcmp(s, "par")) {
      int b;
      scanf("%d", &b);
      addEdge(a, b, 0, i);
    } else if (!strcmp(s, "perp")) {
      int b;
      scanf("%d", &b);
      addEdge(a, b, 1, i);
    } else {
      assert(0);
    }
  }

  vector <int> col(n, -1);
  vector <bool> useE(m, false);
  bool ok = true;
  for (int i = 0; i < n; ++i) {
    if (col[i] == -1) {
      ok &= dfs(i, 0, col, useE);
    }
  }

  if (!ok) {
    printf("inconsistent\n");
  } else {
    printf("consistent\n");
    vector <int> ans;
    for (int i = 0; i < m; ++i) {
      if (!useE[i]) {
        ans.push_back(i);
      }
    }
    printf("%d\n", (int)ans.size());
    for (int x : ans) {
      printf("%d ", x + 1);
    }
    printf("\n");
  }

  return 0;
}
