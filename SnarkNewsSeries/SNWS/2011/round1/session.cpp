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

#define taskname "session"

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

int t[100];
int p[100];
int n;
int dp[55][55][105];

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
	scanf("%d",&n);
	int m;
	scanf("%d",&m);
	for (int i=1;i<=n;i++)
		scanf("%d %d",&t[i],&p[i]);
	for (int i=0;i<=n;i++)
		for (int j=0;j<=m;j++)
			for (int k=0;k<=100;k++)
				if (i==0 && j==0 && k==0)
					dp[i][j][k]=0;
				else
					dp[i][j][k]=-(1<<29);
	for (int i=0;i<n;i++)
		for (int j=0;j<=m;j++)
			for (int k=0;k<=100;k++){
				int nk=max(k-(t[i+1]-t[i])/2,0);
				dp[i+1][j][nk]=max(dp[i+1][j][nk],dp[i][j][k]+nk*p[i+1]);
				if (j==m) continue;
				dp[i+1][j+1][100]=max(dp[i+1][j+1][100],dp[i][j][k]+p[i+1]*100);
			}
//	cerr<<dp[3][1][100]<<endl;
//	cerr<<dp[4][2][100]<<endl;
	int best=0;
	for (int i=0;i<=100;i++)
		for (int j=0;j<=m;j++){
			best=max(best,dp[n][j][i]);
		}
	printf("%d.%02d",best/100,best%100);	
	return 0;
} 