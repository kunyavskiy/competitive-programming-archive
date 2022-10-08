//#include <iostream>
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
#include <stdarg.h>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if (_WIN32 || __WIN32__)
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "B"

typedef long long ll;
typedef long double ld;

double prob[3010][3010];
double win[3010];
double dp[3010];

void solve() {
  int n, k;
  double p;
  scanf("%d%d%lf", &n, &k, &p);
  for (int i = 0; i <= n; i++) {
    win[i] = dp[i] = 0;
    for (int j = 0; j <= i; j++) {
      prob[i][j] = 0;
    }
  }
  prob[0][0] = 1;

  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= i; j++) {
      if (j >= k) win[i] += prob[i][j];
      prob[i + 1][j + 1] += prob[i][j] * p;
      prob[i + 1][j] += prob[i][j] * (1 - p);
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < i; j++)
      dp[i] = max(dp[i], dp[j] + win[i - j]);
  }
  printf("%.10f\n", dp[n]);
}

int main() {
  freopen(TASKNAME".in", "r", stdin);
  freopen(TASKNAME".out", "w", stdout);

  TIMESTAMP(PreCalc);

  int _testNum;
  char buf[1000];
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d", &_testNum);


  for (int i = 0; i < _testNum; i++) {
    printf("Case #%d: ", i+1);
    solve();
    TIMESTAMPf("%d", i);
  }
  TIMESTAMP(end);
  return 0;
}
