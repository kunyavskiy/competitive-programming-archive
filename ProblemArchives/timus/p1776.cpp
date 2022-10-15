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

double dp[410][410];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int n;
    cin >> n;
    n -= 2;

    for (int i = 0; i <= n; i++)
       dp[0][i] = 1.0;

    for (int i = 1; i <= n; i++)
        for (int k = 1; k <= n; k++){
            for (int j = 0; j < i; j++)
                dp[i][k] += dp[j][k-1]*dp[i-j-1][k-1]; 
            dp[i][k] /= i;
            //cerr << i <<" "<<k<<" "<<dp[i][k] << endl;
        }


    ld ans = 0;
    for (int i = 1; i <= n; i++)
        ans += (dp[n][i]-dp[n][i-1]) * i * 10;


    cout.precision(15);
    cout << fixed << ans << endl;

    return 0;
}