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

int x[4000];
int y[4000];              
vector<int> g[4000];
vector<bool> used[4000];
int n;


inline int dest(int a,int b)
{
	int dx=x[a]-x[b];
	int dy=y[a]-y[b];
	return dx*dx+dy*dy;
}

inline void clear()
{
	for (int i=0;i<n;i++)
		used[i].assign(g[i].size(),false);
}

inline bool good(int v, int first,int second)
{
	int x1=x[v]-x[g[v][first]];
	int y1=y[v]-y[g[v][first]];
	int x2=x[g[v][second]]-x[v];
	int y2=y[g[v][second]]-y[v];
	if (x1*1ll*y2-y1*1ll*x2>0)
		return true;
	if (x1*1ll*y2-y1*1ll*x2<0)
		return false;
	return (x1*1ll*x2>=0) && (y1*1ll*y2>=0);
}

vector<int> ans;

bool dfs(int v,int from,int md,bool write=false)
{
/*	if (md==8)
	{ 
		cerr<<v<<" "<<from<<" "<<md;
		if (from!=-1)
			cerr<<" "<<dest(from,v);
		cerr<<endl;
	}*/
	if (v==0 && from!=-1)
		{
			if (write)
				ans.pb(0);
			return true;
		}
	int r;
	int sz=g[v].size();
	if (from!=-1)
	{
		for (int i=0;i<sz;i++)
			if (g[v][i]==from)
				{
					r=i;
					break;
				}
	}
	bool q=false;
	for (int i=0;i<sz && !q;i++)
		if ((!used[v][i]) && (from==-1 || good(v,r,i)) && (dest(v,g[v][i])>=md))
		{
			used[v][i]=true;
			q|=dfs(g[v][i],v,md,write);

		}
	if (write && q)
		ans.pb(v);
	return q;
}




int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  int m;
  scanf("%d %d",&n,&m);
  for (int i=0;i<n;i++)
  	scanf("%d %d",&x[i],&y[i]);
  for (int i=0;i<m;i++)
  {
  	int a,b;
  	scanf("%d %d",&a,&b);
  	--a,--b;
  	g[a].pb(b);
  	g[b].pb(a);
  }
  int l=0;
  int r=1000000000;
  for (;r-l>1;)
  {
  	//cerr<<l<<" "<<r<<endl;
  	clear();
  	int m=(l+r)/2;
  	if (dfs(0,-1,m))
  		l=m;
  	else
  		r=m;
  }
  clear();
  assert(dfs(0,-1,l,true));
  reverse(ans.begin(),ans.end());
  printf("%d\n",ans.size());
  for (int i=0;i<ans.size();i++)
  	printf("%d ",ans[i]+1);
  printf("\n");
  return 0;
}