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

pair<int,int> tree[300000];

int n;
pair<int,int> x[110000];

int lst = 0;

#define max max_mklk

template<typename T>
inline T max(T l,T r){
    return (l > r)?l:r;
}

void init(){
    sort(x,x+n);
    lst = 2;

    while (lst < n)
        lst *= 2;

    for (int i = 0; i < n; i++)
        tree[i+lst] = mp(x[i].second,i);
    for (int i = n; i < lst; i++)
        tree[i+lst] = mp(-1,-1);

    for (int i = lst-1; i > 0; i--)
        tree[i] = max(tree[2*i],tree[2*i+1]);   

}

void update(int pos){
    pos += lst;
    tree[pos] = mp(-1,-1);
    for (pos/=2; pos; pos/=2)
        tree[pos] = max(tree[2*pos],tree[2*pos+1]);   
}

pair<int,int> get(int v,int l,int r,int L,int R){
    if (r < L || R < l)
        return mp(-1,-1);
    if (L <= l && r <= R)
        return tree[v];
    return max(get(2*v,l,(l+r)/2,L,R),get(2*v+1,(l+r)/2+1,r,L,R));
}

void solve(){
    scanf("%d",&n);
    for (int i = 0; i < n; i++)
        scanf("%d %d",&x[i].first,&x[i].second);
    init();

    vector<int> ans;

    for (;tree[1] != mp(-1,-1);){
        int lpos = 0;
        int cnt = 0;
        while (lpos >= 0){
            pair<int,int> tmp = get(1,0,lst-1,lpos,n-1);
            lpos = tmp.second;
            if (tmp.second != -1)
                update(tmp.second),cnt++;
        }
        ans.pb(cnt);
    }

    printf("%d\n",ans.size());

    for (int i = 0; i < (int)ans.size(); i++)
        printf("%d ",ans[i]);
    printf("\n");
}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int t;
  scanf("%d",&t);

  for (int i = 0; i < t; i++)
    solve();
    
  

  return 0;
}

