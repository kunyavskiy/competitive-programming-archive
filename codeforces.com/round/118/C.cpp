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

int dp[55][55][55];

int a[55][55];
int w[55];

int n;

int calc(int line,int l,int r){ 
    if (dp[line][l][r] != -1)
        return dp[len][l][r];
    if (line == 0){
        for (int i = l; i < r; i++)
            if (w[i] < a[0][i])
                return false;
        return true;
    }

    int l1 = l;
    while (l1 < r && a[line-1][l1] >= a[line][l1])
        l1++;


    int r1 = r-1;
    while (r1 > l && a[line-1][r1] >= a[line][r1])
        r1--;

    dp[line][l][r] = 0;

    if (l1 >= r)
        dp[line][l][r] |= calc(line-1,l,r);
    if (r1 <= l)
        dp[line][l][r] |= calc(line-1,l+1,r+1);
    if (l1 >= r1 && )

        


}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    memset(dp,-1,sizeof(dp));

    scanf("%d",&n);

    for (int i = 0; i < n; i++){
        scanf("%d",&w[i]);
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n-i; j++)
            scanf("%d",&a[i][j]);

    int q = calc(n-1,0,1);

    if (q)
        printf("Cerealguy\n");
    else
        printf("Fat Rat\n");
    return 0;
}

