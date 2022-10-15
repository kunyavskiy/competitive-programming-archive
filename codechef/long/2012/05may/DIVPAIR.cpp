#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <queue>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define setval(a,v) memset(a,v,sizeof(a))

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int t;
  scanf("%d",&t);

  while (t --> 0){
    int n,m;
    scanf("%d %d",&n,&m);

    ll ans = 0;                 

    vector<pair<int,int> > d;
    d.pb(mp(0,(n/m)));
    d.pb(mp(0,-1));
    d.pb(mp(1,1));
    d.pb(mp(m-n%m,1));
    d.pb(mp((m+1)/2,-1));
    d.pb(mp(m,0));

    sort(d.begin(),d.end());

    int cur = d[0].second;

    for (int i = 1; i < 6; i++){
//        cerr << cur <<" "<<d[i].first <<" "<<(d[i].first - d[i-1].first)<<endl;
        ans += (cur*1LL*(cur+1)/2LL)*1LL*(d[i].first - d[i-1].first);
        cur += d[i].second;
    }

    

    /*for (int i = 0; i < m; i++){
        int to = a;
        if (i == 0) to--;
        if (i >= m - n%m) to++;
        if (i >= (m+1)/2) to--;

        ans += to*1LL*(to+1)/2;
    }*/
    

    printf("%lld\n",ans);
  }

  return 0;
}
                                                            
