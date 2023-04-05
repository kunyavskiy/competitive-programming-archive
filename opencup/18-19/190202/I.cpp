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
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

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

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
//  freopen("i.out", "w", stdout);
#endif
  int n, m;
  scanf("%d%d", &n, &m);
  int sum = 0;
  vector<vector<int>> a(n, vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      char c1, c2;
      scanf(" %c%c", &c1, &c2);
      if (c2 == '^') sum += 0;
      if (c2 == '>') sum += 1;
      if (c2 == 'v') sum += 2;
      if (c2 == '<') sum += 3;
      a[i][j] = c1 == 'L';
    }
  }
  sum %= 4;

  vector<vector<int>> e(n * m);
  auto get_id = [&](int x, int y) {
    return x * m + y;
  };


  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      for (int t = 0; t < 4; t++) {
        if (a[i][j] == 0) {
          int xx = i + dx[t];
          int yy = j + dy[t];
          if (0 <= xx && xx < n && 0 <= yy && yy < m && a[xx][yy] == 1) {
            e[get_id(i, j)].push_back(get_id(xx, yy));
          }
        }
      }
    }
  }
  vector<bool> use;
  vector<int> p(n * m, -1);
  vector<int> go(n * m, -1);
  function<bool(int)> dfs = [&](int v) {
    use[v] = 1;
    for (auto u: e[v]) {
      if (p[u] == -1 || (!use[p[u]] && dfs(p[u]))) {
        p[u] = v;
        return 1;
      }
    }
    return 0;
  };

  bool change = true;
  int cnt = 0;
  while (change) {
    change = false;
    use.assign(n * m, false);
    for (int i = 0; i < n * m; i++) {
      if (go[i] == -1 && use[i] == 0) {
        if (dfs(i)) {
          cnt++;
          go[i] = 1;
          change = true;
        }
      }
    }
  }
  db(cnt);
  if (cnt * 2 ==  n * m) {
    int glob = 0;
    if (m % 2 == 0) {
      glob = 0;
    }
    else {
      assert(n % 2 == 0);
      glob = (n % 4 == 0)? 0: 2;
    }
    if (glob != sum) {
      cnt--;
    }
//    db2(glob, sum);
  }
  printf("%d\n", cnt);







  return 0;
}
