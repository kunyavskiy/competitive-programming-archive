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
#define time botva
using namespace std;

vector<pair<int,int> > g[100100],g1[100100];
int x[100100],x1[100100];
int p[100100];

bool cmp(int a,int b){
	return x1[a]<x1[b];
}

ld time[5100];

const ld inf=1e+10;


int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int b,n;
  scanf("%d %d",&b,&n);
 	x1[0]=b;
 	p[0]=0;
  for (int i=1;i<=n;i++){
  	int tmp;
  	scanf("%d %d",&x1[i],&tmp);
  	g1[i].resize(tmp);
  	for (int j=0;j<tmp;j++){
  		int a,b;
  		scanf("%d %d",&a,&b);
  		g1[i][j]=mp(b,a);
  	}
  	sort(g1[i].begin(),g1[i].end());
  	reverse(g1[i].begin(),g1[i].end());
  	p[i]=i;
  }
  ++n;
  sort(p,p+n,cmp);
	for (int i=0;i<n;i++)
		{
			x[i]=x1[p[i]];
			g[i]=g1[p[i]];
		}
	if (x[0]!=0)
	{
		printf("-1\n");
		return 0;
	}
	for (int i=0;i<n;i++)
		time[i]=inf;
	time[0]=0;	
	
	
	for (int i=0;i<n;i++){
		int sz=g[i].size();
		if (sz==0){
			if (time[i]>1e+09)
				printf("-1\n");
			else{
				cout.precision(8);
				cout<<fixed<<time[i]<<endl;
			}
			return 0;
		}
		int ptr=0;
		int v=0;
		for (int j=n-1;j>i;j--){
			for (;ptr<sz && x[j]-x[i]<=g[i][ptr].first;++ptr)
				v=max(v,g[i][ptr].second);
			if (v!=0)
				time[j]=min(time[j],time[i]+(x[j]-x[i])*1.0/v);
		}
	}
	
  return 0;
}