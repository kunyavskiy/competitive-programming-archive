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

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int r, c;
  while (scanf("%d%d", &r, &c) == 2) {
    for (int i = 0; i < r; i++) {
      scanf("%s", s[i]);
    }

    vector<vector<vector<int>>> dpx(r + 1, vector<vector<int>>(r + 1, vector<int>(c + 1)));
    vector<vector<vector<int>>> dpy(c + 1, vector<vector<int>>(c + 1, vector<int>(r + 1)));

    for (int it = 0; it < 2; it++) {
      for (int i = 0; i <= r; i++) {
        vector<bool> ok(c, true);
        for (int j = i; j <= r; j++) {
          dpx[i][j][c] = c;
          int v = c;
          for (int k = c - 1; k >= 0; k--) {
            if (!ok[k]) v = k;
            dpx[i][j][k] = max(dpx[i][j][k], v);
            ok[k] = ok[k] && s[j][k] == (it ? '#' : '.');
          }
        }
      }

      for (int i = 0; i <= c; i++) {
        vector<bool> ok(r, true);
        for (int j = i; j <= c; j++) {
          dpy[i][j][r] = r;
          int v = r;
          for (int k = r - 1; k >= 0; k--) {
            if (!ok[k]) v = k;
            dpy[i][j][k] = max(dpy[i][j][k], v);
            ok[k] = ok[k] && s[k][j] == (it ? '#' : '.');
          }
        }
      }
    }

    int ans = 0;
    while (dpx[0][r][0] < c) {
      ans++;
      vector<vector<vector<int>>> ndpx(r + 1, vector<vector<int>>(r + 1, vector<int>(c + 1)));
      vector<vector<vector<int>>> ndpy(c + 1, vector<vector<int>>(c + 1, vector<int>(r + 1)));

      auto ok = [&](int x1, int y1, int x2, int y2) {
//        eprintf("check(%d, %d, %d, %d) : %d->%d, %d->%d\n", x1, y1, x2, y2, dpx[x1][x2][y1], dpx[x1][x2][dpx[x1][x2][y1]], dpy[y1][y2][x1], dpy[y1][y2][dpy[y1][y2][x1]]);
        return dpx[x1][x2][dpx[x1][x2][y1]] >= y2 || dpy[y1][y2][dpy[y1][y2][x1]] >= x2;
      };

      for (int i = 0; i <= r; i++) {
        for (int j = i; j <= r; j++) {
          int pt = 0;
          for (int k = 0; k <= c; k++) {
            pt = max(pt, k);
//            eprintf("======\n");
            while (pt < c && ok(i, k, j, pt + 1)) pt++;
            ndpx[i][j][k] = pt;
          }
        }
      }

      for (int i = 0; i <= c; i++) {
        for (int j = i; j <= c; j++) {
          int pt = 0;
          for (int k = 0; k <= r; k++) {
            pt = max(pt, k);
            while (pt < r && ok(k, i, pt + 1, j)) pt++;
            ndpy[i][j][k] = pt;
          }
        }
      }

      dpx = ndpx;
      dpy = ndpy;
//      eprintf("%d ", dpx[0][r][0]);
//      eprintf("%d ", dpx[0][r][1]);
//      eprintf("%d ", dpx[0][r][2]);
//      eprintf("%d\n", dpx[0][r][3]);
    }

    printf("%d\n", ans);
  }

  return 0;
}
