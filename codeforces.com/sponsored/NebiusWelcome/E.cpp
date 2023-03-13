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

const int MAXN = 20;

int dp[(1 << MAXN) + 5];
int g[(1 << MAXN) + 5];

void solve(int n, int m) {
    memset(g, 0, sizeof(g));
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        g[(1 << v)] |= 1 << u;
        g[(1 << u)] |= 1 << v;
    }
    for (int i = 0; i < (1 << n); i++) {
        g[i] = g[i & (i - 1)] | g[i & ~(i - 1)];
    }
    for (int start = 0; start < n; start++) {
        memset(dp, 0, sizeof(dp));
        dp[(1 << start)] = 1 << start;
        for (int mask = 0; mask < (1 << n); mask++) {
            for (int i = 0; i < n; i++) {
                if (!(mask & (1 << i)) && (g[dp[mask]] & (1 << i))) {
                    dp[mask | (1 << i)] |= (1 << i);
                }
            }
        }
        for (int mask = 0; mask < (1 << n); mask++) {
            if ((mask | g[mask]) == (1 << n) - 1 && (dp[mask] & g[1 << start]) != 0) {
                printf("Yes\n");
                vector<int> ans(n);
                vector<int> cycle;
                int cur = __builtin_ctz(dp[mask] & g[1 << start]);
                int mmask = mask;
                while (cur != start) {
                    cycle.push_back(cur);
                    mmask ^= (1 << cur);
                    for (int j = 0; j < n; j++) {
                        if ((g[1 << cur] & (1 << j)) && (dp[mmask] & (1 << j))) {
                            cur = j;
                            break;
                        }
                    }
                    assert(mmask & (1 << cur));
                }
                cycle.push_back(start);
                for (int i = 0; i < (int)cycle.size(); i++) {
                    ans[cycle[i]] = cycle[(i + 1) % cycle.size()];
                }
                for (int i = 0; i < n; i++) {
                    if (!(mask & (1 << i))) {
                        ans[i] = -1;
                        for (int j = 0; j < n; j++) {
                            if ((mask & (1 << j)) && (g[1 << i] & (1 << j))) {
                                ans[i] = j;
                                break;
                            }
                        }
                        assert(ans[i] != -1);
                    }
                }
                for (int x : ans) {
                    printf("%d ", x + 1);
                }
                printf("\n");
                return;
            }
        }
    }
    printf("No\n");
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
      solve(n, m);
  }

  return 0;
}
