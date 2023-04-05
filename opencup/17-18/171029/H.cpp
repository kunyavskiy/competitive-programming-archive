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

ll an[110][110][110];
ll sq[110][110][110];

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif
  int n, m, q;
  scanf("%d%d%d", &n, &m, &q);

  for (int qq = 0; qq < m; qq++) {
    int x, y, z, a;
    scanf("%d%d%d%d", &x, &y, &z, &a);
    for (int i = 0; i < a; i++) {
      int xx = x + i;
      int aa = i + 1;
      an[xx][y][z]++;
      an[xx][y + aa][z + aa]--;
      sq[xx][y + aa][z]--;
      sq[xx][y + aa][z + aa]++;
    }
  }

  for (int i = 1; i <= n + 1; i++) {
    for (int j = 1; j <= n + 1; j++) {
      for (int k = 1; k <= n + 1; k++) {
        sq[i][j][k] += sq[i][j - 1][k];
        an[i][j][k] += an[i][j - 1][k];
      }
    }
    for (int j = 1; j <= n + 1; j++) {
      for (int k = 1; k <= n + 1; k++) {
        sq[i][j][k] += sq[i][j][k - 1];
        an[i][j][k] += an[i][j - 1][k - 1];
      }
    }
    for (int j = 1; j <= n + 1; j++) {
      for (int k = 1; k <= n + 1; k++) {
        sq[i][j][k] = an[i][j][k] = (sq[i][j][k] + an[i][j][k]);
      }
    }

    for (int j = n + 1; j >= 1; j--) {
      for (int k = n + 1; k >= 1; k--) {
        sq[i][j][k] += sq[i][j + 1][k];
        an[i][j][k] += an[i][j + 1][k];
      }
    }

    for (int j = n + 1; j >= 1; j--) {
      for (int k = n + 1; k >= 1; k--) {
        sq[i][j][k] += sq[i][j][k + 1];
        an[i][j][k] += an[i][j + 1][k + 1];
      }
    }
  }

  for (int qq = 0; qq < q; qq++) {
    int x, y, z, a;
    scanf("%d%d%d%d", &x, &y, &z, &a);
    ll res = 0;
    for (int i = 0; i < a; i++) {
      int xx = x + i;
      int aa = i + 1;
      res += an[xx][y][z];
      res -= an[xx][y + aa][z + aa];
      res -= sq[xx][y + aa][z];
      res += sq[xx][y + aa][z + aa];
    }
    cout << res << "\n";
  }

  return 0;
}
