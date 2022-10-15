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

int dp1[2100][2100];
int dp2[2100][2100];

void relax(int x,int y,int x1,int y1){
    if (dp1[x1][y1] > dp1[x][y] + 1){
        dp1[x1][y1] = dp1[x][y] + 1;
        dp2[x1][y1] = 0;
    }
    if (dp1[x1][y1] == dp1[x][y] + 1)
        dp2[x1][y1] = (dp2[x1][y1] + dp2[x][y])%1000000007;
}


char s[2100];
char t[2100];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    memset(dp1,63,sizeof(dp1));

    dp1[0][0] = 0;
    dp2[0][0] = 1;

    gets(s);
    gets(t);

    int n = strlen(s);
    int m = strlen(t);

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++){
            if (s[i] == t[j])
                relax(i,j,i+1,j+1);
            else {
                relax(i,j,i+1,j);
                relax(i,j,i,j+1);
            }
        }

    cout << dp2[n][m] << endl;

    return 0;
}