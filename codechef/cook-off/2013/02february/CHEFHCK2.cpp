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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "CHEFHCK2"

typedef long long ll;
typedef long double ld;

const ll MAXV = 3141LL*3141LL*3141LL*3141LL*3141LL+10;

vector<ll> pows;

ll sqrt(ll a){
	ll x = sqrt((ld)a);
	while (x*x < a) x++;
	while (x*x > a) x--;
	return x;
}

bool checkSqr(ll a){
	ll b = sqrt(a);
	return b*b == a;
}

bool checkPow(ll a){
	if (a <= 3) return 0;
	return checkSqr(a) || binary_search(pows.begin(),pows.end(),a);
}

ll getPowId(ll a){
	if (a <= 3) return 0;
	ll s = sqrt(a);
	return s - 1 + (upper_bound(pows.begin(),pows.end(), a) - pows.begin());
}


ll solve(ll a){
	if (a == 1) return 2;
	int cnt = 1;
	ll l,r;
	l = 2, r = 4;
	while (r <= a){
	    cnt++;
	    l *= 2;
	    r *= 2;
	}
//	cerr << cnt <<" "<<l <<" "<<r<<endl;
	if (l == a)
		return cnt;
	cnt++;
	while (r - l > 1){
		ll m = (l+r)/2;
		cnt++;
		if (m == a)
			return cnt;
		if (m < a)
			l = m;
		else
			r = m;
	}
	return cnt;
}   	


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	for (ll i = 2; i*i*i <= MAXV; i++){
  		ll t = i*i*i;
  		if (!checkSqr(t)) pows.pb(t);
  		while (t <= MAXV / i){
  			t *= i;
  			if (!checkSqr(t)) pows.pb(t);
  		}
	}

	sort(pows.begin(),pows.end());
	pows.erase(unique(pows.begin(),pows.end()),pows.end());
                              


	int n;
	scanf("%d",&n);

	for (int i = 0; i < n; i++){
		ll x;
		scanf(LLD,&x);
//		cerr << x<< " "<<checkPow(x) <<" "<<getPowId(x) << endl;
		if (checkPow(x))
			printf(LLD" ",getPowId(x));
		else
			printf(LLD" ",solve(x - getPowId(x) + 1));
	}
      
    return 0;
}