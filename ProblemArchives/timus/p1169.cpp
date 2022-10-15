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

int dp[101][101*101/2];
int n,m;


void gen(int i,int j){
    //cerr << i <<" "<<j<<endl;
    if (i == 0)
        return;
    int k = dp[i][j];
    i -= k;
    j -= k*(k-1)/2;
    gen(i,j);
    if (i)
        printf("%d %d\n",(i-1)+1,i+1);
    if (k != 1){
        for (int v = i; v < i+k-1; v++)
         printf("%d %d\n",v+1,(v+1)+1);
        printf("%d %d\n",(i+k-1)+1,i +1);
    }
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int n,m;
    scanf("%d %d",&n,&m);
    m = n*(n-1)/2 - m;

    memset(dp,-1,sizeof(dp));

    //cerr << m << endl;

    dp[0][0] = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j <= m; j++)
            if (dp[i][j] != -1) {
                for (int k = 1; k <= n-i && j + k*(k-1)/2 <= m; k++)
                    if (k != 2) 
                       dp[i+k][j+k*(k-1)/2] = k;
             }

     if (dp[n][m] == -1){
        printf("-1\n");
        return 0;
     }

     gen(n,m);

    return 0;
}