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

bool solve() {
  int n, k;
  if (scanf("%d%d", &n, &k) != 2) {return false;}
  static const int N = 5;
  static char s[N][N + 1];
  for (int i = 0; i < n; ++i) {
    scanf("%s", s[i]);
  }

  vector<int> ships(k);
  for (int i = 0; i < k; ++i) {
    scanf("%d", &ships[i]);
  }

  int ans = 0;
  vector<vector<int>> a(n, vector<int>(n, -1));
  vector<bool> used(k, false);

  function<void(int, int)> brute = [&](int x, int y) {
    if (y == n) {
      y = 0;
      x++;
    }

#if 0
    eprintf("%d %d:\n", x, y);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        eprintf("%d ", a[i][j]);
        if (a[i][j] != -1) {
          assert(used[a[i][j]]);
        }
      }
      eprintf("\n");
    }
    eprintf("\n");
#endif

    if (x == n) {
      bool ok = true;
      for (int i = 0; i < k; ++i) {
        ok &= used[i];
      }
      if (ok) {
//        eprintf("%d:\n", ans);
//        for (int i = 0; i < n; ++i) {
//          for (int j = 0; j < n; ++j) {
//            eprintf("%d ", a[i][j]);
//          }
//          eprintf("\n");
//        }

        ans++;
      }
      return;
    }

    if (a[x][y] != -1) {
      brute(x, y + 1);
      return;
    }

    if (s[x][y] != 'O') {
      if (a[x][y] == -1) {
        brute(x, y + 1);
      }
    }

    if (s[x][y] != 'X') {
      for (int i = 0; i < k; ++i) {
        if (used[i]) { continue; }
        for (int j = 0; j < 2; ++j) {
          if (ships[i] == 1 && j == 1) { continue; }
          int dx = 0, dy = 1;
          if (j == 1) { swap(dx,dy);}

          if (x + dx * ships[i] > n || y + dy * ships[i] > n) { continue; }

          bool ok = true;
          used[i] = true;
          for (int p = 0; ok && p < ships[i]; ++p) {
            int x1 = x + p * dx;
            int y1 = y + p * dy;
            if (s[x1][y1] == 'X' || a[x1][y1] != -1) {
              ok = false;
            } else {
              assert(a[x1][y1] == -1);
              a[x1][y1] = i;
            }
          }
          if (ok) {
            brute(x, y + 1);
          }
          used[i] = false;
          for (int p = 0; p < ships[i]; ++p) {
            int x1 = x + p * dx;
            int y1 = y + p * dy;
            if (a[x1][y1] == i) {
              a[x1][y1] = -1;
            }
          }
        }
      }
    }
  };

  brute(0, 0);
  printf("%d\n", ans);

  return true;
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  while (solve()) {
  }

  return 0;
}


/*
 *
 * 0 0:
-1 -1
-1 -1

0 1:
-1 -1
-1 -1

1 0:
-1 -1
-1 -1

1 1:
-1 -1
-1 -1

2 0:
-1 -1
-1 -1

1 1:
-1 -1
0 0

1 1:
-1 -1
1 1

1 0:
-1 0
-1 0

1 1:
-1 0
-1 0

1 0:
-1 1
-1 1

1 1:
-1 1
-1 1

0 1:
0 0
-1 -1

0 1:
0 -1
0 -1

1 0:
0 -1
0 -1

1 0:
0 1
0 1

0 1:
1 1
-1 -1

0 1:
1 -1
1 -1

1 0:
1 -1
1 -1

1 0:
1 0
1 0
 */
