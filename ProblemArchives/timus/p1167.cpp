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


int dp[510][510], p[510];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int n,k;
  scanf("%d %d",&n,&k);
                       

  for (int i = 0; i < n; i++){
     scanf("%d",&p[i]);
  }
               
  for (int i = 0; i <= n; i++)
     for (int j = 0; j <= k; j++)
        dp[i][j] = 1<<29;
  dp[0][0] = 0;

  for (int i = 0; i < n; i++)
     for (int j = 0; j < k; j++){                     
       int cnt[2];
       cnt[0] = cnt[1] = 0;
       for (int l = i; l < n; l++){
           cnt[p[l]]++;
           dp[l+1][j+1] = min(dp[l+1][j+1],dp[i][j] + cnt[0] * cnt[1]);
       }

     }

  cout << dp[n][k] << endl;
 

    return 0;
}