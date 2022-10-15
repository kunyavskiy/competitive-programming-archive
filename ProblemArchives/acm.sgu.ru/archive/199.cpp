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

struct per{
	int s,b,num;
};

bool operator<(const per& a,const per& b){
	return a.s<b.s;
}

int t[200100];
int pos[200100];
per a[200100];
const int inf=1e+09+10000;
vector<int> ans;

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int n;
  scanf("%d",&n);
  for (int i=0;i<n;i++)
  {
  	scanf("%d %d",&a[i].s,&a[i].b);
  	a[i].num=i+1;
  	t[i]=inf;
  }
  for (int i=n;i<n+50;i++)
  	t[i]=inf;
  sort(a,a+n);
	for (int i=0;i<n;){
		int tmps=a[i].s;
		int tmpi=i;
		for (;i<n && a[i].s==tmps;i++)
		{
			int* tmp=lower_bound(t,t+n,a[i].b);
			pos[i]=tmp-t;
		}
		i=tmpi;
		for (;i<n && a[i].s==tmps;i++)
			t[pos[i]]=min(t[pos[i]],a[i].b);
	}
	int sz=0;
	for (;t[sz]!=inf;++sz);
	printf("%d\n",sz);
	int lv=inf;
	int sv=inf;
	for (int i=n-1;i>=0;i--){
		if (sz==0)
			break;
		if (a[i].b<lv && a[i].s!=sv && pos[i]+1>=sz)
			{
				ans.pb(i);
				lv=a[i].b;
				sv=a[i].s;
				--sz;
			}
	}
	reverse(ans.begin(),ans.end());
	sz=ans.size();
	for (int i=0;i<sz;i++)
		printf("%d ",a[ans[i]].num);
	
  return 0;
}