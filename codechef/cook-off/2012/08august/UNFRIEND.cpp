// WHAT'S WRONG WITH YOU GUYS??? WTF IS PENTIUM 3??? PLEASE UPGRADE SERVERS! IT'S RIDICULOUS TO TEST SOLUTIONS ON 9-YEAR OLD SYSTEM!"
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
#include <bitset>
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

bitset<250> a[250];
int b[250];

void solve(){
    int n,m;
    scanf("%d %d",&n,&m);

    for (int i = 0; i < m; i++){
        for (int j = 0; j < 250; j++)
            a[i][j] = 0;
        int x,y;
        scanf("%d %d",&x,&y);
        a[i][x-1] = a[i][y-1] = 1;
        b[i] = 1;
    }

    int w;
    scanf("%d",&w);
    for (int i = 0; i < w; i++){
        int k;
        scanf("%d",&k);
        a[k-1][n+k-1] = 1;
    }

    n += m;
                                      

    int cur = 0;

    for (int i = 0; i < n; i++){
    /*{
    cerr << endl << endl;
    for (int i = 0; i < m; cerr<<" "<<b[i]<<endl,i++)
        for (int j = 0; j < n; j++)
            cerr << a[i][j];
    }*/
        if (a[cur][i] == 0){
            for (int j = cur; j < m; j++)
                if (a[j][i]){
                    swap(a[cur],a[j]);
                    swap(b[cur],b[j]);
                    break;
                }
        }
        if (a[cur][i] == 0)
            continue;

        for (int j = 0; j < n; j++){
            if (cur != j && a[j][i])
                a[j] ^= a[cur],b[j] ^= b[cur];                
        }    
        cur++;            
    }

    for (int i = 0; i < n; i++)
        if (!a[i].any() && b[i]){
            printf("NO\n");
            return;
        }
    printf("YES\n");
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

   int t;
   scanf("%d",&t);

   while (t-->0)
    solve();

  return 0;
}