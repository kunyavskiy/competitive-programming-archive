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
#define int64 long long
#define ld long double  
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

vector<int> g[100];
vector<int> bg[100];
vector<int> gcomp[100];
int compcnt;
int comp[100];
int n;

void error(bool q){
	if (q) return;
	printf("0\n");
	exit(0);
}

void dfs(int v,int c){
	if (comp[v]!=-1) return;
	comp[v]=c;
	for (int i=0;i<g[v].size();i++)
		dfs(g[v][i],c);
}

int used[100];

void dfscomp(int v,int c){
	if (v==0) return;
	error(used[v]==0 || used[v]==c);
	if (used[v]==c) return;
	used[v]=c;
	for (int i=0;i<gcomp[v].size();i++)
		dfscomp(gcomp[v][i],3-c);		
}


int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d",&n);
	++n;
	for (int i=1;i<n;i++){
		int z;
		scanf("%d",&z);
		for (int j=0;j<z;j++){
			error(i+j<n);
			g[i+j].pb(j);
			g[j].pb(i+j);
		}
		if (i+z<n){
			bg[i+z].pb(z);
			bg[z].pb(i+z);
		}
	}
	memset(comp,-1,sizeof(comp));
	for (int i=0;i<n;i++)
		if (comp[i]==-1)
			dfs(i,compcnt++);
	for (int i=0;i<n;i++){
		for (int j=0;j<bg[i].size();j++){
			error(comp[i]!=comp[bg[i][j]]);
			gcomp[comp[i]].pb(comp[bg[i][j]]);
		}
	}
	

	for (int i=0;i<compcnt;i++){
		sort(gcomp[i].begin(),gcomp[i].end());
		gcomp[i].erase(unique(gcomp[i].begin(),gcomp[i].end()),gcomp[i].end());
		if (i==0)
			assert(gcomp[i].size()==compcnt-1);
		else
			assert(gcomp[i].size()>0 && gcomp[i][0]==0);
	}
	int64 res=3;
	for (int i=1;i<compcnt;i++)
		if (!used[i]){
			dfscomp(i,1);
			res*=2;
		}
	cout<<res<<endl;
	return 0;
}