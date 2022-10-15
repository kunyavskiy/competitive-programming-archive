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

int dp[901][8101];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    memset(dp,63,sizeof(dp));
    dp[0][0] = 0;
    
    for (int i = 0; i < 900; i++)
        for (int j = 0; j < 8100; j++)
            for (int k = 1; k < 10; k++){
                if (i + k <= 900 && j+k*k <= 8100)
                    dp[i+k][j+k*k] = min(dp[i+k][j+k*k], dp[i][j]+1);
            }
    int t;
    scanf("%d",&t);

    while (t-->0){
        int a,b;
        scanf("%d %d",&a,&b);
        if (a > 900 || b > 8100 || dp[a][b] > 100){
            printf("No solution\n");
            continue;
        }
        for (int k = 1; k < 10 && a; k++)
           if (dp[a-k][b-k*k] + 1 == dp[a][b]){
             printf("%d",k);
             a -= k;
             b -= k*k;
             k--;
           } 
       printf("\n");           
    } 

    return 0;
}