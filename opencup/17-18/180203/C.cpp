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
typedef pair<int, int> pii;

bool dfs(int s, int col, const vector <vector<int>> & ed, vector <int> & used, vector <int> &match) {
  if (used[s] == col) {
    return false;
  }
  used[s] = col;
  for (int v : ed[s]) {
    if (match[v] == -1 || dfs(match[v], col, ed, used, match)) {
      match[v] = s;
      match[s] = v;
      return true;
    }
  }
  return false;
}

void check(int s, int n, const vector<vector<int>> & ed) {
  vector <int> comp(n, 2);
  comp[s] = 0;
  for (int x : ed[s]) {
    comp[x] = 1;
  }

  vector <int> match(n, -1);
  match[s] = s;
  vector <vector<int>> ed2(n);
  for (int u = 0; u < n; ++u) {
    if (comp[u] != 2) { continue; }
    for (int v : ed[u]) {
      if (comp[v] == 1) {
        ed2[u].push_back(v);
      }
      if (match[u] == -1 && match[v] == -1 && comp[u] != comp[v]) {
        match[u] = v;
        match[v] = u;
      }
    }
  }
  vector <int> used(n, -1);
  for (int i = 0; i < n; ++i) {
    if (comp[i] == 2 && match[i] == -1) {
      if (!dfs(i, i, ed2, used, match)) {
        return;
      }
    }
  }
  printf("Yes\n");
  vector <pii> teams;
  for (int i = 0; i < n; ++i) {
    if (comp[i] == 1) {
      teams.push_back(pii(i, match[i]));
    }
  }
  printf("%d %d\n", s + 1, int(teams.size()));
  for (pii t : teams) {
    int u = t.first, v = t.second;
    if (u != -1) ++u;
    if (v != -1) ++v;
    printf("%d %d\n", u, v);
  }
  exit(0);
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  vector<vector<int>> ed(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    ed[u].push_back(v);
    ed[v].push_back(u);
  }

  for (int i = 0; i < n; ++i) {
    if (int(ed[i].size()) >= n / 2) {
      check(i, n, ed);
    }
  }
  printf("No\n");

  return 0;
}
