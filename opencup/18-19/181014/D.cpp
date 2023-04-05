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

vector<int> l, r;
vector<vector<int>> g;
vector<int> z;

bool dfs(int x) {
  if (z[x] == 1) return false;
  if (z[x] == 2) return true;
  z[x] = 1;
  for (int y : g[x]) {
    if (!dfs(y))
      return false;
    r[x] = min(r[x], r[y] - 1);
  }
  z[x] = 2;
  return true;
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  l.resize(n);
  r.resize(n);
  g.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &l[i]);
    scanf("%d", &r[i]);
    l[i]--;
    r[i]--;
  }
  vector<int> d(n);
  for (int i = 0; i < m; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    x--; y--;
    g[x].push_back(y);
    d[y]++;
  }
  z.resize(n);
  for (int i = 0; i < n; i++) {
    if (!dfs(i)) {
      cout << -1;
      return 0;
    }
  }
  vector<pair<int, int>> p(n);
  for (int i  = 0; i < n; i++) {
    p[i] = {l[i], i};
  }
  sort(p.begin(), p.end());
  int j = 0;
  set<pair<int, int>> q;
  vector<int> res(n);

  for (int i = 0; i < n; i++) {
    while (j < n && p[j].first == i) {
      int x = p[j].second;
      j++;
      if (d[x] == 0)
        q.insert({r[x], x});
    }
    if (q.size() == 0) {
      cout << -1;
      return 0;
    }
    auto p = *q.begin();
    q.erase(p);
    int x = p.second;
    res[i] = x;
    if (r[x] < i) {
      cout << -1;
      return 0;
    }
    for (int y : g[x]) {
      d[y]--;
      if (d[y] == 0 && l[y] <= i) {
        q.insert({r[y], y});
      }
    }
  }
  for (int i = 0; i < n; i++) {
    cout << res[i] + 1 << "\n";
  }

  return 0;
}
