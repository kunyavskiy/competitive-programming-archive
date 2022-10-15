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

pair<pair<int,int>,int> a[2100];

int dp[50];
int n;

void solve(){
    memset(dp,0,sizeof(dp));
    
    scanf("%d",&n);
    for (int i = 0; i < n; i++)
        scanf("%d %d %d",&a[i].first.first,&a[i].first.second,&a[i].second);
    sort(a,a+n);

    for (int i = 0; i < n; i++){
        for (int j = a[i].first.second; j <= 48; j++)
            dp[j] = max(dp[j], dp[a[i].first.first] + a[i].second);
    }

    cout << dp[48] << endl;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int t;
  scanf("%d",&t);

  while (t--)
    solve();

  return 0;
}