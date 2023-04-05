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

const int MAXN = 10000;

int cost[MAXN];

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int l = 0;
  for (int i = 1; i < MAXN; i++) {
    if ((i & (i - 1)) == 0) l++;
    cost[i] = cost[i - 1] + l;
  }

  vector<int> dp(MAXN);
  dp[1] = 1;

  for (int i = 2; i < MAXN; i++) {
    dp[i] = 1e9;
    for (int j = 1; j < i; j++) {
      dp[i] = min(dp[i], cost[i] + (j > 1 ? cost[j] : 0) + dp[j] + dp[i - j]);
    }
  }

  double phi = (sqrt(5) - 1) / 2.0;
  eprintf("%lf\n", phi);

  for (int i = 0; i < MAXN; i++) {
    printf("%d: %d; opt=", i, dp[i]);
    auto is_opt = [&](int j) {
      return dp[i] == cost[i] + (j > 1 ? cost[j] : 0) + dp[j] + dp[i - j];
    };
    if (!is_opt(i * (1.0 - phi)) && !is_opt(i * (1.0 - phi) + 1)) {
      printf("!!!! %d !!!!", (int)(i * (1.0 - phi)));
    }
    int min_id = MAXN, max_id = 1;
    for (int j = 1; j < i; j++) {
      if (is_opt(j)) {
        min_id = min(min_id, j);
        max_id = max(max_id, j);
      }
    }
    printf(" %d %d", min_id, max_id);
    printf("\n");
  }

  return 0;
}
