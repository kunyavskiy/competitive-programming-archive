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

int sum[(1<<20)+20];
int dp[(1<<20)+20];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int n;
  scanf("%d",&n);
  for (int i = 0; i < n; i++){
    scanf("%d",&sum[1<<i]);
  }
  for (int i = 0; i < (1<<n); i++)
    sum[i] = sum[i&(i-1)] + sum[i&~(i-1)];

  for (int i = 1; i < (1<<n); i++){
    dp[i] = (1<<29);
    for (int j = 0; j < n; j++){
        int temp = i & ~(1<<j) ;
        temp &= ~(1<<((j+1)%n));
        temp &= ~(1<<((j+2)%n));
        dp[i] = min(dp[i],dp[temp] + sum[temp]);
    }
  }

  cout << dp[(1<<n)-1] << endl;

  return 0;
}