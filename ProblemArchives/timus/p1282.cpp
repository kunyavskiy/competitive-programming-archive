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
    #undef assert
    #define assert(x) if (!(x)) throw 1
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const int MAXN = 1100;

int res[MAXN];
vector<int> g[MAXN];

void recmin(int);

void recmax(int v){
    if (res[v] != -2)
        return;

    for (int i = 0; i < g[v].size(); i++){
        recmin(g[v][i]);
        res[v] = max(res[v],res[g[v][i]]);
    }
}

void recmin(int v){
    if (res[v] != -2)
        return;

    res[v] = 2;

    for (int i = 0; i < g[v].size(); i++){
        recmax(g[v][i]);
        res[v] = min(res[v],res[g[v][i]]);
    }
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int n;
    scanf("%d",&n);
    res[0] = -2;
    for (int i = 1; i < n; i++){
         char c;
         scanf(" %c ",&c);
         if (c == 'N'){
            int p;
            res[i] = -2;
            scanf("%d",&p);          
            g[p-1].pb(i);
         }
         else {
            int p;
            scanf("%d %d",&p,&res[i]);
            g[p-1].pb(i);
         }
    }

    recmax(0);
    if (res[0] == 1)
        printf("+");
    printf("%d",res[0]); 
    return 0;
}