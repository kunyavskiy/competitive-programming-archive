#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>
#define mp make_pair
#define pb push_back

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "D"

typedef long long ll;
typedef long double ld;

const int MOD = 1000000007;

void ADD(int& a,int b){
	if ((a += b) >= MOD) a -= MOD;
}

int MULT(int a,int b){
	return (a * 1LL * b) % MOD;
}



int dp1[155][155];
int dp1s[155][155];
int dp2[155][155][155];



int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);            
  #endif

    int n;
    scanf("%d %d",&n,&m);

    int N = max(n,m);

    dp1[1][0] = 1;
    for (int i = 1; i <= N; i++)
    	for (int j = 0; j <= N; j++)
    		for (int k = j; k <= N; k++)
    			ADD(dp1[i+1][k], dp1[i][j]);

    dp1s[1][0] = 1;
    for (int i = 1; i <= N; i++)
    	for (int j = 0; j <= N; j++)
    		for (int k = j+1; k <= N; k++)
    			ADD(dp1s[i+1][k], dp1s[i][j]);




    for (int i = N; i >= 1; i--)
    	for (int j = N; j >= 1; j--)
    		for (int k = 1; k <= N; k++) {
    			dp2[i][j][k] = dp2[i][j+1][k];
    			ADD(dp2[i][j][k], dp2[
    		}
    			
      
    return 0;
}