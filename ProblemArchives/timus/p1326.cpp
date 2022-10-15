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

int dp[(1<<20)+10];
int canm[150];
int canc[150];

int minm;

int getmask(){
    int k;
    scanf("%d",&k);
    int ans = 0;
    for (int i = 0; i < k; i++){
        int x;
        scanf("%d",&x);
        --x;
        ans |= 1<<x; 
    }
    return ans;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; i++){
        canm[i] = 1<<i;
        scanf("%d",&canc[i]);
    }
    int m;
    scanf("%d",&m);
    m += n;
    for (int i = n; i < m; i++){
        scanf("%d",&canc[i]);
        canm[i] = getmask();
    }

    minm = getmask();


    memset(dp,63,sizeof(dp));

    dp[0] = 0;

    int ans = 1<<30;

    for (int i = 0; i < (1<<n); i++){
        if ((i & minm) == minm)
            ans = min(ans,dp[i]);

        for (int j = 0; j < m; j++)
            dp[i|canm[j]] = min(dp[i] + canc[j], dp[i|canm[j]]);
    }

    cout << ans << endl;


    return 0;
}