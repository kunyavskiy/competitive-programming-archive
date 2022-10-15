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
    #undef assert
    #define assert(x) if (!(x)) throw 1
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const int MAXN = 50000;
const int MAXLOG = 17;

vector<int> g[MAXN];
vector<int> l[MAXN];

int sum[MAXN];
int h[MAXN];

int up[MAXLOG][MAXN];
int n;

void dfs(int v,int p,int sum,int h){
    ::h[v] = h;
    ::up[0][v] = p;
    ::sum[v] = sum;

    for (int i = 0; i < g[v].size(); i++)
        if (g[v][i] != p)
            dfs(g[v][i],v,sum+l[v][i],h+1);
}

int lca(int a,int b){
    if (h[a] > h[b])
        swap(a,b);
    int t = h[b] - h[a];
    for (int i = 0; i < MAXLOG; i++)
        if (t & (1<<i))
            b = up[i][b];

    if (a == b)
        return b;
    for (int i = MAXLOG-1; i >= 0; --i){
        if (up[i][a] != up[i][b])
            a = up[i][a], b = up[i][b];
    }
    return up[0][a];
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    scanf("%d",&n);
    for (int i = 0; i < n-1; i++){
        int a,b,w;
        scanf("%d %d %d",&a,&b,&w);
        g[a].pb(b),l[a].pb(w);
        g[b].pb(a),l[b].pb(w);
    }

    dfs(0,0,0,0);

    for (int i = 1; i < MAXLOG; i++)
        for (int j = 0; j < n; j++)
            up[i][j] = up[i-1][up[i-1][j]];

    int m;
    scanf("%d",&m);

    for (int i = 0; i < m; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        int l = lca(a,b);
        printf("%d\n",sum[a] + sum[b] - 2*sum[l]);
    }

   

    return 0;
}