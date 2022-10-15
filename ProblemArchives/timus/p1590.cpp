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

int *dp1,*dp2;
char s[5100];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	gets(s);
  	int n = strlen(s);
  	dp1 = new int[n],dp2 = new int[n];
  	memset(dp1,0,sizeof(int)*n);
  	memset(dp2,0,sizeof(int)*n);

  	int ans = n * (n+1)/2;
  	
  	for (int i = n-1; i >= 0; i--){
  		for (int j = n-1; j >= 0;--j){
  			if (s[i] != s[j])
  				dp1[j] = 0;
  			else 
  				dp1[j] = 1 + ((j == n-1)?0:dp2[j+1]);
  		}

  		int mv = 0;

  		for (int j = 0; j < i; j++)
  			mv = max(mv,dp1[j]);

  		ans -= mv;

  		swap(dp1,dp2);
  		memset(dp1,0,sizeof(int)*n);  			
  	}

  cout << ans << endl;
  return 0;
}