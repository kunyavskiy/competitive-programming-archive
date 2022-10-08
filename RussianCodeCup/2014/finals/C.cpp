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
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "C"

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

ll sadd(ll a, ll b){
	if ((a + b) >= 1.05e18) return 1.1e18;
	return a + b;
}

vector<ll> v(501);
vector<int> used;

void doit(long long x) {
  	    used.pb(x);
  		for (int i = 500; i >= x; i--) {
  			v[i] = sadd(v[i], v[i-x]);
  		}
}

int main(){
  #ifdef LOCAL
	assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  	v[0] = 1;
  	for (int y = 10; y <= 70; y++){
  	    int x = y/10;
  	    doit(x);
  	}

  	assert(v[250] == 0);

  	long long x;
	cin >> x;
	ll x0 = x;
	while (x) {
//		eprintf("%I64d\n", x);
		int best = 0;
		for (int i = 0; i < 250; i++)
			if (v[i] <= x && v[i] > v[best])
				best = i;
		x -= v[best];
		assert(x >= 0);
		doit(500-best);
	}
//	eprintf("%I64d %I64d\n", v[500], x0);
	assert(v[500] == x0);
	printf("%d %d\n", used.size(), 500);
	for (int i = 0; i < (int)used.size(); i++)
		printf("%d ", used[i]);
	printf("\n");

    return 0;
}