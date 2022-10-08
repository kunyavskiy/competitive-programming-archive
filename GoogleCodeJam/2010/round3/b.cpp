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


void PreCalc(){
}


const int maxn=10001000;

int n;
int a[100];
int64 l;

const int inf=1<<30;

int v[maxn];
int ans[maxn];




void solve(){
	
	cin>>l;

	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d",&a[i]);
		
	sort(a,a+n);	
		
	for (int i=0;i<maxn;i++)
		t[i]=inf;
		
	t[0]=0;
		
	for (int i=0;i<n-1;i++)
		for (int j=0;j<maxn;j++)
			if (a[i]<=j)
				t[j]=min(t[j],t[j-a[i]]+1);
	
	int64 ans=(1ll<<60);			
				
	for (int i=0;i<maxn;i++)
		if ((l-i)%a[n-1]==0 && t[i]!=inf)
			ans=min(ans,t[i]+(l-i)/a[n-1]);
			
	if (ans==(1ll<<60))
		cout<<"IMPOSSIBLE"<<endl;
	else	
		cout<<ans<<endl;
}

int main()
{
	PreCalc();
	int t;
	cin>>t;
	for (int i=1;i<=t;i++)
		{
			printf("Case #%d: ",i);
			solve();
			if (i%5==0)
				cerr<<"SOLVED:"<<i<<endl;
		}
  return 0;
}