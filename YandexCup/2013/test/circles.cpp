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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "circles"

typedef long long ll;
typedef long double ld;


ll dist(ll x1,ll y1,ll x2,ll y2){
	return (x1 - x2) * 1LL * (x1 - x2) + (y1 - y2) * 1LL * (y1 - y2);
}

ll gcd(ll a,ll b){
	return b ? gcd(b, a%b) : a;
}

int main(){
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  	int n;
  	scanf("%d",&n);
  	vector<pair<ll,ll> > ds;
  	for (int i = 0; i < n; i++){
  		ll x[3],y[3];
  		for (int j = 0; j < 3; j++)
  			cin >> x[j] >> y[j];
  		ll num = dist(x[0],y[0],x[1],y[1]) * 1LL *  dist(x[1],y[1],x[2],y[2]) * 1LL* dist(x[2],y[2],x[0],y[0]);
  		ll den = ((x[2] - x[0]) * 1LL * (y[1] - y[0]) - (y[2] - y[0]) * 1LL * (x[1] - x[0]));
  		den = den * den;
//  		if (den < 0) den = -den;
                                       

  		ll g = gcd(num,den);
  		num /= g;
  		den /= g;                      
  		ds.pb(mp(num,den));
  	}

  	sort(ds.begin(),ds.end());

  	int ans = 0;
  	for (int i = 0; i < n; ){
  		int j = i;
  		for (; j < n && ds[i] == ds[j]; j++);
  		ans = max(ans,j - i);
  		i = j;
  	}

  	printf("%d\n",ans);
      
    TIMESTAMP(end);
    return 0;
}