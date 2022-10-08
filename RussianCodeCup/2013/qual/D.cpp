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

#define TASKNAME "D"

typedef long long ll;
typedef long double ld;


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
    int n;
	ll R;
	cin >> n >> R;
	vector<pair<ll,int> > evs;

	for (int i = 0; i < n; i++){
		int x,y,z;
		int vx,vy,vz;
		scanf("%d %d %d %d %d %d",&x,&y,&z,&vx,&vy,&vz);
		ll a = vx * 1LL *vx + vy * 1LL * vy + vz * 1LL * vz;
		ll b = 2LL * x * vx + 2LL * y * vy + 2LL * z * vz;
		double t0 = -b/(2.0 * a);
		ld res = a * t0 * t0 + b * t0 + x*ld(x)+y*ld(y)+z*ld(z);
		res = sqrt(res);
		eprintf("%lf %lf\n",(double)res,t0);

		if (res > R + 1e-9)
			continue;
		evs.pb(mp(ll(t0 - sqrt(R*R - res*res) / sqrt(vx * vx + vy * vy + vz*vz) + 1 - 1e-5),1));
		eprintf("+ "LLD"\n",evs.back().first);
		evs.pb(mp(ll(t0 + sqrt(R*R - res* res) / sqrt(vx * vx + vy * vy + vz*vz) + 1e-5) + 1,-1));
		eprintf("- "LLD"\n",evs.back().first);
		
	}

    sort(evs.begin(),evs.end());

    vector<int> sum(evs.size()+1);
    for (int i = 0; i < (int)evs.size(); i++)
    	sum[i+1] = sum[i] + evs[i].second; 

    int m;
    scanf("%d",&m);
    for (int i = 0; i < m; i++){
    	int t;
    	scanf("%d",&t);
    	int id = upper_bound(evs.begin(),evs.end(),mp(ll(t),2)) - evs.begin();
    	printf("%d\n",sum[id]);
    }
      
    TIMESTAMP(end);
  return 0;
}