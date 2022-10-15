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
int used[1100];

int dfs(int v){
    if (used[v])
        return 0;
    used[v] = 1;
    int res = 0;
    for (int i = 0; i < (int)g[v].size(); i++)
        res += dfs(g[v][i]) + (used[g[v][i]] != 1);    
    used[v] = 2;
    return res;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    for (int a,b; scanf("%d %d",&a,&b) == 2;){
        --a,--b;
        g[a].pb(b);
        g[b].pb(a);
    }

    for (int i = 0; i < 1100; i++){
        int t = dfs(i);
//        if (t) cerr << t;
        if (t % 2 == 1){
            printf("0\n");
            return 0;
        }
    }

    printf("1\n");
    return 0;
}