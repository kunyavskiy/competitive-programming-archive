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

bool used[100000];
int color[200000];
vector<int> g[100000];
vector<int> c[100000];
vector<int> way[100000];
vector<bool> ex[100000];
int p[100000];
int pnum[100000];
int n,m;


void dfs(int v,int par,int parnum){
	if (used[v])
		return;
	used[v]=true;
	p[v]=par;
	pnum[v]=parnum;
	int sz=g[v].size();
	for (int i=0;i<sz;i++)
		if (g[v][i]!=par)
			dfs(g[v][i],v,i);
		else
			swap(g[v][i],g[v][0]);
	for (int i=1;i<sz;i++)
		pnum[g[v][i]]=i;
	return;
}


void dfs(int v,const vector<int>* g,vector<int> &tr){
	if (used[v])
		return;
	used[v]=true;
	int sz=g[v].size();
	for (int i=0;i<sz;i++)
		dfs(g[v][i],g,tr);
	tr.pb(v);
	return;
}

void dfs(int v,const vector<int>* g,int c){
	if (color[v]!=0 && color[v]!=c)
		{			
			printf("NO\n");
			exit(0);
		}
	if (used[v])
		return;
	color[v]=c;
	used[v]=true;
	int sz=g[v].size();
	for (int i=0;i<sz;i++)
		dfs(g[v][i],g,c);
	return;
}

void  topsort(const vector<int>* g,vector<int>& tr){
	setval(used,false);
	for (int i=0;i<n;i++)
		dfs(i,g,tr);
	return;
}

vector<int> ng[200000];

void mark_graf(){
	for (int i=0;i<m;i++){
		int sz=way[i].size();
		for (int j=0;j<sz-1;j++){
			int a=way[i][j];
			int b=way[i][j+1];
			int coef=0;
			if (p[a]==b)
			{
				swap(a,b);
				coef=1;
			}
			if (c[b][0]==-1){
				c[b][0]=2*i+1-coef;
				c[a][pnum[b]]=2*i+coef;												
				continue;
			}
			ng[2*i+1-coef].pb(c[b][0]);
			ng[2*i+coef].pb(c[a][pnum[b]]);
			ng[c[b][0]].pb(2*i+1-coef);
			ng[c[a][pnum[b]]].pb(2*i+coef);
		}
	}
	setval(used,false);
	setval(color,0);
	for (int i=0;i<2*m;i++){
		if (color[i]==0 && color[i^1]==0){
			dfs(i,ng,1);
			dfs(i^1,ng,2);			
			continue;
		}                  
		dfs(i^1,ng,3-color[i]);
	}
	for (int i=0;i<m;i++)
	{
		if (color[2*i+1]==1)
			reverse(way[i].begin(),way[i].end());
	}
	for (int i=0;i<m;i++){	
		int sz=way[i].size();
		for (int j=0;j<sz-1;j++)
		{
			int a=way[i][j];
			int b=way[i][j+1];
			if (p[b]==a)
				ex[b][0]=0;
			else
				ex[b][pnum[a]]=0;	
		}
	}
}

void  del_graf(){
	for (int i=0;i<n;i++)
		{
			int sz=g[i].size();
			for (int j=0;j<sz;j++)
				if (!ex[i][j]){
					swap(g[i][j],g[i][sz-1]);
					g[i].pop_back();
					bool tmp=ex[i][j];
					ex[i][j]=ex[i][sz-1];
					ex[i][sz-1]=tmp;
					--j;
					--sz;	
				}
		}
}

int main()
{
  freopen("rail.in","r",stdin);
  freopen("rail.out","w",stdout);
  scanf("%d %d",&n,&m);
  for (int i=0;i<m;i++){
  	int a,b;
  	scanf("%d %d",&a,&b);
  	--a,--b;
  	g[a].pb(b);
  	g[b].pb(a);
  	c[a].pb(-1);
  	c[b].pb(-1);
  	ex[a].pb(true);
  	ex[b].pb(true);
  }
 	setval(used,false);
 	for (int i=0;i<n;i++)
 		dfs(i,-1,-1);
 	scanf("%d",&m);
 	for (int i=0;i<m;i++)
 		{
 			int a;
 			for (scanf("%d",&a);a!=0;scanf("%d",&a))
 			{
 				--a;
 				way[i].pb(a);
 			}
 		}
 	mark_graf();
 	del_graf();
 	vector<int> tr;
 	topsort(g,tr);
 	for (int i=0;i<n;i++)
 	{
 		color[tr[i]]=i+1;
 	}
 	printf("YES\n");
 	for (int i=0;i<n;i++)
 		printf("%d ",color[i]);
 	return 0;
}