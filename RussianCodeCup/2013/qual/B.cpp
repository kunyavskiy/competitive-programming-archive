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

#define TASKNAME "B"

typedef long long ll;
typedef long double ld;

const int MAXN = 5100;

int a[MAXN];
ll sum[MAXN]; 

ll c4(ll len){
	return len * (len-1) * (len - 2) * (len - 3) / 4 / 3 / 2 / 1;
}

ll c3(ll len){
	return len * (len - 1) * (len - 2) / 3 / 2;
}


ll c2(ll len){
	return len * (len - 1) / 2;
}

int n;

int get(int l,int r){
	return upper_bound(a,a+n,r) - lower_bound(a,a+n,l);
}

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

    int tst;
    scanf("%d",&tst);

  	while (tst --> 0){
  		scanf("%d",&n);
  		for (int i = 0; i < n; i++)
  			scanf("%d",&a[i]);

  		sort(a,a+n);
  		ll ans = 0;

  		eprintf("%d %d %d %d\n",a[0],a[1],a[2],a[3]);

                          		

  		for (int i = 0; i < n; i++)
  			for (int j = 0; j < n; j++) if (i != j){
  				int maxsz = 2*a[j] + a[i] - 1;
  				int cnt = get(a[i],maxsz);
  				cnt -= get(a[i],a[i]);
  				if (a[i] != a[j]) cnt -= get(a[j],a[j]);
  				ll cur = 0;
  				cur += cnt * (get(a[j],a[j]) - 1 - (a[i] == a[j]));
  				cur += c2(get(a[j],a[j]) - 1 - (a[i] == a[j]));
  				eprintf("%d %d cnt = %d, ans = "LLD"\n",a[i],a[j],cnt,cur);
  				ans += cur;
  			}

  		for (int i = 0; i < n; i++)
  			if (!i || a[i] != a[i-1])
  				ans -= c3(get(a[i],a[i])) * 1LL * (get(0,3*a[i]-1) - get(a[i],a[i]));

  	     
        assert(ans % 2 == 0);
        ans /= 2;


		for (int i = 0; i < n; i++)
			if (!i || a[i] != a[i-1])
				ans -= 2 * c4(get(a[i],a[i])); 

		for (int i = 0; i < n; i++)
			if (!i || a[i] != a[i-1])
				for (int j = i+1; j < n; j++)
					if (a[j] != a[j-1])
						ans -= c2(get(a[i],a[i])) * 1LL * c2(get(a[j],a[j]));


  		printf(LLD"\n",ans);
  	}
      
  TIMESTAMP(end);
  return 0;
}