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

char s[110][110];

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int h, w;
  while (scanf("%d%d", &h, &w) == 2) {
    for (int i = 0; i < h; i++) {
      scanf("%s", s[i]);
    }

    vector<vector<int>> dp(h, vector<int>(w, 1e9));
    dp[h - 1][w - 1] = 0;

    for (int i = h - 1; i >= 0; i--) {
      for (int j = w - 1; j >= 0; j--) {
        if (i != h - 1) {
          dp[i][j] = min(dp[i][j], dp[i+1][j] + (s[i][j] != s[i+1][j]));
        }
        if (j != w - 1) {
          dp[i][j] = min(dp[i][j], dp[i][j+1] + (s[i][j] != s[i][j+1]));
        }
      }
    }

    int ans = dp[0][0];
    if (s[0][0] == '#') ans++;
    if (s[h - 1][w - 1] == '#') ans++;
    assert(ans % 2 == 0);
    ans /= 2;
    printf("%d\n", ans);
  }

  return 0;
}
