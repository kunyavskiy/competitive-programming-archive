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

set<int> g[10010];
int per[10010];
int ans;
int d[10010];
int n;

bool del1()
{                
	bool q=false;
	for (int i=0;i<n;i++)
	if (d[i]==1)
	{
		int s=*(g[i].begin());
		int md=min(per[s],per[i]);
		if (i==s)
		{
			md/=2;
			ans+=md;
			per[i]=0;
			g[i].clear();
			d[i]=0;
			continue;
		}
		per[i]-=md;
		per[s]-=md;
		ans+=md;
		d[s]--;
		d[i]=0;
		g[i].clear();
		g[s].erase(i);
		if (per[s]==0)
		{
			for (set<int>::iterator iter=g[s].begin();iter!=g[s].end();++iter)
				{
					int t=*iter;
					d[t]--;
					if (s!=t)
						g[t].erase(s);
				}
			g[s].clear();
			d[s]=0;
		}
		q=true;
	}
	return q;
}


int next[10010];
                    
void perebor(int v)
{                       
	int s=*g[v].begin();
	g[s].erase(v);
	g[v].erase(s);
	int m=min(per[v],per[s]);
	int mans=0;     
	memset(next,0,sizeof(next));
	for (int i=v;i!=s;)
	{
		int tmp=*g[i].begin();  
		g[tmp].erase(i);
		next[i]=tmp;
		i=tmp;                               
	}
	for (int i=0;i<=m;i++)
	{
		int tans=i;
		per[s]-=i;
		int bef=i;
		for (int j=v;j!=s;j=next[j])
		{
			int tmp=min(per[j]-bef,per[next[j]]);
			bef=tmp;
			tans+=tmp;
		}
		per[s]+=i;
		if (tans>mans)
			mans=tans;
	}
	ans+=mans;
	for (int i=v;i!=s;i=next[i])
	{
		per[i]=d[i]=0;
		g[i].clear();
	}
	per[s]=d[s]=0;
	g[s].clear();
}


int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  setval(per,0);
  setval(d,0);
 	scanf("%d",&n);
 	for (int i=0;i<n;i++)
 		{
 			int a;
 			scanf("%d %d",&per[i],&a);
 			--a;               
 			if (g[i].find(a)==g[i].end())
 			{
	 			g[i].insert(a);   
	 			d[i]++;
	 			if (a!=i)
	 			{
 					d[a]++;
		 			g[a].insert(i);
 				}
 			}
 		}
 	for (;del1(););
 	for (int i=0;i<n;i++)
 	{                                  
 		if (d[i]!=0)
 			perebor(i);
 	}
	cout<<ans<<endl;
  return 0;
}