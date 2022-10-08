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

const int MAXN = 410;
const int MAXM = 100100;

int a[MAXM];
int b[MAXM];

int g[MAXN][MAXN];
bool ok[MAXN];

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    for (int i = 0; i < m; i++) {
      scanf("%d%d", &a[i], &b[i]);
      --a[i], --b[i];
    }
    for (int v = 0; v < n; v++) {
      vector<bool> protect(n);
      protect[v] = true;
      ok[v] = true;
      for (int i = m - 1; i >= 0; i--) {
        if (protect[a[i]] && protect[b[i]]) {
          ok[v] = false;
          break;
        }
        if (protect[a[i]] || protect[b[i]]) {
          protect[a[i]] = protect[b[i]] = true;
        }
      }
      for (int i = 0; i < n; i++) {
        g[v][i] = protect[i];
      }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        bool can = ok[i] && ok[j];
        for (int k = 0; k < n; k++) {
          if (g[i][k] && g[j][k]) {
            can = false;
          }
        }
        if (can) ans++;
      }
    }
    printf("%d\n", ans);
  }

  return 0;
}
