#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

#define taskname "binary"



using namespace std;

typedef long long int64;
typedef long double ld;

char s[2100];
int p[2100];
int next[2100][2];
int dp[2][2100];

const int MOD = 10000;

void ADD(int& a,int b){
    if ((a+=b) >= MOD) a-=MOD;
}

int main(){
    #ifdef LOCAL
        #ifndef taskname
            #error taskname is not defined
        #else
            freopen(taskname".in","r",stdin);
            freopen(taskname".out","w",stdout);
        #endif
    #endif
           
    int n,m;
    scanf("%d %d %s",&m,&n,s);

    p[0] = 0;
    next[0][s[0]-'0'] = 1;
    next[0][(s[0]-'0')^1] = 0;
    for (int i = 1; i < n; i++){
       int j = p[i-1];
       for (;j && s[j] != s[i]; j = p[j-1]);
       if (s[j] == s[i]) 
         j++;
       p[i] = j;
      next[i][s[i]-'0'] = i+1;
      next[i][(s[i]-'0')^1] = next[p[i-1]][(s[i]-'0')^1];
      //cerr << p[i] <<" "<<next[i][0] <<" "<<next[i][1] << endl;
    }


    dp[0][0] = 1;
    for (int i = 0; i < m; i++){
        int id = (i&1);
        memset(dp[id^1],0,sizeof(dp[0]));

        for (int j = 0; j < n; j++){
            ADD(dp[id^1][next[j][0]], dp[id][j]);
            ADD(dp[id^1][next[j][1]], dp[id][j]);
        }

        ADD(dp[id^1][n],dp[id][n]);
        ADD(dp[id^1][n],dp[id][n]);
    }                              


    cout << dp[m&1][n] << endl;

    return 0;
} 