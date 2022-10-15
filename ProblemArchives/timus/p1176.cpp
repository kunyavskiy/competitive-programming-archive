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

int g[1111][1111];
int ptr[1111];
int n,a;        

vector<int> v;

void dfs(int x){
    for (;ptr[x] < n; ptr[x]++){
        if (g[x][ptr[x]] == 0 && ptr[x] != x){
            g[x][ptr[x]] = 1;
            dfs(ptr[x]);
        }
    }
    v.pb(x);
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    scanf("%d %d",&n,&a);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
           scanf("%d",&g[j][i]);
    dfs(a-1);

    for (int i = 0; i+1 < (int)v.size(); i++)
       printf("%d %d\n",v[i]+1,v[i+1]+1); 

    return 0;
}