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


vector<int> g[6100];
int dp[6100][2];
int val[6100];

bool have[6100];


int calc(int a,int b){
	if (dp[a][b] != -1)
		return dp[a][b];
	dp[a][b] = 0;
	for (int i = 0; i < g[a].size(); i++)
		dp[a][b] += calc(g[a][i],1-b);
	dp[a][b] += val[a]*b;
	if (b == 1)
		dp[a][b] = max(dp[a][b],calc(a,0));
//	cerr << a <<" "<<b<<" "<<dp[a][b] << endl;	
	return dp[a][b];	
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int n;
  scanf("%d",&n);
  for (int i = 0; i < n; i++)
  	scanf("%d",&val[i]);

  for (int i = 0; i < n-1; i++){
  	int a,b;
  	scanf("%d %d",&a,&b);
  	--a,--b;
  	g[b].pb(a);
  	have[a] = true;
  }

  memset(dp,-1,sizeof(dp));

  for (int i = 0; i < n; i++){
  	if (!have[i]){
  		cout << calc(i,1) << endl;
  		return 0;
  	}
  }              


  return 0;
}