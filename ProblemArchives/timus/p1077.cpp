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

vector<vector<int> > ans;
vector<int> cur;


const int MAXN = 210;

vector<int> g[MAXN];

int dfs(int v,int to,int p){
    cur.pb(v);
    if (v == to)
        return 1;

    for (int i = 0; i < (int)g[v].size(); i++)
        if (g[v][i] != p && dfs(g[v][i],to,v))
            return 1;
    cur.pop_back();
    return 0;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int n,m;
    scanf("%d %d",&n,&m);
    for (int i = 0; i < m; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        cur.clear();
        if (dfs(a,b,-1)){
           if (cur.size() > 2)
               ans.pb(cur);
        }
        else {
           g[a].pb(b);
           g[b].pb(a); 
        }
    }

    printf("%d\n",ans.size());
    for (int i = 0; i < (int)ans.size(); i++){
        printf("%d",ans[i].size());
        for (int j = 0; j < (int)ans[i].size(); j++)
            printf(" %d",ans[i][j]);
        printf("\n");
    }

    return 0;
}