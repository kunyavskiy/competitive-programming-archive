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

const int MAXN = 510;

int x[MAXN];
int y[MAXN];

struct segment {
  int x1, y1;
  int x2, y2;
};

vector<segment> ans;
int dp[MAXN][MAXN];

void print(int i, int j) {
  if (j - i <= 1) {
    return;
  }
  for (int k = i; k < j; k++) {
    int r = (x[k] - x[i]) + (y[k + 1] - y[j]) + dp[i][k] + dp[k+1][j];
    if (dp[i][j] == r) {
      ans.push_back({x[k], y[k], x[i], y[k]});
      ans.push_back({x[k + 1], y[k + 1], x[k + 1], y[j]});
      print(i, k);
      print(k + 1, j);
      return;
    }
  }
  assert(false);
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &x[i], &y[i]);
  }

  ans.push_back({x[0], y[0], x[0], 0});
  ans.push_back({x[0], 0, 0, 0});
  ans.push_back({x[n - 1], y[n - 1], x[0], y[n - 1]});

  for (int len = 3; len <= n; len++) {
    for (int i = 0; i + len <= n; i++) {
      int j = i + len - 1;
      int& ans = dp[i][j];
      ans = (int)(2e9);
      for (int k = i; k < j; k++) {
        int r = (x[k] - x[i]) + (y[k + 1] - y[j]) + dp[i][k] + dp[k+1][j];
        ans = min(ans, r);
      }
    }
  }

  print(0, n - 1);

  int ptr = 0;
  int res = 0;
  for (int i = 0; i < (int)ans.size(); i++) {
    int len = abs(ans[i].x2 - ans[i].x1) + abs(ans[i].y2 - ans[i].y1);
    if (len != 0) {
      ans[ptr++] = ans[i];
      res += len;
    }
  }

  printf("%d %d\n", ptr, res);
  for (int i = 0; i < ptr; i++) {
    printf("%d %d %d %d\n", ans[i].x1, ans[i].y1, ans[i].x2, ans[i].y2);
  }

  return 0;
}
