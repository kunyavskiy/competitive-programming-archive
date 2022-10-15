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

vector<int> g[10010];

int used[10010];
int d[10010];
int s,t,n;

bool dfs(int v){
	if (v==t)
		return true;
	if (used[v]!=0)
		return false;
	used[v]=1;
	int sz=g[v].size();
	for (int i=0;i<sz;i++)
		if (d[g[v][i]]==d[v]+1 && dfs(g[v][i]))
				return true;
	used[v]=2;
	return false;
}

void bfs(){
	setval(d,1);
	d[s]=0;
	queue<int> q;
	q.push(s);
	for (;!q.empty();){
		int fr=q.front();
		q.pop();
		int sz=g[fr].size();
		for (int i=0;i<sz;i++)
		{
			int to=g[fr][i];
			if (d[to]>d[fr]+1)
				{
					d[to]=d[fr]+1;
					q.push(to);
				}
		}
	}
}

bool dfs_1(int v){
	if (v==t)
		return true;
	if (used[v]!=1 && v!=s)
		return false;
	if (used[v]==1)
		printf("%d ",v+1);
	int sz=g[v].size();
	for (int i=0;i<sz;i++)
		if (d[g[v][i]]==d[v]+1 && dfs_1(g[v][i])){
				used[v]=2;
				return true;
			}
	used[v]=2;
	return false;

}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int m;
	scanf("%d %d",&n,&m);
	for (int i=0;i<m;i++){
		int a,b;
		scanf("%d %d",&a,&b);
		--a,--b;
		g[a].pb(b);
		g[b].pb(a);
	}
	n+=2;
	s=n-2;
	t=n-1;
	int n1;
	scanf("%d",&n1);
	for (int i=0;i<n1;i++){
		int a;
		scanf("%d",&a);
		--a;
		g[s].pb(a);
		g[a].pb(s);
	}	
	scanf("%d",&n1);
	for (int i=0;i<n1;i++){
		int a;
		scanf("%d",&a);
		--a;
		g[t].pb(a);
		g[a].pb(t);
	}	
	
	
	bfs();
	int kol=0;
	for (;dfs(s);){
		++kol;
		used[s]=0;
	}
	
	printf("%d %d\n",kol,d[t]-2);
	used[s]=0;
	for (int i=0;i<kol;i++)
		{
			used[s]=0;
			dfs_1(s);
			printf("\n");
		}
  return 0;
}