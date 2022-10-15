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

vector<int> g[1100];
int d[1100];
int p[1100];
int ans;
int res;

void bfs(int v)
{
	memset(d,1,sizeof(d));
	memset(p,-1,sizeof(p));
	d[v]=0;
	queue<int> q;
	q.push(v);
	for (;!q.empty();){
		int v=q.front();
//		cerr<<v<<endl;
		q.pop();
		int sz=g[v].size();
		for (int i=0;i<sz;i++){
			int to=g[v][i];
//			cerr<<to<<" "<<v<<" "<<p[to]<<endl;
			if (to==p[v])
				continue;
			if (to!=p[v] && p[to]!=-1)
			{             
				ans=min(ans,d[v]+d[to]+1);
				continue;				
			}
			d[to]=d[v]+1;
			p[to]=v;
			q.push(to);
		}
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,m;
	while (true)
	{
		int sch=scanf("%d %d",&n,&m);
		if (sch!=2)
			return 0;                
		for (int i=0;i<n;i++)
			 g[i].clear();
		ans=1<<30;
		for (int i=0;i<m;i++)
		{
			int a,b;
			scanf("%d %d\n",&a,&b);
			--a,--b;
			g[a].pb(b);
			g[b].pb(a);
			assert(a!=b);
		}
		for (int i=0;i<n;i++)
			{
				sort(g[i].begin(),g[i].end());
				assert(unique(g[i].begin(),g[i].end())==g[i].end());
			}
		for (int i=0;i<n;i++)
			bfs(i);
		if (ans==(1<<30))
			cout<<-1<<endl;
		else
			cout<<ans<<endl;
	}
	return 0;
}