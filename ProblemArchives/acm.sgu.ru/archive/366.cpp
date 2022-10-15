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


int sum[60000];

vector<int> vals[101];
vector<int> psum[101];

int t[101][21][2001];
int from[101][21][2001];

const int inf=1<<30;

bool sumcmp(int a,int b){
	return sum[a]>sum[b];
}

vector<int> ans;

void print(int m,int k,int s){
	if (m==0)
	{
		for (int i=0;i<k;i++)
			ans.pb(vals[0][i]);
		return;
	}
	for (int i=0;i<from[m][k][s];i++)
		ans.pb(vals[m][i]);
	int kol=from[m][k][s];
	print(m-1,k-kol,s-kol*(m-50));
}



int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int n,k;
  scanf("%d",&n);
  scanf("%d",&k);
  for (int i=0;i<n;i++){
  	int a,b;
  	scanf("%d %d",&a,&b);
  	vals[a-b+50].pb(i);
  	sum[i]=a+b;
  }
  for (int i=0;i<101;i++)
  {
  	sort(vals[i].begin(),vals[i].end(),sumcmp);
  	if (vals[i].size()>k)
  		vals[i].erase(vals[i].begin()+k,vals[i].end());
  	if (vals[i].size()==0)
  		continue;
  	psum[i].resize(vals[i].size());
		psum[i][0]=sum[vals[i][0]];
  	for (int j=1;j<vals[i].size();j++)
			psum[i][j]=psum[i][j-1]+sum[vals[i][j]];
  }
  for (int i=0;i<21;i++)
		for (int j=0;j<2001;j++)
			if (i==0 && j==1000)
				t[0][i][j]=0;
			else
				t[0][i][j]=-inf;
	for (int i=0;i<vals[0].size();i++)
		t[0][i+1][(-50*(i+1))+1000]=psum[0][i];
	for (int i=1;i<101;i++)
			for (int j=0;j<=k;j++)
				for (int sum=0;sum<2001;sum++){
					t[i][j][sum]=t[i-1][j][sum];
					for (int kol=0;kol<vals[i].size();kol++)
					if (kol<j)
					{
						if (sum-(kol+1)*(i-50)<0)
							continue;						
						if (sum-(kol+1)*(i-50)>2000)
							continue;
						if (t[i][j][sum]<t[i-1][j-kol-1][sum-(kol+1)*(i-50)]+psum[i][kol])
						{
							t[i][j][sum]=t[i-1][j-kol-1][sum-(kol+1)*(i-50)]+psum[i][kol];
							from[i][j][sum]=kol+1;
						}
					}
				}
	for (int asum=0;;++asum)
		{
			int tmp=max(t[100][k][1000+asum],t[100][k][1000-asum]);
			if (tmp<0)
				continue;
			if (tmp==t[100][k][1000+asum])
				{
					printf("%d %d\n",(asum+t[100][k][1000+asum])/2,(t[100][k][1000+asum]-asum)/2);
					print(100,k,1000+asum);
					sort(ans.begin(),ans.end());
					for (int i=0;i<k;i++)
						printf("%d ",ans[i]+1);
					return 0;
				}
			if (tmp==t[100][k][1000-asum])
				{						
//					cerr<<asum<<" "<<t[100][k][1000-asum]<<endl;
					printf("%d %d\n",(-asum+t[100][k][1000-asum])/2,(asum+t[100][k][1000-asum])/2);
					print(100,k,1000-asum);
					sort(ans.begin(),ans.end());
					for (int i=0;i<k;i++)
						printf("%d ",ans[i]+1);
					return 0;
				}
		}
  return 0;
}