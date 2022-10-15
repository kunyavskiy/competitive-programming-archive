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

using namespace std;

typedef long long int64;
typedef long double ld;

const int maxn=160;

int c[maxn][maxn]; 
vector<int> g[maxn];
int spon,part;     
bool used[maxn];
int n;

void gen(int w){
//	memset(f,0,sizeof(f));
	memset(c,0,sizeof(c));
	n=spon+part+2;
	for (int i=1;i<=spon;i++)
		c[0][i]=1;
	for (int i=spon+1;i<=spon+part;i++)
		c[i][n-1]=w;
	for (int i=0;i<part;i++){
		int sz=g[i].size();
		for (int j=0;j<sz;j++)
			c[g[i][j]+1][spon+i+1]=1;
	}
}

int dfs(int v){
	if (v==n-1)
		return 1;
	if (used[v])
		return 0;
	used[v]=true;
	for (int i=0;i<n;i++)
		if (c[v][i]!=0){
			if (dfs(i)==1){
				c[v][i]--;
				c[i][v]++;
				return 1;
			};
		}
	return 0;
}

void flow(){
	memset(used,0,sizeof(used));	
	for (;dfs(0);)
		memset(used,0,sizeof(used));
}

bool check(int w){
	gen(w);
	flow();
	for (int i=0;i<n;i++)
		if (c[0][i])
			return false;
	return true;
}

int main(){
	scanf("%d %d",&spon,&part);
	for (int i=0;i<part;i++){
		int kol=0;
		scanf("%d",&kol);
		g[i].resize(kol);
		for (int j=0;j<kol;j++)
			scanf("%d",&g[i][j]);
	}
	if (!check(10000))
		{
			printf("-1\n");
			return 0;
		}
	int l=0;
	int r=10000;
	for (;r-l>1;){
		int m=(l+r)/2;
		if (check(m))
			r=m;
		else
			l=m;
	}
	cout<<r<<endl;
	return 0;
} 