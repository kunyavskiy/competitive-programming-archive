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

bool dfs(int v, int c, const vector<vector<pair<int, int>>>& g, vector<int>& zs, vector<int> &os, vector<int> &color) {
  if (color[v] != -1) {
    return color[v] == c;
  }
  color[v] = c;
  (c ? os : zs).push_back(v);
  for (auto [u, cc] : g[v]) {
    if (!dfs(u, c ^ cc, g, zs, os, color)) {
      return false;
    }
  }
  return true;
}

void solve() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  char buf[200];
  vector<string> s(n);
  for (int i = 0; i < n; i++) {
    scanf("%s", buf);
    s[i] = buf;
  }
  vector<vector<pair<int, int>>> g(n);
  auto check = [&](const string& a, const string& b) {
    int same = 0;
    for (int i = 0; i < m; i++) {
      if (a[i] == b[i]) {
        same++;
      }
    }
    return same >= k;
  };
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      bool ok_same = check(s[i], s[j]);
      reverse(s[j].begin(), s[j].end());
      bool ok_not_same = check(s[i], s[j]);
      reverse(s[j].begin(), s[j].end());
      if (!ok_same && !ok_not_same) {
        printf("-1\n");
        return;
      }
      if (ok_same && !ok_not_same) {
        g[i].emplace_back(j, 0);
        g[j].emplace_back(i, 0);
      }
      if (!ok_same && ok_not_same) {
        g[i].emplace_back(j, 1);
        g[j].emplace_back(i, 1);
      }
    }
  }
  vector<int> ans;
  vector<int> color(n, -1);
  for (int i = 0; i < n; i++) {
    vector<int> zs, os;
    if (color[i] == -1) {
      if (!dfs(i, 0, g, zs, os, color)) {
        printf("-1\n");
        return;
      }
      for (int x : (zs.size() < os.size() ? zs : os)) {
        ans.push_back(x);
      }
    }
  }

  printf("%d\n", (int)ans.size());
  for (int x : ans) {
    printf("%d ", x + 1);
  }
  printf("\n");
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    solve();
  }

  return 0;
}
