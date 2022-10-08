//#include <iostream>
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
#include <sstream>
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

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "E"

typedef long long ll;
typedef long double ld;

const int MAXN = 110;

int c[MAXN][MAXN];
int x[MAXN][MAXN];
int x2[MAXN][MAXN][MAXN];

int sum(int x,int y){
	return min(101,x+y);
}

int dp[MAXN][MAXN][MAXN];

const int MOD = 1000000007;

void add(int& x,int y){
	if ((x += y) >= MOD) x -= MOD;
}


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif        

  	for (int i = 0; i < MAXN; i++)
  		for (int j = 0; j < MAXN; j++)
	  		x2[0][i][j] = 1;

	c[0][0] = 1;
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXN; j++){
			if (i) c[i][j] = sum(c[i][j],c[i-1][j]);
			if (i && j) c[i][j] = sum(c[i][j], c[i-1][j-1]);
		}

  	for (int i = 1; i < MAXN; i++)
  		for (int j = 0; j < MAXN; j++)
  			for (int k = 1; k < MAXN; k++)
  				for (int cnt = 0; k * cnt <= i && cnt <= j; cnt++)
  					x2[i][j][k] = sum(x2[i][j][k], x2[i-k*cnt][j - cnt][k-1] * c[j][cnt]);


  	for (int i = 1; i < MAXN; i++)
  		for (int j = 1; j < MAXN; j++)
  			for (int k = 0; k <= i; k++)
  				x[i][j] = x2[i][j][i];

	dp[0][1][1] = 1;
	                
	for (int i = 0; i < MAXN; i++)
		for (int j = 1; j < MAXN; j++)
			for (int k = 1; k < MAXN; k++)
				for (int cnt = 1; i + 2 * cnt < MAXN; cnt++){
					if (dp[i][j][k] == 0) continue;        
					int nk = k * x[cnt][j];
					//eprintf("%d %d %d -> %d %d %d\n",i,j,k,i+2*cnt,cnt,nk);
					if (nk >= MAXN) break;
					add(dp[i + 2 * cnt][cnt][nk],dp[i][j][k]);					
				}

	int n,m,k;
	scanf("%d %d %d",&n,&m,&k);


	int ans = 0;

	for (int r = 1; r <= n; r++)
		for (int j = 0; j < m; j++)
			for (int cnt = 1; cnt <= k; cnt++){
				add(ans, (dp[r][j][cnt] * 1LL * (m - j)) % MOD);
			}

	printf("%d\n",ans);
			
      
    TIMESTAMP(end);
    return 0;
}