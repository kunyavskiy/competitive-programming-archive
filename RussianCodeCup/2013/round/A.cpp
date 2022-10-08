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

typedef long long ll;
typedef long double ld;

const int MAXN = 110000;

ll a[MAXN];


void solve(){
    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; i++)
    	scanf(LLD,&a[i]);
    sort(a,a+n);

    int u[2],t;
    scanf("%d %d %d",&u[0],&u[1],&t);
    int b1,L1,b2,L2;

    scanf("%d %d %d %d",&b1,&L1,&b2,&L2);
    --b1,--b2;

    ll ans = 1LL<<60;
    int id1 = lower_bound(a,a+n,L1) - a;
    int id2 = lower_bound(a,a+n,L2) - a;


    if (b1 == b2){
    	ans = abs(L2 - L1) * 1LL * u[b1];
        for (int i = id1-3; i < id1+3; i++)
        	if (0 <= i && i < n)
	    	    for (int j = id2-3; j < id2+3; j++)
    	    		if (0 <= j && j < n) {
    	    			ans = min(ans, abs(a[i] - L1) * u[b2] + 2*t + abs(a[j] - L2) * u[b2] + abs(a[i] - a[j]) * u[1-b2]);
    	    		}

    }
    else {
        for (int i = id1-3; i < id1+3; i++)
        	if (0 <= i && i < n)
	        	ans = min(ans,abs(a[i] - L1) * u[b1] + t + abs(a[i] - L2) * u[b2]);

        for (int i = id2-3; i < id2+3; i++)
        	if (0 <= i && i < n)
		    	ans = min(ans,abs(a[i] - L1) * u[b1] + t + abs(a[i] - L2) * u[b2]);
    }	
      
    printf(LLD"\n",ans);

}


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	int n;
  	scanf("%d",&n);
  	for (int i = 0; i < n; i++)
  		solve();

    TIMESTAMP(end);
    return 0;
}