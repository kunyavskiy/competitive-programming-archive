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

int ans[1<<20];

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int sum = 0;
  int n;
  cin >> n;
  for (int i = 0; i < n; i++){
  	cin >> ans[1<<i];
  	sum += ans[1<<i];
  }
  int res = sum;
  for (int i = 0; i < (1<<n); i++){
  	ans[i] = ans[i&(i-1)] + ans[i&~(i-1)];
  	res = min(res,abs(ans[i] - (sum - ans[i])));
  }
  cout << res << endl;
  

  return 0;
}