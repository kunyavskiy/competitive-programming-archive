#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

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

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
    #define M_PI 3.1415926535897932384626433832795
    #define prev prev_dsfdfgfhgfh
    #define next next_mkdlsmfdgkl
    #define hash hash_mdfdsgdhgfm
    #undef assert
    #define assert(x) if (!(x)) throw 1
    #define sqrt(x) sqrt((double)(x))
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

vector<pair<int,int> > ans;

vector<int> g[110000];


bool dfs(int v,bool canup, int p = -1){
    bool used = false;
    for (int i = 0; i < (int)g[v].size(); i++){
       if (g[v][i] == p)
          continue;
       if (dfs(g[v][i],!used,v))
           used = true;
    }                             
    if (!used && canup){           
        ans.pb(mp(v,p));
        return true;
    }                
    return false;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

     int n;
     scanf("%d %*d",&n);
     for (int i = 0; i < n-1; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        --a,--b;
        g[a].pb(b);
        g[b].pb(a);
     }

     dfs(0,0);
     
     printf("%d\n",ans.size());

     for (int i = 0; i < (int)ans.size(); i++)
        printf("%d %d\n",ans[i].first+1,ans[i].second+1);
    return 0;
}