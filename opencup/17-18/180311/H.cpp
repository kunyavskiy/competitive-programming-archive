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
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

  ~__timestamper() {
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
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  vector<vector<int>> aa(n, vector<int>(n, -1));
  vector<vector<int>> a(n, vector<int>(n, 1000000000));
  for (int i = 0; i < k; i++) {
    int x, y, v;
    scanf("%d%d%d", &x, &y, &v);
    aa[x - 1][y - 1] = a[x - 1][y - 1] = v;
  }

  vector<vector<bool>> z(n, vector<bool>(n));
  while (true) {
    int ii = -1;
    int jj = -1;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (!z[i][j]) {
          if (ii == -1 || a[i][j] < a[ii][jj]) {
            ii = i;
            jj = j;
          }
        }
      }
    }
    if (ii == -1) break;
    z[ii][jj] = true;
    for (int i = ii - 1; i <= ii + 1; i++) {
      for (int j = jj - 1; j <= jj + 1; j++) {
        if (i < 0 || i >= n || j < 0 || j >= n || (i != ii && j != jj)) {
          continue;
        }
        a[i][j] = min(a[i][j], a[ii][jj] + m);
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (aa[i][j] != -1 && aa[i][j] != a[i][j]) {
        cout << "NO\n";
        return 0;
      }
    }
  }
  cout << "YES\n";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << min(a[i][j], 1000000000) << " ";
    }
    cout << "\n";
  }


  return 0;
}
