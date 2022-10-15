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

#define TASKNAME "D"

typedef long long ll;
typedef long double ld;


const ll INF = 2e18+100;

ll n,q;

ll solve(ll R,ll t){
	if (t <= n)
		return min(t,R);
	t -= n;
	if (n < 2e9 && n * (n + 1) / 2 < t){
		ll ans = R*(R+1) / 2;
		t -= n * (n + 1) / 2;
		ans += (t / n) * R;
		ans += R;
		ans += min(R, t % n);
		return ans;
	}
	ll Lf = 0;
	ll Rg = min(t, (ll)2e9);

	while (Rg - Lf > 1){
		ll mid = (Lf + Rg) / 2;
		if (mid * (mid + 1) / 2 > t)
			Rg = mid;
		else
			Lf = mid;
	}   
    ll first = n - Rg;
    if (first > R) return R;
    ll ans = R + (R - first) * (R - first + 1) / 2;
    ll extra = (Rg * (Rg + 1)) / 2 - t;
    ll last = n - extra;
    ans -= max(0LL, R - last);
	return ans;
}

ll solve(ll L,ll R,ll t){
	return solve(R,t) - ((L != 1)? solve(L-1,t) : 0);
}

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  int q;
  scanf(LLD" %d", &n,&q);

  for (int i = 0; i < q; i++){
  	ll L,R,t;
  	scanf(LLD" "LLD" "LLD,&L,&R,&t);
  	printf(LLD"\n",solve(L,R,t));
  }
      
  TIMESTAMP(end);
  return 0;
}