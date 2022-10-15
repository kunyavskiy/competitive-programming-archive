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



int pot[400];
int f[400][400];
int c[400][400];
int w[400][400];

int par[400];
int d[400];
bool used[400];

int n;

vector<int> ans1,ans2;

void flow(int v){
	if (v==0)
		return;
	int p=par[v];
	f[p][v]++;
	c[p][v]--;
	c[v][p]++;
	f[v][p]--;
	flow(p);
	return;
}

void deigstra(){
	memset(d,1,sizeof(d));
	memset(par,-1,sizeof(par));
	memset(used,0,sizeof(used));
	d[0]=0;

	for (int i=0;i<n;i++){
		int mv=-1;
		for (int i=0;i<n;i++)
			if (!used[i])
				if (mv==-1 || d[mv]>d[i])
					mv=i;
		if (mv==-1)
			break;
		used[mv]=true;
		for (int j=0;j<n;j++)
			if (c[mv][j])
			{
				int len=w[mv][j];
				if (f[mv][j]==-1)
					len*=-1;
				len=len+pot[mv]-pot[j];
				if (d[j]>d[mv]+len){
					d[j]=d[mv]+len;
					par[j]=mv;
				}
			}
	}
	for (int i=0;i<n;i++)
		pot[i]+=d[i];
}

void find_way(int v,int p,vector<int>& res){
	if (v==n-1)
		{
			res.pb(v);
			return;
		}
	for (int i=0;i<n;i++)
		if (f[v][i]>0){
			f[v][i]--;
			f[i][v]++;
			c[v][i]++;
			c[i][v]--;
			find_way(i,v,res);
			res.pb(v);
			if (v==0)
				reverse(res.begin(),res.end());
			return;
		}
	assert(false);			
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
  	int a,b,cs;
  	scanf("%d %d %d",&a,&b,&cs);
  	--a,--b;
  	c[a][b]=c[b][a]=1;
  	w[a][b]=w[b][a]=cs;
  	f[a][b]=f[b][a]=0;
  }
	deigstra();
  if (par[n-1]==-1)
  	{
  		printf("No solution\n");
  		return 0;
  	}
//  cerr<<"FIND 1 WAY"<<endl;
  flow(n-1);
  deigstra();
  if (par[n-1]==-1)
  	{
  		printf("No solution\n");
  		return 0;
  	}
 // cerr<<"FIND 2 WAY"<<endl;
  flow(n-1);
  find_way(0,-1,ans1);
  find_way(0,-1,ans2);
  int sum1=0;
  for (int i=0;i<ans1.size()-1;i++)
  	sum1+=w[ans1[i]][ans1[i+1]];
  int sum2=0;
  for (int i=0;i<ans2.size()-1;i++)
  	sum2+=w[ans2[i]][ans2[i+1]];
  if (sum1!=sum2){
  		printf("No solution\n");
  		return 0;
  }	
//  cerr<<"EQL SUM"<<endl;
  for (int i=0;i<ans1.size();i++)
		printf("%d ",ans1[i]+1);
 	printf("\n");
  for (int i=0;i<ans2.size();i++)
		printf("%d ",ans2[i]+1);
 	printf("\n");
  return 0;
}