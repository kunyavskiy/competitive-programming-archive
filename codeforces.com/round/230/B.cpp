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

int t[3][3];

ll dp[45][3][3][3];

ll solve(int n, int from, int mid, int to){
	ll& res = dp[n][from][mid][to];
	if (res != -1) return res;
	if (n == 0) return res = 0;

	res = solve(n - 1, from, to, mid) + 
	      t[from][to] + 
	      solve(n - 1, mid, from, to);
	res = min(res, solve(n - 1, from, mid, to) + 
	               t[from][mid] +
	               solve(n - 1, to, mid, from) +
	               t[mid][to] +
	               solve(n - 1, from, mid, to)
	               );

	return res;
}


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  	int n;
  	for (int i = 0; i < 3; i++)
  		for (int j = 0; j < 3; j++)
  			scanf("%d", &t[i][j]);
  	scanf("%d", &n);
  
  	memset(dp, -1, sizeof(dp));

    printf(LLD"\n", solve(n, 0, 1, 2));  
    return 0;
}