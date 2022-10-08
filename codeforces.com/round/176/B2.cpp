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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "B2"

typedef long long ll;
typedef long double ld;


bool check(ll a,ll k,ll b){
	return a <= k*(k+1)/2 - (k-b)*(k-b+1)/2 - b + 1;
}


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
    ll n,k;
    scanf(LLD" "LLD,&n,&k);

    if (!check(n,k,k)){
    	printf("-1\n");
    	return 0;
    }

    if (n == 1){
    	printf("0\n");
    	return 0;	
   	}


    ll l = 0;
    ll r = k;

    while (r - l > 1){
    	ll m = (l+r)/2;
    	if (check(n,k,m))
    		r = m;
    	else
    		l = m;
    }

    printf(LLD"\n",r);

      
  TIMESTAMP(end);
  return 0;
}