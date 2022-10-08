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

pair<int,int> dp[110000];
int prev[110000];
int a[110000];


bool cmp(const pair<int,int>& a,const pair<int,int>& b){
    return a.first*log(2.0)+a.second*log(3.0) < b.first*log(2.0)+b.second*log(3.0) + (1e-9);
}

vector<int> ans;

void print(int v){
    if (v == 0)
        return;
    print(prev[v]);
    ans.pb(v);
}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int n;
  scanf("%d",&n);

  for (int i = 0; i < n; i++)
     scanf("%d",&a[i]);

  for (int i = 0; i < n; i++)
    dp[i] = mp(-1,-1);

  dp[0] = mp(0,0);
  
  for (int i = 0; i < n; i++){
    if (cmp(dp[i+1],dp[i])){
        dp[i+1] = dp[i];
        prev[i+1] = i;
    }

    if (i < n-1 && cmp(dp[i+2],mp(dp[i].first+1,dp[i].second))){
        dp[i+2] = mp(dp[i].first +1,dp[i].second);
        prev[i+2] = i;
    }

    if (i < n-2 && ((a[i] >= a[i+1] && a[i+1] >= a[i+2]) || (a[i] <= a[i+1] && a[i+1] <= a[i+2])))
        if (cmp(dp[i+3],mp(dp[i].first,dp[i].second+1))){
            dp[i+3] = mp(dp[i].first,dp[i].second+1);
            prev[i+3] = i;
        }      
  }

  print(n);

  printf("%d\n",ans.size());
  for (int i = 0; i < (int)ans.size(); i++)
    printf("%d ",ans[i]);

  return 0;
}