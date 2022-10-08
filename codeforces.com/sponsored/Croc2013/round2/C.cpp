#include <iostream>
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

#define TASKNAME "C"

typedef long long ll;
typedef long double ld;


ll pow3(ll a){
	return a*a*a;
}

ll get(ll a,ll b,ll c){
	return pow3(a+b+c)-pow3(a)-pow3(b)-pow3(c);
}

ll getc(ll n,ll a,ll b){
	ll L = b;
	ll R = n / (a*b) + 1;
//	eprintf(LLD" "LLD"\n",L,R);
	while (R - L > 1){
		ll mid = L + (R - L) / 2;
		if (get(a,b,mid) <= n)
			L = mid;
		else
			R = mid;
	}

	if (get(a,b,L) == n)
		return L;
	return -1;
}


void solve(ll n){
  	if (n % 3){
  		printf("0\n");
  		return;
  	}

  	ll ans = 0;

    for (ll a = 1; get(a,a,a) <= n; a++) {
    	eprintf(LLD"\n",a);
    	for (ll b = a; get(a,b,b) <= n; b++){
     		ll c = getc(n,a,b);
			if (c < b) continue;
			int diff = 1 + (b != a) + (c != b);
			if (diff == 1)
				ans += 1;
			if (diff == 2)
				ans += 3;
			if (diff == 3)
				ans += 6;
    	}
    }	


     cout << ans << endl;
     	
}

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	ll n;     
  	cin >> n;
  	solve(n);
    		
    TIMESTAMP(end);
    return 0;
}