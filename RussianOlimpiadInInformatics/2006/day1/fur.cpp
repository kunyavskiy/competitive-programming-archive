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
#define ld long double  
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

string s[1000];

typedef long long int64 ; 
typedef unsigned long long uint64 ;

const int inf=1<<29;

uint64 h[1000][2000];
int g[1000][1000];

int lcp(int a,int b){
	int l=0;
	int r=min(s[a].size(),s[b].size())+1;
	for (;r-l>1;){
		int m=(r+l)/2;
		if (h[a][m-1]==h[b][m-1])
			l=m;
		else
			r=m;
	}
	return l;
}

int from[1000];
bool used[1000];
int d[1000];
int n;

void print(int st,int en)
{
	if (en==st)
		return;
	int f=from[en];
	print(st,f);
	if (g[f][en]==1){
		if (en==(f+1)%n)
			printf("down\n");
		else
			printf("up\n");
		return;
	}
	printf("Alt\n");
	int kol=g[f][en]-1;
	for (int i=0;i<kol;i++)
		printf("%c\n",s[en][i]);
	return;
}

void findway(int& st,int& en){
	setval(used,false);
	for (int i=0;i<n;i++)
		d[i]=inf;
	d[st]=0;
	for (;;)
	{
		int md=-1;
		for (int i=0;i<n;i++)
			if (!used[i])
				if (md==-1 || d[md]>d[i])
					md=i;
		if (md==-1)
			break;
		used[md]=true;
		for (int i=0;i<n;i++)
			if (d[i]>d[md]+g[md][i])
				 {
						d[i]=d[md]+g[md][i];
						from[i]=md;											
				 }
	}
	printf("%d\n",d[en]);
	print(st,en);
	st=en;
}

int main()
{
  freopen("fur.in","r",stdin);
  freopen("fur.out","w",stdout);
	cin>>n;
	for (int i=0;i<n;i++)
	{
		cin>>s[i];
		int sz=s[i].size();
		h[i][0]=s[i][0]-'a'+1;
		for (int j=1;j<sz;j++)
			h[i][j]=h[i][j-1]*37+(s[i][j]-'a'+1);
	}
	for (int i=1;i<n;i++)
	{
		g[0][i]=0;
		for (int j=0;j<i;j++)
			g[0][i]=max(g[0][i],lcp(i,j)+1);
		if (g[0][i]>s[i].size())
			g[0][i]=inf;
		else 
			g[0][i]++;
	}	
	for (int i=1;i<n;i++){
		int ans=1;
		for (int j=i;j<i+n;j++)
			{
				int jn=j%n;
				int tmp=lcp(i-1,jn)+1;
				if (tmp>ans){
					g[i][jn]=ans;
					if (g[i][jn]>s[jn].size())
						g[i][jn]=inf;
					else
						g[i][jn]++;
					ans=max(ans,tmp);
				}
				else
					g[i][jn]=g[i-1][jn];
			}			
		g[i][i-1]=1;
		for (int j=0;j<n;j++)
			if (j!=i-1)
				g[i][i-1]=max(g[i][i-1],lcp(i-1,j)+1);
		if (g[i][i-1]>s[i-1].size())
			g[i][i-1]=inf;
		else 
			g[i][i-1]++;

	}
	for (int i=0;i<n;i++)
		{
			g[i][i]=0;
			g[i][(i+1)%n]=1;
			g[i][(i-1+n)%n]=1;
		}		
	int st=0;
	int m;
	scanf("%d",&m);	
	for (int i=0;i<m;i++)
		{
			int a;
			scanf("%d",&a);
			--a;
			findway(st,a);
		}
  return 0;
}