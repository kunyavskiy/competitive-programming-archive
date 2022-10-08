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

typedef long long ll;
typedef long double ld;

const int MAXN = 1010;
int t[MAXN][2*MAXN];
double ans[MAXN][MAXN];

void solve(){
  int n;
  scanf("%d",&n);
//  eprintf("n = %d\n", n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < 2*(i+1); j++) {
      scanf("%d",&t[i][j]);
//      eprintf("%d,%d: %d\n", i, j, t[i][j]);
    }
  for (int i = n; i >= 0; i--)
    ans[n][i] = 0;
  for (int i = n - 1; i >= 0; i--) {
    for (int j = 0; j <= i; j++){
      if (t[i][2*j] < t[i][2*j+1])
        ans[i][j] = ans[i+1][j] + t[i][2*j];
      else if (t[i][2*j] > t[i][2*j+1])
        ans[i][j] = ans[i+1][j+1] + t[i][2*j+1];
      else
        ans[i][j] = (ans[i+1][j] + ans[i+1][j+1])/2 + t[i][2*j+1];
//      eprintf("%.1f [%.1f %.1f %d %d] ", ans[i][j], ans[i+1][j], ans[i+1][j+1], t[i][2*j], t[i][2*j+1]);
    }
//    eprintf("\n");  
  }
  printf("%.10f\n", ans[0][0]);       
}


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

    int t;
    scanf("%d",&t);
    while (t-->0)
      solve();      
  return 0;
}
