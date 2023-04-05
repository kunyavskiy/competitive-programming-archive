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

const int P = int(1e9) + 7;

int dfs(int s, const vector<vector<int>> & ed, vector<int> & dp) {
  if (dp[s] != -1) {
    return dp[s];
  }
  dp[s] = 1;
  for (int v : ed[s]) {
    dp[s] = max(dp[s], dfs(v, ed, dp) + 1);
  }
  return dp[s];
}

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  vector <vector<int>> ed(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    ed[u].push_back(v);
  }
  ll sum = 0;
  vector <int> dp(n, -1);
  for (int i = 0; i < n; ++i) {
    sum += dfs(i, ed, dp);
  }
  printf("%lld\n", sum % P);

  return 0;
}
