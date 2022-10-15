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

#define TASKNAME "FLOORI4"

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


int m;

int get4(ll x) {
   	int tmp = (x * 1LL * x) % m;
   	tmp = (tmp * 1LL * tmp) % m;
   	return tmp;
}


int getSum(ll r) {
/*	#ifdef LOCAL
		ll res2 = 0;
		for (int i = 0; i <= r; i++)
			res2 = (res2 + get4(i)) % m;
		eprintf(LLD" "LLD" ", r, res2);
	#endif*/
//	eprintf(LLD"\n", r);
	r %= 30 * m;
	ll res = 1;
	res = (res * 1LL * r) % (30 * m);
	res = (res * 1LL * (r + 1)) % (30 * m);
	res = (res * 1LL * (2 * r + 1)) % (30 * m);
	res = (res * 1LL * ((3 * r * r + 3 * r - 1) % (30 * m))) % (30 * m);
	if (res < 0) res += 30 * m;
	assert(res % 30 == 0);
/*	#ifdef LOCAL
		eprintf(LLD"\n", res / 30);
		assert(res / 30 == res2);
	#endif*/
	return res / 30;
}

int getSum(ll l, ll r) {
	return (getSum(r) - getSum(l-1) + m) % m;
}



void solve(){
	ll n;
	scanf(LLD "%d", &n,&m);
	getSum(1027960);
	int res = 0;
	ll left;
	for (left = 1; left * left <= n; left++)
		res = (res + get4(left) * (n / left)) % m;
	for (ll val = left; val >= 1; val--) {
		ll rg = n / val;
		ll lf = n / (val+1) + 1;
//		eprintf(LLD" "LLD" "LLD"\n", val, lf, rg);
		if (rg < lf) continue;
		assert(n / lf == val);
		assert(n / rg == val);
		assert(lf == 1 || n / (lf - 1) > val);
		assert(n / (rg + 1) < val);
		assert(lf <= rg);
		lf = max(lf, left);
		if (lf <= rg) {
//			eprintf("["LLD".."LLD"] with val "LLD"\n", lf, rg, val);
			res = (res + getSum(lf, rg) * val) % m;
		}
	}
	printf("%d\n", res);
}


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

    int t;
    scanf("%d",&t);
    for (int i = 0; i < t; i++) {
		solve();    	
    }
      
    return 0;
}