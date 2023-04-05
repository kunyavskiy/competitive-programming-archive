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

int main() {
#ifdef LOCAL
  freopen("p3.in", "r", stdin);
  freopen("p3.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n,&m) == 2) {
    int p, r;
    scanf("%d%d", &p, &r);
    p /= 2;
    vector<string> s(n);
    static char buf[2000];
    for (int i = 0; i < n; i++) {
      scanf(" %s", buf);
      s[i] = buf;
    }
    int sx = -1, sy = -1, tx = -1, ty = -1;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (s[i][j] == 'S') {
          sx = i;
          sy = j;
          s[i][j] = '.';
        } else if (s[i][j] == 'E') {
          tx = i;
          ty = j;
          s[i][j] = '.';
        }
      }
    }

    assert(sx != -1);
    assert(tx != -1);
    vector<vector<int>> dp(n, vector<int>(m, -1));
    vector<vector<pair<int, int>>> par(n, vector<pair<int, int>>(m, {-1, -1}));
    dp[sx][sy] = 0;

    vector<pair<pair<int, int>, int>> q;
    q.push_back({{sx, sy}, 0});
    int dist = 0;

    static const int dx[] = {1, 0, -1, 0};
    static const int dy[] = {0, 1, 0, -1};
    auto good = [&](int x, int y) {
      return 0 <= x && x < n && 0 <= y && y < m;
    };

    while (dp[tx][ty] == -1) {
      {
        for (int pos = 0; pos < (int) q.size(); pos++) {
          int x = q[pos].first.first;
          int y = q[pos].first.second;
          q[pos].second = 0;
          for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (!good(nx, ny) || dp[nx][ny] != -1 || s[nx][ny] != '.') {
              continue;
            }
            dp[nx][ny] = dist;
            par[nx][ny] = {x, y};
            q.push_back({{nx, ny}, 0});
          }
        }
      }
      int old_size = q.size();
      dist++;
      {
        for (int pos = 0; pos < (int) q.size(); pos++) {
          int x = q[pos].first.first;
          int y = q[pos].first.second;
          int d = q[pos].second;
          q[pos].second = 0;
          if (d >= r) continue;
          for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (!good(nx, ny) || dp[nx][ny] != -1) {
              continue;
            }
            dp[nx][ny] = dist;
            par[nx][ny] = {x, y};
            q.push_back({{nx, ny}, d + 1});
          }
        }
      }
      {
        for (int pos = 0; pos < (int) q.size(); pos++) {
          int x = q[pos].first.first;
          int y = q[pos].first.second;
          int d = q[pos].second;
          q[pos].second = 0;
          if (d >= p) continue;
          for (int nx = x - 1; nx <= x + 1; nx++) {
            for (int ny = y - 1; ny <= y + 1; ny++) {
              if (!good(nx, ny) || dp[nx][ny] != -1) {
                continue;
              }
              dp[nx][ny] = dist;
              par[nx][ny] = {x, y};
              q.push_back({{nx, ny}, d + 1});
            }
          }
        }
      }
      q.erase(q.begin(), q.begin() + old_size);
    }

    printf("%d\n", dp[tx][ty]);
    vector<pair<int, int>> path;
    while (tx != sx || ty != sy) {
      path.emplace_back(tx, ty);
      auto tmp = par[tx][ty];
      if (tmp.first != tx && tmp.second != ty) {
        path.emplace_back(tx, tmp.second);
      }
      tx = tmp.first;
      ty = tmp.second;
    }
    path.emplace_back(sx, sy);
    reverse(path.begin(), path.end());

    vector<pair<int, int>> ans;
    for (int i = 0; i < (int)path.size(); i++) {
      auto [x, y] = path[i];
      if (s[x][y] != '.') {
        auto [x, y] = path[i - 1];
        ans.emplace_back(path[i - 1]);
        for (int j = -p - r; j <= p + r; j++) {
          for (int k = -p - r; k <= p + r; k++) {
            if (!good(x + j, y + k)) continue;
            if (abs(j) + abs(k) > 2 * p + r) continue;
            s[x + j][y + k] = '.';
          }
        }
      }
    }
    for (auto[x,y] : ans) {
      printf("%d %d\n", x+1, y+1);
    }
    fflush(stdout);
    assert((int)ans.size() == dp[path.back().first][path.back().second]);

  }

  return 0;
}
