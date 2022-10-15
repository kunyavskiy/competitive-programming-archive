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

int dp[110][110][10][2][2];

int a[110][110];
int n,m;
int p;

int get(int x,int y,int v,int c){
	return (a[x][y]+(v+c)*p)%10;
}

int go(int x,int y,int z,int a,int b){
	int& ans = dp[x][y][z][a][b];
	if (ans != -1)
		return ans;
	ans = 0;                   
	if (x != n-1){
		if (z >= get(x+1,y,0,b))
			ans = max(ans,go(x+1,y,get(x+1,y,0,b),0,b)+1);
		if (z >= get(x+1,y,1,b))           
			ans = max(ans,go(x+1,y,get(x+1,y,1,b),1,b)+1);
		ans = max(ans,go(x+1,y,z,0,b)); 
		ans = max(ans,go(x+1,y,z,1,b));        
	}

	if (y != m-1){
		if (z >= get(x,y+1,a,0))
			ans = max(ans,go(x,y+1,get(x,y+1,a,0),a,0)+1);
		if (z >= get(x,y+1,a,1))
			ans = max(ans,go(x,y+1,get(x,y+1,a,1),a,1)+1);
		ans = max(ans,go(x,y+1,z,a,0)); 
		ans = max(ans,go(x,y+1,z,a,1));        

	}
	return ans;
}


void solve(){
	scanf("%d %d",&n,&m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++){
			char c;
			scanf(" %c",&c);
			a[i][j] = c - '0';
		}

	int ans = 0;

	for (p=1;p<10;p++){
	   memset(dp,-1,sizeof(dp));
	   for (int i = 0; i < 2; i++)
	   	for (int j = 0; j < 2; j++){
	   		ans = max(ans, go(0,0,9,i,j));
	   		ans = max(ans, go(0,0,get(0,0,i,j),i,j)+1);
	   	}
	}

	cout << ans << endl;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int t;
    scanf("%d",&t);
    while (t-- > 0)
    	solve();

  return 0;
}