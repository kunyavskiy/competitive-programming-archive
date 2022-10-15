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

#define taskname "vugluscr"

using namespace std;

typedef long long int64;
typedef long double ld;

int dp[110][110];
char c[110][110];

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif

        int n,m;
        scanf("%d %d",&n,&m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                scanf(" %c ",&c[i][j]);

        memset(dp,255^63,sizeof(dp));
        
        dp[n-1][0] = 0;


        for (int j = 0; j < m; j++)
            for (int i = 0; i < n; i++){
                int sum = dp[i][j];
                for (int k = i; k < n; k++){
                    if (c[k][j] == '*')
                        break;
                    if (c[k][j] != '.')
                        sum += c[k][j] - '0';
                    dp[k][j+1] = max(dp[k][j+1],sum);
                }
                sum = dp[i][j];
                for (int k = i; k >=0; k--){
                    if (c[k][j] == '*')
                        break;
                    if (c[k][j] != '.')
                        sum += c[k][j] - '0';
                    dp[k][j+1] = max(dp[k][j+1],sum);
                }
            }
                                
       cout << dp[n-1][m] << endl;

   	   return 0;
} 