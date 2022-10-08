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

const int MAXN = 610;

int used[MAXN][MAXN];

vector<pair<int, int>> ds;

void init_dxdy(int d) {
  ds.clear();
  for (int i = 0; i * i <= d; i++) {
    int t = d - i * i;
    int tt = (int)sqrt(t);
    tt = max(tt, 0);
    while (tt * tt <= t) tt++;
    while (tt * tt > t) tt--;
    if (tt * tt + i * i == d) {
      ds.push_back({i, tt});
      ds.push_back({-i, tt});
      ds.push_back({i, -tt});
      ds.push_back({-i, -tt});
    }
  }
  sort(ds.begin(), ds.end());
  ds.erase(unique(ds.begin(), ds.end()), ds.end());
}

int n;

void dfs(int x, int y, int c) {
  if (used[x][y] != -1) {
    assert(used[x][y] == c || used[x][y] == -2);
    return;
  }
  used[x][y] = c;
  for (auto d : ds) {
    int nx = x + d.first;
    int ny = y + d.second;
    if (0 <= nx && nx < n && 0 <= ny && ny < n) {
      dfs(nx, ny, c ^ 1);
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif


  while (scanf("%d", &n) == 1) {
    int d1, d2;
    scanf("%d%d", &d1, &d2);
    memset(used, -1, sizeof(used));
    int need = n * n;
    n *= 2;
    int cnt[4];
    memset(cnt, 0, sizeof(cnt));
    init_dxdy(d1);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (used[i][j] == -1) {
          dfs(i, j, 0);
        }
        cnt[used[i][j]]++;
      }
    }

    int c = 1;
    if (cnt[0] > cnt[1]) {
      c = 0;
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (used[i][j] == c) {
          used[i][j] = -1;
        } else {
          used[i][j] = -2;
        }
      }
    }

    init_dxdy(d2);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (used[i][j] == -1) {
          dfs(i, j, 2);
        }
        if (used[i][j] != -2) {
          cnt[used[i][j]]++;
        }
      }
    }

    c = 3;
    if (cnt[2] > cnt[3]) {
      c = 2;
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (used[i][j] == c) {
          if (need > 0) {
            printf("%d %d\n", i, j);
            need--;
          }
        }
      }
    }
    assert(need == 0);
  }

  return 0;
}
