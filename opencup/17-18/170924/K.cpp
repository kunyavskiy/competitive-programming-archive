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

const int MAXN = 51;
int n, m;
char s[MAXN][MAXN + 1];
char par[MAXN][MAXN][MAXN][MAXN];
vector <pii> ed[MAXN][MAXN];
int dist[MAXN][MAXN];
pii par2[MAXN][MAXN];

const char dirCh[] = "UDLR";
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

struct Position {
  int sx, sy, fx, fy;
};

bool check_cell(int x, int y) {
  return (0 <= x && x < n && 0 <= y && y < m && s[x][y] == '.');
}

void printPath(int sx, int sy, int fx, int fy) {
  static char pal[200];
  int k = 0;
  while (par[sx][sy][fx][fy] < 4) {
    int dir = par[sx][sy][fx][fy];
    pal[k++] = dirCh[dir];
    sx -= dx[dir^1];
    sy -= dy[dir^1];
    fx -= dx[dir];
    fy -= dy[dir];
  }
  for (int i = 0; i < k; ++i) {
    printf("%c", pal[i]);
  }
  if (par[sx][sy][fx][fy] != (char)8) {
    int dir = par[sx][sy][fx][fy];
    printf("%c", dirCh[dir - 4]);
  }
  for (int i = k - 1; i >= 0; --i) {
    printf("%c", pal[i]);
  }
  printf("\n");
}

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%s", s[i]);
  }
  int sx = -1, sy = -1, fx = -1, fy = -1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (s[i][j] == 'S') {
        sx = i;
        sy = j;
        s[i][j] = '.';
      }
      if (s[i][j] == 'F') {
        fx = i;
        fy = j;
        s[i][j] = '.';
      }
    }
  }

  memset(par, 0xff, sizeof(par));
  vector<vector<Position>> q(3);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (s[i][j] == '.') {
        Position cur({i, j, i, j});
        q[0].push_back(cur);
        par[i][j][i][j] = (char)8;
        for (int dir = 0; dir < 4; ++dir) {
          int i2 = i + dx[dir];
          int j2 = j + dy[dir];
          if (check_cell(i2, j2)) {
            Position cur2({i, j, i2, j2});
            q[1].push_back(cur2);
            par[i][j][i2][j2] = (char)(4 + dir);
          }
        }
      }
    }
  }

  for (int d = 0; d <= 100 - 2; ++d) {
    int d0 = d % 3;
    int d1 = (d + 1) % 3;
    int d2 = (d + 2) % 3;
    if (q[d0].empty() && q[d1].empty()) { break; }

    for (auto & p : q[d0]) {
      eprintf("len %d (%d %d) (%d %d)\n", d, p.sx, p.sy, p.fx, p.fy);
      for (int dir = 0; dir < 4; ++dir) {
        int x1 = p.sx + dx[dir^1];
        int y1 = p.sy + dy[dir^1];
        int x2 = p.fx + dx[dir];
        int y2 = p.fy + dy[dir];
        if (check_cell(x1, y1) && check_cell(x2, y2) && par[x1][y1][x2][y2] == (char)-1) {
          q[d2].push_back({x1, y1, x2, y2});
          par[x1][y1][x2][y2] = (char)dir;
        }
      }
    }
  }

  for (int x1 = 0; x1 < n; ++x1) {
    for (int y1 = 0; y1 < m; ++y1) {
      for (int x2 = 0; x2 < n; ++x2) {
        for (int y2 = 0; y2 < m; ++y2) {
          if (par[x1][y1][x2][y2] != (char)-1) {
            ed[x2][y2].push_back(pii(x1, y1));
          }
        }
      }
    }
  }

  memset(dist, 0xff, sizeof(dist));
  vector <pii> qq;
  qq.push_back(pii(fx, fy));
  dist[fx][fy] = 0;
  for (int i = 0; i < int(qq.size()); ++i) {
    int xx = qq[i].first;
    int yy = qq[i].second;
    eprintf("%d %d dist %d\n", xx, yy, dist[xx][yy]);
    for (auto p : ed[xx][yy]) {
      if (dist[p.first][p.second] == -1) {
        dist[p.first][p.second] = dist[xx][yy] + 1;
        par2[p.first][p.second] = {xx, yy};
        qq.push_back(p);
      }
    }
  }

  if (dist[sx][sy] == -1) {
    printf("-1\n");
  } else {
    printf("%d\n", dist[sx][sy]);
    while (sx != fx || sy != fy) {
      int nx = par2[sx][sy].first;
      int ny = par2[sx][sy].second;
      printPath(sx, sy, nx, ny);
      sx = nx;
      sy = ny;
    }
  }

  return 0;
}
