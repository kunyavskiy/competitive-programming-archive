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
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int dp[11000];

int n,s;


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    cin >> n >> s;
    dp[s] = 1;
    int ans = 0;

    for (int i = s; i <= n; i++){
        ans = max(ans,dp[i]);
        if (dp[i])
            for (int j = i+1; j <= n && j <= 2*i; j++){
                if (((j-i)*100) % i == 0)
                    dp[j] = max(dp[j],dp[i]+1);
            }      
    }
    cout << ans << endl;
    return 0;
}