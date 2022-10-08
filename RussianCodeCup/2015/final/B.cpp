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

#define TASKNAME "B"

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

const int INF = 1e9;

typedef long long ll;
typedef long double ld;


int dp[251][251][251];
int a[251];
int pref[251];
int suff[251];


void relax(int& a, int b) {
  a = min(a, b);
}

int main() {
  #ifdef LOCAL
  assert(freopen (TASKNAME".in", "r", stdin));
  assert(freopen (TASKNAME".out", "w", stdout));
  #endif

  int n, t, start;
  scanf ("%d%d%d", &n, &t, &start);
  --start;
  for (int i = 0; i < n; i++) {
    scanf ("%d", &a[i]);
  }

  for (int i = 0; i < n; i++) {
    pref[i+1] = pref[i] + a[i];
  }

  for (int i = n - 1; i >= 0; i--) {
    suff[i] = suff[i+1] + a[i];
  }

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      for (int k = 0; k <= t; k++)
        dp[i][j][k] = INF;

  for (int i = 0; i < n; i++)
    dp[i][i][0] = 0;

  int ans = INF;

  for (int i = 0; i <= t; i++) {
    for (int l = 0; l < n; l++) {
      for (int r = 0; r < n; r++) {
        if (dp[l][r][i] == INF)
          continue;
        //eprintf("dp[%d][%d][%d] = %d\n", l, r, i, dp[l][r][i]);
        if (abs (l - start) <= t - i) {
          //eprintf("ans %d + %d + %d = %d\n", dp[l][r][i], pref[min (l, r)] * t, suff[max (l, r) + 1] * t, dp[l][r][i] + pref[min (l, r)] * t + suff[max (l, r) + 1] * t);
          ans = min (ans, dp[l][r][i] + pref[min (l, r)] * t + suff[max (l, r) + 1] * t);
        }
        if (l < r) {
          if (l != 0) {
            relax (dp[l - 1][r][i + 1], dp[l][r][i] + a[l - 1] * (i + 1));
          }
          if (i + r - l < t && r != n - 1) {
            relax (dp[r + 1][l][i + r - l + 1], dp[l][r][i] + a[r + 1] * (i + r - l + 1));
          }
        } else {
          if (l != n - 1) {
            relax (dp[l + 1][r][i + 1], dp[l][r][i] + a[l + 1] * (i + 1));
          }
          if (i + r - l < t && r != 0) {
            relax (dp[r - 1][l][i + r - l + 1], dp[l][r][i] + a[r - 1] * (i + r - l + 1));
          }
        }
      }
    }
  }


  printf("%d\n", accumulate (a, a+n, 0) * t - ans);
  return 0;
}
