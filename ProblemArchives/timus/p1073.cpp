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
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int dp[110000];
int n;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    scanf("%d",&n);

    memset(dp,1,sizeof(dp));
    dp[0] = 0;

    for (int i = 0; i < n; i++){
    	for (int j = 1; i+j*j <= n; j++)
    		dp[i+j*j] = min(dp[i+j*j],dp[i]+1);
    	if (dp[i] == 4)
    		cout << i << endl;
    }

    cout << dp[n] << endl;
  return 0;
}