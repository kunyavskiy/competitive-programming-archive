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


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  	int n,k;
  	scanf("%d%d",&n,&k);

  	vector<ll> dp(2*k+1, -1e18);
  	dp[0] = 0;

  	for (int i = 0; i < n; i++){
  		ll p;
  		scanf(LLD, &p);
  		for (int j = min(i, 2*k - 1); j >= 0; j--)
  			if (j & 1)
  				dp[j+1] = max(dp[j+1], dp[j] + p);
  			else
  			    dp[j+1] = max(dp[j+1], dp[j] - p);

//  		for (int j = 0; j <= 2*k; j++)
//  			printf(LLD"%c", dp[j], " \n"[j==2*k]);
  	}

  	printf(LLD"\n", *max_element(dp.begin(), dp.end()));
    return 0;
}