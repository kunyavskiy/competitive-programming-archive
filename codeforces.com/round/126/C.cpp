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

int a[110000]; 
ll dps[110000][2];
ll dpp[110000][2];
int n;


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
  #endif

  scanf("%d",&n);
  --n;
  for (int i = 1; i <= n; i++)
    scanf("%d",&a[i]);

  dpp[0][0] = dpp[0][1] = 0;
  for (int i = 1; i <= n; i++){
    dpp[i][0] = max(dpp[i-1][0]+a[i] - (a[i]%2 == 0),dpp[i-1][1]+a[i]);
    dpp[i][1] = dpp[i-1][1] + a[i] - (a[i] % 2);
    if (a[i] == 1)
        dpp[i][1] = 0;
  }

  reverse(a+1,a+n+1);


  dps[0][0] = dps[0][1] = 0;
  for (int i = 1; i <= n; i++){
    dps[i][0] = max(dps[i-1][0]+ a[i] - (a[i] % 2 == 0),dps[i-1][1]+a[i]);
    dps[i][1] = dps[i-1][1] + a[i] - (a[i] % 2);
    if (a[i] == 1)
        dpp[i][1] = 0;
  }

  ll ans = 0;
  for (int i = 0; i <= n; i++){
      ans = max(ans, dpp[i][0]);
      ans = max(ans, dps[n-i][0]);
      ans = max(ans, dpp[i][1] + dps[n-i][0]);
      ans = max(ans, dpp[i][0] + dps[n-i][1]);
      cerr << i <<" "<<dpp[i][0] << endl;
      cerr << i <<" "<<dps[n-i][0] << endl;
      cerr << i <<" "<<dpp[i][1] + dps[n-i][0] << endl;
      cerr << i <<" "<<dpp[i][0] + dps[n-i][0] << endl;
  }

  cout << ans << endl;


      
  return 0;
}