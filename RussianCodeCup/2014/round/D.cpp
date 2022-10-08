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

#define TASKNAME "D"

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

const int MOD = 1000000007;

void madd(int& a, int b){
	if ((a += b) >= MOD) a -= MOD;
}
int mmul(int a, int b){
	return (a * 1LL * b) % MOD;
}

const int MAXN = 5010;

int cnk[MAXN][MAXN];
int dp[MAXN];

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
    eprintf("%d\n", sizeof(cnk) / 1024 / 1024);
  #endif

    cnk[0][0] = 1;
    for (int i = 0; i < MAXN; i++)
    	for (int j = 0; j < MAXN; j++){
    		if (i) madd(cnk[i][j], cnk[i-1][j]);
    		if (i && j) madd(cnk[i][j], cnk[i-1][j-1]);
    	}

    int n;
    scanf("%d",&n);
    dp[0] = dp[1] = dp[2] = 1;
    for (int i = 3; i <= n; i++){
    	for (int j = 1; j < n; j += 2) {
    		madd(dp[i], mmul(dp[j], mmul(dp[i-j-1], cnk[i-1][j])));
    	}
    }
    printf("%d\n", dp[n]);
      
    return 0;
}