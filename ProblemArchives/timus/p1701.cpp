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

vector<int> g[MAXN];
vector<int> d[MAXN];
vector<int> id[MAXN];

int n,m;

int a[MAXN];
int b[MAXN];
int c[MAXN];

int val[MAXN];
int temp[MAXN];

int error;

void dfs(int v,int sum,int mid){
    if (sum < 0)
        error = min(error, mid);    
    val[v] = sum;
    for (int i = 0; i < (int)g[v].size(); i++)
        if (val[g[v][i]] == -1){
            dfs(g[v][i], sum - d[v][i], max(mid,id[v][i]));
        }
}

int dfs1(int v,int sum){
    temp[v] = sum;
    for (int i = 0; i < (int)g[v].size(); i++)
        if (temp[g[v][i]] == -1)
            temp[v] = min(temp[v],dfs1(g[v][i], sum - d[v][i]));
    return temp[v];
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    memset(val,-1,sizeof(val));
    memset(temp,-1,sizeof(temp));

    scanf("%d %d",&n,&m);
    for (int i = 0; i < m; i++){
        scanf("%d %d %d",&a[i],&b[i],&c[i]);
        g[a[i]].pb(b[i]);
        g[b[i]].pb(a[i]);
        d[a[i]].pb(c[i]);
        d[b[i]].pb(-c[i]);
        id[a[i]].pb(i);
        id[b[i]].pb(i);
    }

    error = 1<<30;
    dfs(0,0,-1);
    for (int i = 0; i < n; i++)
        if (val[i] == -1){
           dfs1(i,0);
           dfs(i,-temp[i],-1);
        }
            
    for (int i = 0; i < n; i++)
        if (val[a[i]] - val[b[i]] != c[i] || i == error) {
            printf("Impossible after %d statements\n",i+1);
            exit(0);
        }

    printf("Possible\n");
    for (int i = 0; i < n; i++)
        printf("%d\n",val[i]);

    return 0;
}