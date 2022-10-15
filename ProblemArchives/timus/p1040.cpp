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

const int MAXN = 110*110;

vector<pair<int,int> > g[MAXN];

int id[MAXN];

bool ok[MAXN];

int cnt = 1;

void go(int x){
    ok[x] = true;
    for (int i = 0; i < (int)g[x].size(); i++)
        if (id[g[x][i].second] == -1){
            id[g[x][i].second] = cnt++;
            go(g[x][i].first);
            return;
        }
}

int gcd(int x,int y){
    return y?gcd(y,x%y):x;
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
        --a,--b;
        g[a].pb(mp(b,i));
        g[b].pb(mp(a,i));
        id[i] = -1;
    }

               
    while (true){
       bool q = false;

       for (int i = 0; i < n && !q; i++)
          for (int j = 0; j < (int)g[i].size() && !q; j++){
             if ((ok[i] || cnt == 1) && id[g[i][j].second] == -1){
                go(i);
                q = true;
             }
          }
       if (!q) break;            
    }

    printf("YES\n");
    for (int i = 0; i < m; i++)
        printf("%d%c",id[i]," \n"[i==m-1]);         

    return 0;
}