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

ll dp[20][2];

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int n,k;
  cin >>n  >> k;

  dp[0][0] = 1;
  dp[0][1] = 0;
  for (int i = 1; i <= n; i++){
  	dp[i][0] = (dp[i-1][0] + dp[i-1][1])*(k-1);
  	dp[i][1] = dp[i-1][0];
  }

  cout << dp[n][0] << endl;
  return 0;
}