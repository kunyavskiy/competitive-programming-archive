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

#define TASKNAME "A"

typedef long long ll;
typedef long double ld;

int a[2],b[2],c[2];

ll solve(pair<int,int> a,pair<int,int> b,pair<int,int> c){
	if (a < c) swap(a,c);
	if (a < b) swap(a,b);
	if (b < c) swap(b,c);
	return a.first * 1LL * a.second + b.first * max(0,b.second - a.second) + c.first * max(0,c.second - max(a.second,b.second));
}


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	while (scanf("%d %d %d %d %d %d",&a[0],&a[1],&b[0],&b[1],&c[0],&c[1]) == 6){
  		if (!a[0] && !a[1] && !b[0] && !b[1] && !c[0] && !c[1])
  			break;
  		ll ans = 1LL<<60;
  		for (int i = 0; i < 2; i++){
  			for (int j = 0; j < 2; j++){
  				for (int k = 0; k < 2; k++){
  					ans = min(ans,solve(mp(a[0],a[1]),mp(b[0],b[1]),mp(c[0],c[1])));
  					swap(c[0],c[1]);
  				}
  				swap(b[0],b[1]);
  			}
  			swap(a[0],a[1]);
  		}
  		printf(LLD"\n",ans);
  	}

      
  TIMESTAMP(end);
  return 0;
}