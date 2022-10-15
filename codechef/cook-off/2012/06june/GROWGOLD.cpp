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

const int MOD = 100000007;
const int MODFI = MOD - 1;

#ifdef LOCAL
    ld START = clock();
#endif

int val[110];

int a[110][110];
int b[110][110];
ll temp[110][110];
int n;

int pow(int a,int b){
    if (b == 0)
        return 1;
    if (b & 1)
        return (pow(a,b-1)*1LL*a)%MOD;
    int temp = pow(a, b/2);
    return (temp * 1LL * temp) % MOD;
}


void mult(int a[][110],int b[][110]){
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            temp[i][j] = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                temp[i][j] = temp[i][j] + a[i][k] * 1LL * b[k][j];
}

void solve(){
   int s1,s2,m;
   scanf("%d %d %d",&val[0],&s1,&s2);
   for (int i = 1; i <= s1; i++)
      val[i] = (val[i-1] + 1)%MOD;
   for (int i = s1+1; i <= s1+s2; i++)
      val[i] = (val[i-1] * 2)%MOD;



   scanf("%d %d",&n,&m);
   --m;
   if (m <= s1 + s2){
     printf("%d\n",val[m]);
     return;
   }
   m -= s1+s2;

   memset(b,0,sizeof(b));
   memset(a,0,sizeof(a));
   for (int i = 0; i < n; i++)
      b[0][i] = a[i][i] = 1;
   for (int i = 1; i < n; i++)
      b[i][i-1] = 1;



   for (int i = 0; i <= 30; i++){
      if (m & (1<<i)){
          mult(a,b);
          for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                a[i][j] = temp[i][j] % MODFI;
      }
      mult(b,b);
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          b[i][j] = temp[i][j] % MODFI;
   }

   int ans = 1;

   for (int j = 0; j < n; j++){
     assert(a[0][j] >= 0);
     ans = (ans * 1LL * pow(val[s1+s2-j], a[0][j])) % MOD;
   }    

   printf("%d\n",ans%MOD);
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

    #ifdef LOCAL
        cerr << (clock()-START)/CLOCKS_PER_SEC << endl;
    #endif

  return 0;
}