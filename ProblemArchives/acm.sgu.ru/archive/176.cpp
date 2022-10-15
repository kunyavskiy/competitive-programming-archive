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

const int maxn=110;

int64 c[maxn][maxn];
int64 f[maxn][maxn];
int64 num[maxn][maxn];
bool need[maxn][maxn];
bool used[maxn];
int flow[maxn*maxn];
int t;
int n,m;
const int64 inf=1ll<<50;
int par[maxn];
int d[maxn];
int64 cur_flow;

int64 go(int t,int s,int64 mv){
	if (t==s)
		return min(mv,cur_flow);
	int p=par[t];
	int64 tmp=go(p,s,min(c[p][t],mv));
	f[p][t]+=tmp;
	f[t][p]-=tmp;
	c[p][t]-=tmp;
	c[t][p]+=tmp;
	return tmp;
}

int64 bfs(int v){
	queue<int> q;
	q.push(v);
	setval(d,1);
	setval(par,-1);
	d[v]=0;
	for (;!q.empty();){
		int fr=q.front();
		q.pop();
		for (int i=0;i<n;i++)
			if (c[fr][i]>0 && !need[fr][i] && !need[i][fr])
				if (d[i]>d[fr]+1)
					{
						d[i]=d[fr]+1;
						q.push(i);
						par[i]=fr;
					}
	}
	if (par[t]==-1)
		return 0;
	return go(t,v,inf);
}



int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  scanf("%d %d",&n,&m);
  setval(c,0);
  for (int i=0;i<m;i++){
  	int a,b,w,q;
  	scanf("%d %d %d %d",&a,&b,&w,&q);
  	--a;--b;
  	c[a][b]=w;
  	need[a][b]=q;
  	num[a][b]=i;
  }
	c[n-1][0]=inf; 
  n+=2;
  t=n-1;
  int s=n-2;
  for (int i=0;i<n-2;i++)
  	for (int j=0;j<n-2;j++)
  		if (need[i][j]){
  			c[s][j]+=c[i][j];
  			c[i][t]+=c[i][j];
  		}	
  		
  cur_flow=inf;
  		
  for (;bfs(s)>0;)
  	setval(used,false);
  for (int i=0;i<n;i++)
  	if (c[i][t]!=0)
  		{
  			printf("Impossible\n");
  			return 0;
  		}
  		
  for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if (need[i][j])
				{
					f[i][j]=c[i][j];
					f[j][i]=-c[i][j];
					c[i][j]=c[j][i]=0;
					need[i][j]=need[j][i]=0;
				}
	
				
	n-=2;
	s=n-1;
	t=0;
	c[s][t]=c[t][s]=0;			
	f[t][s]=f[s][t]=0;
	
 // for (int i=0;i<n;i++)
//  	for (int j=0;j<n;j++)
//  		cerr<<f[i][j]<<" \n"[j==n-1];
//  cerr<<endl<<endl;

  cur_flow=0; 
 	for (int i=0;i<n;i++)
		cur_flow+=f[0][i];
	cerr<<cur_flow<<endl;	
	setval(used,false);
	for (;;){
		int tmp=bfs(s);
		if (tmp==0)
			break;
		cur_flow-=tmp;
	}
		
		
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if (f[i][j]>0)	
				flow[num[i][j]]=f[i][j];
		
	cout<<cur_flow<<endl;
	for (int i=0;i<m;i++)
		printf("%d ",flow[i]);
	printf("\n");
  return 0;
}