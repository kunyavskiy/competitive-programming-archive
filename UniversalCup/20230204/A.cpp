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

void solve() {
    int n;
    scanf("%d", &n);
    vector<vector<int>> g(n);
    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        --a;
        if (i == 0)continue;
        g[a].push_back(i);
    }
    vector<int> dp(n);
    for (int i = n - 1; i >= 0; i--) {
        for (int &x : g[i]) {
            x = dp[x];
        }
        sort(g[i].begin(), g[i].end());
        if (g[i].size() == 0) {
            dp[i] = 1;
        } else if (g[i].size() == 1) {
            dp[i] = g[i].back();
        } else {
            dp[i] = max(g[i][g[i].size() - 2] + 1, g[i][g[i].size() - 1]);
        }
    }
    printf("%d\n", dp[0]);
}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) solve();

  return 0;
}
