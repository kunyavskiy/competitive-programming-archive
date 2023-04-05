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
typedef pair<int,int> pii;

bool solve() {
  int n, m;
  if (scanf("%d%d", &n, &m) != 2) {
    return false;
  }

  static char s[510][510];
  for (int i = 0; i < n; ++i) {
    scanf("%s", s[i]);
  }

  vector<vector<int>> a(n, vector<int>(m, -1));
  vector<pii> gar;
  vector<int> color;
  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < m; ++y) {
      if (s[x][y] != 'V' && s[x][y] != 'H') {
        continue;
      }
      a[x][y] = int(gar.size());
      gar.emplace_back(x, y);
      color.push_back(s[x][y] == 'H' ? 0 : 1);
    }
  }

  static const int dx[] = {0, -1, 0, 1};
  static const int dy[] = {-1, 0, 1, 0};

  int k = int(gar.size());

  vector<vector<int>> can_color(k, vector<int>(2, 1));

  vector<vector<pii>> ed(k);
  for (int i = 0; i < k; ++i) {
    int x0 = gar[i].first;
    int y0 = gar[i].second;
    for (int j = 0; j < 4; ++j) {
      int xx = x0;
      int yy = y0;
      int dir = j;
      bool ok = true;
      int targ_num = -1;
      int targ_color = -1;
      while (true) {
        xx += dx[dir];
        yy += dy[dir];

        if (!(0 <= xx && xx < n && 0 <= yy && yy < m)) {
          // ok
          break;
        } else if (s[xx][yy] == '/') {
          dir ^= 3;
        } else if (s[xx][yy] == '\\') {
          dir ^= 1;
        } else if (s[xx][yy] == '#') {
          ok = false;
        } else if (s[xx][yy] == '.') {
          // just continue
        } else if (s[xx][yy] == 'V' || s[xx][yy] == 'H') {
          targ_num = a[xx][yy];
          assert(targ_num != -1);
          targ_color = (dir % 2);
          break;
        } else {
          assert(0);
        }
      }

      eprintf("i %d j %d ok %d targ_num %d targ_color %d\n", i, j, ok, targ_num, targ_color);
      can_color[i][j % 2] &= ok;
      if (targ_num != -1) {
        ed[i].emplace_back(targ_num, (targ_color == j % 2) ? 0 : 1);
      }
    }
  }

  bool imp = false;
  int ans = 0;
  vector<int> used(k, -1);
  function<pii(int, int)> dfs = [&](int s, int curC) {
    if (used[s] != -1) {
      if (used[s] != curC) {
        imp = true;
      }
      return pii{0, 0};
    }
    used[s] = curC;
    int tot_cnt = 1;
    int ch_cnt = (color[s] == curC ? 0 : 1);
    if (!can_color[s][curC]) {
      imp = true;
    }
    for (auto e : ed[s]) {
      auto cur = dfs(e.first, curC ^ e.second);
      tot_cnt += cur.first;
      ch_cnt += cur.second;
    }
    return pii{tot_cnt, ch_cnt};
  };

  for (int i = 0; i < k; ++i) {
    if (used[i] != -1) { continue; }

    if (!can_color[i][0] && !can_color[i][1]) {
      imp = true;
    } else if (!can_color[i][0]) {
      assert(can_color[i][1]);
      auto cur = dfs(i, 1);
      ans += cur.second;
    } else if (!can_color[i][1]) {
      assert(can_color[i][0]);
      auto cur = dfs(i, 0);
      ans += cur.second;
    }
  }
  for (int i = 0; i < k; ++i) {
    if (used[i] != -1) { continue; }
    auto cur = dfs(i, 0);
    ans += min(cur.second, cur.first - cur.second);
  }

  if (imp) {
    printf("-1\n");
  } else {
    printf("%d\n", ans);
  }

  return true;
}

int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
#endif

  while (solve());

  return 0;
}
