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

int n,k;
int scores[110];

ll dp[13][13][11*110];
int sc[110];

void solve(){
    n = 11;


    for (int i = 0; i < n; i++)
        scanf("%d",&sc[i]);
    scanf("%d",&k);

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= k; j++)
            for (int t = 0; t <= j*101; t++)
                dp[i][j][t] = 0;

    dp[0][0][0] = 1;

    for (int i = 0; i < n; i++){        

        for (int j = 0; j <= k; j++)
            for (int t = 0; t <= j*101; t++){
                dp[i+1][j][t] += dp[i][j][t];
                dp[i+1][j+1][t+sc[i]] += dp[i][j][t];
            }
    }

    for (int i = k*101; i >= 0; i--)
        if (dp[n][k][i]){
            cout << dp[n][k][i] << endl;
            return;
        }   

    cout << 0 << endl;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int t;
  scanf("%d",&t);

  for (; t -- > 0;){
    solve();
  }

  return 0;
}

