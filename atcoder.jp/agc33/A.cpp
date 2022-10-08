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

char s[1010][1010];
int d[1010][1010];

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int r, c;
  while (scanf("%d%d", &r, &c) == 2) {
    memset(d, -1, sizeof(d));
    queue<pair<int, int>> q;
    for (int i = 0; i < r; i++) {
      scanf("%s", s[i]);
      for (int j = 0; j < c; j++) {
        if (s[i][j] == '#') {
          q.emplace(i, j);
          d[i][j] = 0;
        }
      }
    }

    int ans = 0;

    while (!q.empty()) {
      int u, v;
      tie(u, v) = q.front();
      q.pop();
      ans = max(ans, d[u][v]);
      auto go = [&](int x, int y) {
        if (x >= 0 && x < r && y >= 0 && y < c && d[x][y] == -1) {
          d[x][y] = d[u][v] + 1;
          q.emplace(x, y);
        }
      };
      go(u - 1, v);
      go(u + 1, v);
      go(u, v - 1);
      go(u, v + 1);
    }

    printf("%d\n", ans);
  }

  return 0;
}
