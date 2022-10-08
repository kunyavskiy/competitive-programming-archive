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

const int MAXN = 110000;

pair<int,int> val[MAXN];
int n;

int cnt[MAXN];

int r[MAXN],a[MAXN];


int bit[MAXN];

void Fupdate(int pos,int val){
    for (;pos < n; pos = (pos | (pos+1)))
        bit[pos]+=val;
}

int Fget(int pos){
    int ans = 0;
    for (;pos != -1; pos = (pos & (pos-1))-1)
        ans += bit[pos];
    return ans;
}

int Fget(int l,int r){
    l = lower_bound(val,val+n,mp(l,-(1<<30))) - val;
    r = upper_bound(val,val+n,mp(r,-(1<<30))) - val - 1;
    return Fget(r) - Fget(l-1);
}

vector<pair<int,int> > reqs[MAXN];

int ans[MAXN];

int tree[MAXN*4];
int lst = 0;

void Tinit(int n){
    lst = 2;
    while (lst < n)
        lst++;
    memset(tree,-1,sizeof(tree));
}

void Tupdate(int pos,int val){
    pos += lst;
    tree[pos] = val;
    for (pos /= 2;pos; pos /= 2)
        tree[pos] = max(tree[pos*2],tree[pos*2+1]);
}

int Tget(int v,int l,int r,int L,int R){
    if (r < L || R < l)
        return -1;
    if (L <= l && r <= R)
        return tree[v];
    return max(Tget(2*v,l,(l+r)/2,L,R),
               Tget(2*v+1,(l+r)/2+1,L,R));
}

void Tget(int l,int r){
    l = lower_bound(val,val+n,mp(l,-(1<<30))) - val;
    r = upper_bound(val,val+n,mp(r,-(1<<30))) - val - 1;
    return Tget(1,0,lst-1,l,r);
}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  scanf("%d %d",&n,&k);

  for (int i = 0; i < n; i++)
    scanf("%d",&val[i].first),r[i] = val[i].first;
  for (int i = 0; i < n; i++)
    scanf("%d",&val[i].second), a[i] = val[i].second;

  sort(val.begin(),val.end());

  for (int i = 0; i < n; ){
    int j = i;
    for (;j < n && val[j].first == val[i].first; j++)
        update(i,1);

    for (;i < j; i++)
        cnt[i] = Fget(val[i].first - k,val[i].first+k);
  }

  int q;
  scanf("%d",&q);

  for (int i = 0; i < q; i++){
    int x,y;
    scanf("%d %d",&x,&y);
    --x,--y;
    x = lower_bound(val,val+n,mp(r[x],a[x]))-val;
    y = lower_bound(val,val+n,mp(r[y],a[y]))-val;
    if (x > y)
        swap(x,y);
    g[y].pb(mp(x,i));
    ans[i] = -1;
  }

  Tinit(n);

  for (int i = n-1; i >= 0; ){
    int j = i;
    for (;j >= 0 && val[j].first == val[i].first;j--)
        Tupdate(j,cnt[j]);
    for (;i >= j; i--){
        for (int k = 0; k < (int)reqs[i].size(); k++)
            ans[reqs[i][k].second] = Tget(max(val[i].second-k,val[reqs[i][k].first].second-k),
                                          min(val[i].second+K,val[reqs[i][k].first].second+k))
    }
  }

  for (int i = 0; i < n; i++)
    printf("%d\n",ans[i]);


  return 0;
}

