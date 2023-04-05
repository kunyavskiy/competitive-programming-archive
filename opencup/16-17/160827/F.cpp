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
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "F"

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

const int MAXN = 10010;

int cnt[MAXN][4];

double dp[MAXN];

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int n, k;
  scanf("%d%d",&n,&k);

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      int count = 0;
      if (1 <= 2 * i - j && 2 * i - j <= n) count++;
      if (1 <= 2 * j - i && 2 * j - i <= n) count++;
      if ((i + j) % 2 == 0) count++;
      if (i == j) count = 1;
      cnt[i][count]++;
    }
/*
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 4; j++) {
      eprintf("%d ", cnt[i][j]);
    }
    eprintf("\n");
  }
*/
  dp[0] = 0;
  for (int i = 0; i < k; i++) {
    double old0 = dp[0];
    dp[0] = 0;
    for (int j = 1; j <= n; j++) {
      dp[0] += max(dp[j], old0);
    }
    dp[0] /= n;
    double prob[4];
    for (int j = 0; j < 4; j++) {
      prob[j] = 1.0 - pow(1.0 - j * 1.0 / n, i);
    }
    for (int j = 1; j <= n; j++) {
      double oldj = dp[j];
      dp[j] = 0;
      for (int q = 0; q < 4; q++) {
        dp[j] += cnt[j][q] * max(prob[q], oldj);
      }
      dp[j] /= n;
    }
    /*
    for (int j = 0; j <= n; j++) {
      eprintf("%.2f ", dp[j]);
    }
    eprintf("\n");
     */
  }

  printf("%.18f\n", dp[0]);
  return 0;
}
