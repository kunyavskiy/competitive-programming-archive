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

const int MAXN = 1010;

char s[MAXN][MAXN];
int color[MAXN][MAXN];
int n, m, r, c;
int found;

void dfs(int x, int y, int col) {
  if (color[x][y] != -1) {
    assert(color[x][y] == col);
    return;
  }
  color[x][y] = col;
  found++;
  for (int i = -1; i <= 1; i += 2) {
    for (int j = -1; j <= 1; j += 2) {
      for (int o = 0; o <= 1; o++) {
        int nx = x + i * (o ? r : c);
        int ny = y + j * (o ? c : r);
        if (nx < 0 || nx >= n) continue;
        if (ny < 0 || ny >= m) continue;
        if (s[nx][ny] == '@') continue;
        dfs(nx, ny, 1 - col);
      }
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

  while (scanf("%d%d%d%d", &n, &m, &r, &c) == 4) {
    int ax = 0, ay = 0;
    int bx = 0, by = 0;

    for (int i = 0; i < n; i++) {
      scanf("%s", s[i]);
      for (int j = 0; j < m; j++) {
        color[i][j] = -1;
        if (s[i][j] == 'A') {
          s[i][j] = '.';
          ax = i, ay = j;
        } else if (s[i][j] == 'B') {
          s[i][j] = '.';
          bx = i, by = j;
        }
      }
    }

    if (r == 0 && c == 0) {
      found = 1;
    } else {
      found = 0;
      dfs(ax, ay, 0);
    }

    if (found != 1 && (color[bx][by] == -1 || color[bx][by] == 0)) {
      printf("Alice\n");
    } else {
      printf("Bob\n");
    }
  }

  return 0;
}
