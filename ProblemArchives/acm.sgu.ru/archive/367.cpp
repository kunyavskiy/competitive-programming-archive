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

vector<int> g[3500];
int ts[3500];
int n;
int tn;
pair<int,int> ans[3500];
const int inf=1<<30;
bool used[3500];

bool topsort(int v)
{
//	cerr<<v<<endl;
	if (used[v])
		return ts[v]!=inf;
	used[v]=true;
	int sz=g[v].size();
	ts[v]=inf;
	bool q=true;
	for (int i=0;i<sz;i++)
		if (topsort(g[v][i])==false)
			q=false;
	tn--;
	if (!q)
		return false;
	ts[v]=tn;
	return true;
}

bool cmp(const pair<int,int> &a,const pair<int,int> &b)
{
	if (ts[a.second]==inf)
		return false;
	if (ts[b.second]==inf)
		return true;
	if (a.first!=b.first)
		return a.first<b.first;
	return ts[a.second]>ts[b.second];
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int t;
  scanf("%d %d",&n,&t);
  tn=n;
	for (int i=0;i<n;i++)
		{
			scanf("%d",&ans[i].first);
			ans[i].second=i;
		}
	int m;
	scanf("%d",&m); 
	for (int i=0;i<m;i++)
	{
		int a,b;
		scanf("%d %d",&a,&b);
		--a,--b;
		g[b].pb(a);
	}
	for (int i=0;i<n;i++)
		topsort(i);
	sort(ans,ans+n,cmp);
	int pen=0;
	int tt=0;
	int kol=0;
	for (int i=0;i<n && ts[ans[i].second]!=inf && tt+ans[i].first<=t;i++)
		{
			tt+=ans[i].first;
			pen+=tt;
			kol++;			
		}
	printf("%d %d\n",kol,pen);		
	tt=0;
	for (int i=0;i<n && ts[ans[i].second]!=inf && tt+ans[i].first<=t;i++)
		{
			tt+=ans[i].first;
			printf("%d ",ans[i].second+1);
		}
	printf("\n");
  return 0;
}
