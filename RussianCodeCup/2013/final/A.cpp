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

#define TASKNAME "A"

#ifdef LOCAL
static struct __timestamper {
	~__timestamper(){
		TIMESTAMP(end);
	}
} __TIMESTAMPER;
#endif

typedef long long ll;
typedef long double ld;

ll getrem(ll a, ll b, ll rem){
	while (b % 2 != rem) --b;
	while (a % 2 != rem) ++a;
	return (b - a) / 2 + 1;
}


ll getcnt(ll n,ll k){
	if (n == 0) return 0;
	if (n % 2 == 1){
		return (n/2);
	}
    ll x = n/2;
    ll y = x/2;
	return getcnt(y, k) + (x - y) + getrem(x+1, n, !(n%2));
}

ll solve(ll n,ll k){
	assert(n != 0);
    assert(k >= 0);
    assert(k < getcnt(n,k));
	if (n % 2 == 1){
		return n - 2*k - 1;
	}
    ll x = n/2;
    if (n - 2*k - 1 > x)
    	return n - 2*k - 1;
    k -= getrem(x+1, n, !(n%2));
    assert(k >= 0);
    ll y = x/2;
    if (x - k > y)
    	return x - k;
    k -= x - y;
    assert(k >= 0);
	return solve(y, k);
}



int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	int t;
  	scanf("%d",&t);

  	while (t-->0){
  		ll n,k;
  		scanf(LLD" "LLD,&n,&k);
  		ll cnt = getcnt(n,k) - k;
  		if (cnt < 0)
  			printf("-1\n");
  		else
  		{
/*  			#ifdef LOCAL
  				printf(LLD" "LLD"   ",n,k);
  			#endif*/
  			ll res = solve(n, cnt);
  			assert(1 <= res && res < n);
  			printf(LLD"\n", res);
  		}
  	}
      
  return 0;
}