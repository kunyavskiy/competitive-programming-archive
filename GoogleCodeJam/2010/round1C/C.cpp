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

int ans[512][512];

int a[512][512];
int szkol[513];
int n,m;  

void use(int lx,int rx,int ly,int ry){
	for (int i=2*lx-rx;i<rx;i++)
		for (int j=2*lx-rx;j<ry;j++){
			int tmp=lx-i;
			tmp=max(tmp,ly-j);
			tmp=max(tmp,0);
			ans[i][j]=min(ans[i][j],tmp);
		}
}

int cnt(int i,int j){
	if (i==n-1 || j==m-1) 
		return ans[i][j]=1;
	if (ans[i][j]!=-1)
		return ans[i][j];
	if (a[i][j+1]==a[i][j])
		return ans[i][j]=1;
	if (a[i+1][j]==a[i][j])
		return ans[i][j]=1;
	int tmp=min(cnt(i+1,j),cnt(i,j+1));
	if (a[i+tmp][j+tmp]==a[i][j])
		tmp++;
	return ans[i][j]=tmp;
		
}

void solve(int tnum){
	scanf("%d %d",&n,&m);
	for (int i=0;i<n;i++)
		for (int j=0;j<m/4;j++){	
			char c;
			scanf(" %c ",&c);
			int tmp=0;
			if ('0'<=c && c<='9')
				tmp=c-'0';
			else
				tmp=c-'A'+10;
			for (int k=3;k>=0;k--)
			{
				a[i][j*4+k]=tmp&1;
				tmp>>=1;
			}
		}

	memset(ans,-1,sizeof(ans));
		
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			cnt(i,j);
	
	int tans=0;
	int kol=512;
	for (;kol;--kol){
		szkol[kol]=0;
		bool q=false;
		for (int i=0;i<n;i++)
			for (int j=0;j<m;j++)
				if (ans[i][j]==kol)
				{
					use(i,i+kol,j,j+kol);
					szkol[kol]++;
					q=true;
				}
		if (q)
			++tans;
	}
	printf("Case #%d: %d\n",tnum,tans);
//	cerr<<tnum<<endl;
	for (int i=512;i>=0;--i)
		if (szkol[i]!=0)
			printf("%d %d\n",i,szkol[i]);
}

int main()
{
  //freopen("input.txt","r",stdin);
//  freopen("output.txt","w",stdout);
  int t;
  cin>>t;
  for (int i=1;i<=t;i++)
  	solve(i);
  
  return 0;
}