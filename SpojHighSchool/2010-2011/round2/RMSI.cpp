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

const int MAXN=110;

int used[MAXN];
vector<int> g[MAXN][2];
bool G[MAXN][MAXN];
int good[2];
int need[2];
int color;
int n;

void solve(int vert,int kol){
	for (;vert<n && used[vert]!=kol;vert++);
	if (vert==n)
		return;
	if (kol == need[color]-1){
		for (int i=vert;i<n;i++)
			if (used[i] == kol)
				good[color]++;
		return;
	}
	solve(vert+1,kol);
	for (int i=0;i<g[vert][color].size();i++)
		used[g[vert][color][i]]++;
	solve(vert+1,kol+1);		
	for (int i=0;i<g[vert][color].size();i++)
		used[g[vert][color][i]]--;
	return;
}

void init(){
	int m;
	scanf("%d %d %d %d",&n,&need[0],&need[1],&m);
	memset(G,0,sizeof(G));
	for (int i=0;i<m;i++){
		int a,b;
		scanf("%d %d",&a,&b);
		G[a][b]=G[b][a]=1;
	}
	for (int i=0;i<n;i++){
		g[i][0].clear();
		g[i][1].clear();
		for (int j=0;j<n;j++)
			g[i][G[i][j]].pb(j);
	}
	good[0]=good[1]=0;
	color=0;
	solve(0,0);
	color=1;
	solve(0,0);
	printf("The number of blue K(%d) is %d and the number of red K(%d) is %d.\n",need[0],good[0],need[1],good[1]);
}

int main()
{
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int t;
  	scanf("%d",&t);
  	for (int i=1;i<=t;i++){
  		printf("Case #%d:\n",i);
  		init();		
  	}
	return 0;
}