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


vector<pair<pair<int,int>,ll> > v;

int x[150];
int y[150];
int ord[150];


ll vp(ll x1,ll y1,ll x2,ll y2){
    return x1*y2-x2*y1;
}

ll s(int ){
   return 0LL;
}  

ll s(int i,int j){
    return vp(x[i],y[i],x[i]+x[j],y[i]+y[j]);
} 

ll s(int i,int j,int k){
    return vp(x[i],y[i],x[i]+x[j],y[i]+y[j])+vp(x[i]+x[j],y[i]+y[j],x[i]+x[j]+x[k],y[i]+y[j]+y[k]);
} 

bool cmp(int i,int j){
    ld ang1 = atan2(y[i],x[i]);
    ld ang2 = atan2(y[j],x[j]);
    if (abs(ang1 - ang2) < 0.1)
        return vp(x[i],y[i],x[j],y[j]) > 0;
    return ang1 < ang2;        
}


ll ans;


void update(pair<int,int> p,ll s1){
  vector<pair<pair<int,int>,ll> >::iterator pp = lower_bound(v.begin(),v.end(),mp(p,-(1LL<<60)));
  if (pp != v.end() && pp->first == p)
    ans = max(ans, abs(s1 + pp->second));

  pp = upper_bound(v.begin(),v.end(),mp(p,(1LL<<60)))-1;
  if (pp != v.begin()-1 && pp->first == p)
    ans = max(ans, abs(s1 + pp->second));
  //cerr << p.first <<" "<<p.second <<" "<< ans << endl;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int n;
  scanf("%d",&n);
  for (int i = 0; i < n; i++){
    scanf("%d %d",&x[i],&y[i]);
    ord[i] = i;
  }

  sort(ord,ord+n,cmp);

  v.reserve(n*n*n/6+n*n/2+n);

  for (int _i = 0; _i < n; _i++){
    int i = ord[_i];
    v.pb(mp(mp(x[i],y[i]),s(i)));
    for (int _j = _i; _j < n; _j++){
        int j = ord[_j];
        v.pb(mp(mp(x[i]+x[j],y[i]+y[j]),s(i,j)));
        for (int _k = _j; _k < n; _k++){
            int k = ord[_k];
            v.pb(mp(mp(x[i]+x[j]+x[k],y[i]+y[j]+y[k]),s(i,j,k)));
        }
     }
  }

  sort(v.begin(),v.end());

  for (int i = 0; i < n; i++)
    x[i] *= -1, y[i] *= -1;

  sort(ord,ord+n,cmp);



  for (int _i = 0; _i < n; _i++){
    int i = ord[_i];
    update(mp(x[i],y[i]),s(i));
    for (int _j = _i; _j < n; _j++){
        int j = ord[_j];
        update(mp(x[i]+x[j],y[i]+y[j]),s(i,j));
        for (int _k = _j; _k < n; _k++){
            int k = ord[_k];
            update(mp(x[i]+x[j]+x[k],y[i]+y[j]+y[k]),s(i,j,k));
        }
     }
  }


  cout << ans/2 <<"."<<(ans%2)*5 << endl;

  return 0;
}