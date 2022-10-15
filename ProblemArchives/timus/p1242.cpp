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


vector<int> g[1100];
vector<int> gt[1100];
bool bad[1100];
bool used[1100];

bool dfs(int v,vector<int>* g){
    if (bad[v])
        return true;
    if (used[v])
        return false;
    used[v] = true;
    for (int i = 0; i < (int)g[v].size(); i++)
        if (dfs(g[v][i],g))
            return true;
    return false;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int n;
    scanf("%d",&n);

    for (int a,b; scanf("%d %d",&a,&b) == 2; ){
        --a,--b;
        g[b].pb(a);
        gt[a].pb(b);
    }

    scanf(" BLOOD");

    for (int a; scanf("%d",&a) == 1; ){
        --a;
        bad[a] = true;
    }

    bool any = false;

    for (int i = 0; i < n; i++){
        memset(used,0,sizeof(used));
        if (dfs(i,g))
            continue;
        memset(used,0,sizeof(used));
        if (dfs(i,gt))
            continue;
        printf("%d ",i+1);
        any = true;
    }

    if (!any)
        printf("0\n");



    return 0;
}