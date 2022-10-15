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

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif


#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

bool check(int a){
	for (int i = 2; i < a; i++)
		if (a % i == 0)
			return false;
    return true;
}

bool prime[1000];

int dp[11000][10][10];

void norm(int& a){
	static const int MOD = 1000000009;
	if ( a >= MOD)
		a -= MOD;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int cnt = 0;

  for (int i = 100; i < 1000; i++){
  	 prime[i] = check(i);
  	 cnt+= prime[i];
  }
                 


  for (int i = 0; i < 10; i++)
  	for (int j = 0; j < 10; j++)
  		dp[2][i][j] = 1;

  int n;
  cin >> n;

  for (int i = 2; i < n; i++)
  	for (int j = 0; j < 10; j++)
  		for (int k = 0; k < 10; k++)
  			for (int l = 1; l < 10; l++)
  				if (prime[100*j+10*k+l]){
  					dp[i+1][k][l] += dp[i][j][k];
  					norm(dp[i+1][k][l]);
  				}


  int ans = 0;

  for (int i = 0; i < 10; i++)
  	for (int j = 0;j < 10; j++){
  		ans += dp[n][i][j];
  		norm(ans);
  	}

  cout << ans << endl;
  		

  return 0;
}