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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "B"

typedef long long ll;
typedef long double ld;

const int MOD = 1000200013;

int pow(int a,int b){
	if (!b) return 1;
	if (b & 1) return (pow(a, b-1) * 1LL * a) % MOD;
	int tmp = pow(a, b/2);
	return (tmp * 1LL * tmp) % MOD;
}

int inv(int a){
	return pow(a, MOD - 2);
}

int f[2550];


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	int n,m;
  	scanf("%d %d",&n,&m);

  	f[0] = 1;
  	for (int i = 1; i <= n*m; i++)
  		f[i] = (f[i-1] * 1LL * i) % MOD;
  	
  	int ans = 0;

  	for (int i = 1; i <= n*m; i++){
  		int cur = f[n*m];             
  		cur = (cur * 1LL * inv(f[n*m - i])) % MOD;
  		cur = (cur * 1LL * inv(f[i])) % MOD;
  		cur = (cur * 1LL * cur) % MOD;
  		if (min(n,m) != 1)
	  		cur = (cur * 1LL * f[i]) % MOD;
  		if (i == n*m - 1 && min(n,m) != 1)
  			cur = (cur * 1LL * inv(2)) % MOD;
  		if (i == n*m)
  			cur = 1;
  		ans = (ans + cur) % MOD;
  	}

  	printf("%d\n", ans);
      
    TIMESTAMP(end);
    return 0;
}