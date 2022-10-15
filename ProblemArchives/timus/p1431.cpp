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
    #undef assert
    #define assert(x) if (!(x)) throw 1
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int dp[(1<<18)+10];

int a[18];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    
    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; i++)
        scanf("%d",&a[i]);

    for (int i = 1; i < (1<<n); i++){
        int j = 0;
        while (!(i &(1<<j)))
            j++;

        dp[i] = dp[i ^ (1<<j)] + 1;

        for (int k = j+1; k < n; k++)
            if ((i & (1<<k)) && (abs(a[j] - a[k]) == 1))
                dp[i] = min(dp[i], dp[i ^ (1<<j) ^ (1<<k)]+1);                 
    }

    cout << dp[(1<<n)-1] << endl;
    return 0;
}