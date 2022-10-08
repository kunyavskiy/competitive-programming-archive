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

int n;
int a[300][300];

bool cmp(int a,int b){
	return a==b || a==10 || b==10;
}

void readdata(){
	cin>>n;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			a[i][j]=10;
	vector<vector<int> > v(2*n);
	for (int i=0;i<2*n-1;i++){
		int sz;
		if (i<n)
			sz=i+1;
		else
			sz=2*n-i-1;
		v[i].resize(sz);
		for (int j=sz-1;j>=0;j--)
			scanf("%d",&v[i][j]);
	}
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
		{
			a[i][j]=v[i+j].back();
			v[i+j].pop_back();
		}
}

void vsymetry(){
	for (int i=0;i<n;i++)	
		for (int j=0;j*2<n;j++)
			swap(a[i][j],a[i][n-j-1]);
	return;
}

void dsymetry(){
	for (int i=0;i<n;i++)
		for (int j=0;i+j<n;j++)
			swap(a[i][j],a[n-j-1][n-i-1]);
	return ;
}

int cnt(){
	int ans=0;
	for (int sz=1;sz<=n;sz++)
	{
		bool q=true;
		for (int i=0;i<sz && q;i++)
			for (int j=0;j<sz && q;j++)
				if (!cmp(a[i][j],a[sz-j][sz-i]))
					q=false;
		if (q)
			ans=sz;						
	}
	return ans;
}



void solve(){
	readdata();
	int n0=n;
	
		int tmp1=cnt();
		dsymetry();
		int tmp2=cnt();
		if (tmp2<tmp1)
		{
			dsymetry();
			swap(tmp1,tmp2);
		}
		
		int nn=2*n-tmp1;
					
		for (int i=0;i<nn;i++)
			for (int j=0;j<nn;j++)
				if (i>=n || j>=n)
					a[i][j]=10;
					
		for (int i=0;i<n;i++)
			for (int j=0;j<n;j++)
			{
				assert(cmp(a[nn-j-1][nn-i-1],a[i][j]));
				a[nn-j-1][nn-i-1]=a[i][j];
			}

		n=nn;	

		vsymetry();	
	}
	
	cout<< n*n-n0*n0<<endl;
	return ;
}

int main()
{

  int t;
  cin>>t;
  for (int i=0;i<t;i++)
  {
  	printf("Case #%d: ",i+1);
  	solve();
  }
  return 0;
}