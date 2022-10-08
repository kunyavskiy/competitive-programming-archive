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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


const int MAXN = 110;

int n,m;
int g0[MAXN][MAXN];
int g[MAXN][MAXN];

int d[MAXN][MAXN];
int s[MAXN];
int t[MAXN];

bool any;

void relax(int x,int y,int v){
    if (d[x][y] > v){
        d[x][y] = v;
        any = true;
    }
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int a,b;
    scanf("%d %d %d %d",&n,&m,&a,&b);
    --a,--b;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            g[i][j] = (1<<29) * (i != j);

    for (int i = 0; i < m; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        --a,--b;
        g0[a][b] = g[a][b] = 1;
    }

    int cnt = 0;
    scanf("%d",&cnt);
    for (int i = 0; i < cnt; i++){
        scanf("%d %d",&s[i],&t[i]);
        --s[i],--t[i];
    }

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                g[i][j] = min(g[i][j],g[i][k] + g[k][j]);

    memset(d,63,sizeof(d));

    /*for (int i = 0; i < n; i++,cerr<<endl)
        for (int j = 0; j < n; j++)
            cerr << g[i][j] <<" ";*/


    d[b][cnt] = 0;

    any = true;

    while (any){
        any = false;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < cnt; j++){
                relax(i,j,d[i][cnt]); 

                if (g[s[j]][t[j]] <= n && g[s[j]][t[j]] == g[s[j]][i] + g[i][t[j]] && j != t[j]){
                    int tmp = 0;
                    for (int k = 0; k < n; k++)
                        if (g0[i][k] && g[i][t[j]] == g[k][t[j]]+1)
                            tmp = max(tmp, d[k][j]);
                    relax(i,j,tmp);
                }
            }

        for (int j = 0; j < cnt; j++)
           for (int i = 0; i < n; i++)
              if (g[s[j]][t[j]] <= n && g[s[j]][t[j]] == g[s[j]][i] + g[i][t[j]] && i != t[j])
                 relax(i, cnt, d[i][j]+1);
    }

    if (d[a][cnt] > 1000000)
        printf("-1\n");
    else
        printf("%d\n",d[a][cnt]);
        
      
    return 0;
}