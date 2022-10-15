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

#define TASKNAME "RAINBOWB"

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


const int MAXN = 1000010;
const int MOD = 1000000007;

int c[MAXN][7];

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

    c[0][0] = 1;
  	for (int i = 0; i < MAXN; i++)
  		for (int j = 0; j < 7; j++){
  			if (i) c[i][j] = (c[i][j] + c[i-1][j]) % MOD;
  			if (i && j) c[i][j] = (c[i][j] + c[i-1][j-1]) % MOD;
  		}

  	int res = 0;
  			
  	int n;
  	scanf("%d",&n);
  	for (int i = 1; i < n; i++) {
  		if ((n - i) % 2 != 0)
  			continue;
  		int t = (n - i) / 2;
  		res = (res + c[t - 1][5]) % MOD;
  	}
  	printf("%d\n", res);
      
    return 0;
}