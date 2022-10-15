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


const int MAXN = 110000;

vector<pair<int,int> > r[MAXN];
int ans[MAXN];   
vector<int> g[MAXN];

int h[MAXN];
int st[MAXN];
int n,m;


void dfs1(int v,int p,int h){
    ::h[v] = h;
    for (int i = 0; i < (int)g[v].size(); i++)
        if (g[v][i] != p)
            dfs1(g[v][i],v,h+1);
}

void dfs2(int v,int p,int h){
    st[h] = v;
    for (int i = 0; i < (int)r[v].size(); i++)
        if (h >= r[v][i].first)
            ans[r[v][i].second] = st[h - r[v][i].first];

    for (int i = 0; i < (int)g[v].size(); i++)
        if (g[v][i] != p)
            dfs2(g[v][i],v,h+1);
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    
    scanf("%d %d",&n,&m);
    for (int i = 0; i < n-1; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        --a,--b;
        g[a].pb(b);
        g[b].pb(a);
    }

    for (int j = 0; j < m; j++){
        int a,b;
        scanf("%d %d",&a,&b);
        --a;
        r[a].pb(mp(b,j));
        ans[j] = -1;
    }

    dfs1(0,-1,0);
    int l = max_element(h,h+n) - h;
    dfs1(l,-1,0);
    int r = max_element(h,h+n) - h;

    dfs2(l,-1,0);
    dfs2(r,-1,0);

    for (int i = 0; i < m; i++)
        printf("%d\n",ans[i]+1);
    return 0;
}