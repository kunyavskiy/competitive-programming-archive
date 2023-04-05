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

const int MAXN = 1005;

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

char s[MAXN][MAXN];
int dst[MAXN][MAXN][4];

struct item {
  int x, y, d;
};

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);

  int sx = -1, sy = -1;
  int tx = -1, ty = -1;

  for (int i = 0; i < n; i++) {
    scanf("%s", s[i]);
    for (int j = 0; j < m; j++) {
      if (s[i][j] == 'K') {
        sx = i, sy = j;
        s[i][j] = '.';
      }
      if (s[i][j] == 'S') {
        tx = i, ty = j;
        s[i][j] = '.';
      }
    }
  }

  memset(dst, -1, sizeof(dst));
  dst[sx][sy][0] = 0;
  queue<item> q;
  q.push({sx, sy, 0});

  while (!q.empty()) {
    int x = q.front().x;
    int y = q.front().y;
    int d = q.front().d;
    q.pop();

    if (s[x][y] == '*') continue;
    if (x == tx && y == ty) {
      printf("%d\n", dst[x][y][d]);
      return 0;
    }
    for (int i = 0; i < 4; i++) {
      if (s[x][y] == '.' || i == d) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (0 <= nx && nx < n && 0 <= ny && ny < m && dst[nx][ny][i] == -1) {
          dst[nx][ny][i] = dst[x][y][d] + 1;
          q.push({nx, ny, i});
        }
      }
    }
  }

  printf("-1\n");
  return 0;
}
