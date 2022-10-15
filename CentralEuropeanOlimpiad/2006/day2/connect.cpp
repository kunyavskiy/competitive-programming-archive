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

typedef long long int64;
typedef long double ld;

short dp[42][14][(1<<13)+100];
short par[42][14][(1<<13)+100];


char s[40][100];
int n,m;

void update(int i,int j,int k,int i1,int j1,int k1,int val){
	if (dp[i][j][k] > val){
		dp[i][j][k] = val;
		par[i][j][k] = k1;
	}
}


void go(int y,int x,int mask){
	if (dp[y][x][mask] > 20000)
		return;
	if (x == n/2 + 1){
		int nmask = (mask << 1) & ((1<<(n/2+1))-1);
		update(y+1,0,nmask,y,x,mask,dp[y][x][mask]);
		return;
	}
	int b1 = mask & (1<<x);b1 = !!b1;
	int b2 = mask & (1<<(x+1));b2 = !!b2;
	for (int b3 = 0;b3 < 2;b3 ++)
		if (b3 == 0 || s[2*x+1][2*y+2] == ' ')
			for (int b4 = 0;b4 < 2;b4 ++)
				if (b4 == 0 || s[2*x+2][2*y+1] == ' '){
					int cnt = b1+b2+b3+b4;
					if (s[2*x+1][2*y+1] == 'X' && cnt != 1)
						continue;
					if (s[2*x+1][2*y+1] != 'X' && cnt != 2 && cnt != 0)
						continue;
					int nmask = (mask & ~(1<<x) & ~(1<<(x+1))) | (b3 << x) | (b4 << (x+1));
					update(y,x+1,nmask,y,x,mask,dp[y][x][mask] + b3 + b4 + (cnt == 2));
				}			
}


void gen(int y,int x,int mask,int omask){

	if (y == -1)
		return;
	if (x == -1){
		gen(y-1,n/2+1,mask,omask);	
		return;
	}
	else
		gen(y,x-1,par[y][x][mask],mask);
		
	if (x == n/2+1)
		return;	
		
		
	
	int b3 = omask & (1<<x);b3 = !!b3;
	int b4 = omask & (1<<(x+1));b4 = !!b4;
	if (b3) s[2*x+1][2*y+2] = '.';
	if (b4) s[2*x+2][2*y+1] = '.';
	int b1 = mask & (1<<x);b1 = !!b1;
	int b2 = mask & (1<<(x+1));b2 = !!b2;
	if (b1 +b2 + b3 + b4 == 2)
		s[2*x+1][2*y+1] = '.';
		
	/*cerr << x << " "<<y << " "<<mask << endl;
	for (int i=0;i<n;i++){
		fputs(s[i],stderr);		
		cerr << endl;
	}
		
	cerr << endl << endl;*/
		

		
	return;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	//cerr << (sizeof(dp) + sizeof(par))/1024.0/1024 <<endl;
	gets(s[0]);
	sscanf(s[0],"%d %d",&n,&m);		
	for (int i=0;i<n;i++)
		gets(s[i]);
	memset(dp,127,sizeof(dp));
	int MAXMASK = 1<<((n/2)+1);
	int MAXI = n/2+1;
	int MAXJ = m/2;
	dp[0][0][0] = 0;
	for (int j=0;j<=MAXJ;j++)
		for (int i=0;i<=MAXI;i++)
			for (int mask=0;mask < MAXMASK;++mask)
				go(j,i,mask);
	
	int cnt = 0;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			cnt += (s[i][j] == 'X');
	
	cout << dp[MAXJ+1][0][0] + cnt/2  << endl;		
	gen(MAXJ+1,0,0,0);
	for (int i=0;i<n;i++)
		puts(s[i]);		
	return 0;
}