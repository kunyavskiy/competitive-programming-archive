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

vector<int> g[55];

int maxd[55];
int ans[55]; 
int d[55];
int n,m;

int bfs(int v){
    memset(d,-1,sizeof(d));

    d[v] = 0;
    queue<int> q;
    q.push(v);

    for (;!q.empty();){
        int v = q.front();
        q.pop();
        for (int i = 0; i < (int)g[v].size(); i++){
            if (d[g[v][i]] == -1){
                d[g[v][i]] = d[v] + 1;
                q.push(g[v][i]);
            }
            if (abs(d[v]-d[g[v][i]]) != 1){
                printf("-1\n");
                exit(0);
            }
        }
    }
    
    return *max_element(d,d+n);
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    cin >> m >> n;
    
    for (int i = 0; i < m; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        --a,--b;
        g[a].pb(b);
        g[b].pb(a);
    }

    for (int i = 0; i < n; i++)
        maxd[i] = bfs(i);

    bfs(max_element(maxd,maxd+n)-maxd);

    memset(ans,-1,sizeof(ans));
    int res = *max_element(maxd,maxd+n);

    for (int i = 0; i < n; i++){
        ans[i] = d[i];        
    }

    for (int i = 0; i < n; i++){
        if (ans[i] != -1)
            continue;
        bfs(i);
        res = 49;
        for (int j = 0; j < n; j++)
            if (d[j] != -1)
                ans[j] = 49 - d[j];
    }

    printf("%d\n",res);

    for (int j = 0; j < n; j++)
        printf("%d ",ans[j]+1);
    return 0;
}