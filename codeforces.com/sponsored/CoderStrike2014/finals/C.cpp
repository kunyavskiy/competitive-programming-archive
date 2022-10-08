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

const int MAXN = 310000;

pair<int,int> g[MAXN];

int deg[MAXN];
int deg0[MAXN];

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  	int n,p;
  	scanf("%d %d",&n,&p);
  	for (int i = 0; i < n; i++){
  		int a, b;
  		scanf("%d %d",&a,&b);
  		--a, --b;
  		deg[a]++, deg[b]++;
  		if (a > b) swap(a, b);
  		g[i] = mp(a,b);
  	}
  	memcpy(deg0, deg, sizeof(deg));
  	sort(deg, deg+n);
  	ll ans = 0;

  	for (int l = 0, r = n-1; l < n; l++){
  		while (r >= 0 && deg[l] + deg[r] >= p) r--;
  		ans += n - r - 1;
  	}
  	for (int i = 0; i < n; i++)
  		if (2*deg[i] >= p)
  			ans--;

  	assert(ans % 2 == 0);
  	ans /= 2;
  	memcpy(deg, deg0, sizeof(deg));
                                      

  	sort(g, g+n);

  	for (int i = 0; i < n; ){
  		int j = i;
  		while (g[i] == g[j]) j++;
  		if (deg[g[i].first] + deg[g[i].second] >= p &&
  		    deg[g[i].first] + deg[g[i].second] - (j - i) < p)
  		   	ans--;  			
  		i = j;
  	}

  	printf(LLD"\n", ans);      
    return 0;
}