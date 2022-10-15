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

const int nmax=30000;

int p[nmax];
int as[nmax];
int n;

int root(int v)
{
	if (p[v]==v)
		return v;
	return p[v]=root(p[v]);
}

bool uni(int v1,int v2)
{
	v1=root(v1);
	v2=root(v2);
	if (v1==v2)
		return false;
	if (rand()&1)
		{
			as[v1]=v1;
			p[v2]=v1;
		}
 	else
 		{
 			as[v2]=v1;
 			p[v1]=v2;
 		}
 	return true;
}

void init()
{
	for (int i=0;i<n;i++)
		p[i]=i;  
}

vector<int> g[2][nmax];
vector<int> ans[nmax];
vector<int> obr[2][nmax];
int kol[nmax];
vector<int> tree[2][nmax];
vector<int> obrtree[2][nmax];
vector<int> number[2][nmax];
vector<int> treenumber[2][nmax];

bool build_tree()
{
	init();
	int kol[2];
	kol[0]=kol[1]=0;
	for (int r=0;r<2;r++)
		for (int i=0;i<n;i++)
			{
				int sz=g[r][i].size();
				for (int j=0;j<sz;j++)
					if (uni(i,g[r][i][j]))
					{
						int to=g[r][i][j];                     
						obrtree[r][i].pb(tree[r][to].size());
						obrtree[r][to].pb(tree[r][i].size());
						tree[r][i].pb(to);
						tree[r][to].pb(i);
						treenumber[r][i].pb(number[r][i][j]);
						treenumber[r][to].pb(number[r][i][j]);                    
						kol[r]++;
					}
			}
	if (kol[0]+kol[1]!=n-1)
	{
		printf("-1\n");
		exit(0);
	}
	return ((kol[1]%2)==0);
}

void print_ans()
{
	for (int i=0;i<n;i++)
		for (int r=0;r<2;r++)
		{
		  int sz=tree[r][i].size();
		  for (int j=0;j<sz;j++)
		 	 if (tree[r][i][j]<i)
		  		printf("%d ",treenumber[r][i][j]);
		}
  printf("\n");
  exit(0);
}



bool used[nmax];

void dfs(int v,int k=0)
{
	used[v]=true;
	as[v]=v;
	kol[v]=k;
	int sz=g[1][v].size();
	for (int i=0;i<sz;i++)
		ans[v][i]=ans[g[1][v][i]][obr[1][v][i]]=as[root(g[1][v][i])];
	for (int r=0;r<2;r++)
	{
		int sz=tree[r][v].size();
		for (int i=0;i<sz;i++)
		{
			int to=tree[r][v][i];
			if (!used[to])
			{
				dfs(to,k+(1-r));
				uni(v,to);
			}
		}
	}
}

int deleted;

bool delete_reb(int v,int b,bool q)
{
	if (v==b)
		return true;
	used[v]=true;
	int sz=tree[0][v].size();
	for (int i=0;i<sz;i++)
	{
		int to=tree[0][v][i];
		if (!used[to])
			if (delete_reb(to,b,true))
				{
					if (!q)
					{
						swap(tree[0][v][i],tree[0][v][tree[0][v].size()-1]);
						tree[0][v].pop_back();
						int obr=obrtree[0][v][i];
						swap(tree[0][to][obr],tree[0][to][tree[0][to].size()-1]);
						tree[0][to].pop_back();

						swap(treenumber[0][v][i],treenumber[0][v][treenumber[0][v].size()-1]);
						treenumber[0][v].pop_back();
						swap(treenumber[0][to][obr],treenumber[0][to][treenumber[0][to].size()-1]);
						treenumber[0][to].pop_back();

					}
					return true;
				}
	}
	sz=tree[1][v].size();
	for (int i=0;i<sz;i++)
	{
		int to=tree[1][v][i];
		if (!used[to])
			if (delete_reb(to,b,q))
					return true;
	}
	return false;
}


bool correct_tree()
{
  init();
  for (int i=0;i<n;i++)
  	ans[i].resize(g[1][i].size());
  setval(used,0);	
  dfs(0); 
  for (int i=0;i<n;i++)
  	{
  		int sz=g[1][i].size();
  		for (int j=0;j<sz;j++)
			{
				int to=g[1][i][j];
				int lca=ans[i][j];
				if (kol[i]+kol[to]-kol[lca]*2>0)
				{
					setval(used,0);
					delete_reb(i,to,false);
					tree[1][i].pb(to);
					tree[1][to].pb(i);
					treenumber[1][i].pb(number[1][i][j]);
					treenumber[1][to].pb(number[1][i][j]);
					return true;
				}
			}
  	}
  return false;
}


int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  int m;
  scanf("%d %d",&n,&m);
  for (int i=0;i<m;i++)
  {
  	int a,b,c;  
  	scanf("%d %d %d",&a,&b,&c);               
  	--a,--b,--c;
   	obr[c][a].pb(g[c][b].size());
  	obr[c][b].pb(g[c][a].size());
   	g[c][a].pb(b);
  	g[c][b].pb(a);      
  	number[c][a].pb(i+1);
  	number[c][b].pb(i+1);

  }                                     
  if (build_tree())
  	print_ans();
 	if (correct_tree())
		print_ans();
  printf("-1\n");
  return 0;
}