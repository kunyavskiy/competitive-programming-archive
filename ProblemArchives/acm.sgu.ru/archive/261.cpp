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

int mod;

int pow(int a,int b){
	if (b<0){
		return pow(pow(a,mod-2),-b);
	}
	if (b==0)
		return 1;
	if (b%2==1){
		int tmp=pow(a,b-1);
		tmp=(tmp*1ll*a)%mod;
		return tmp;
	}
	int tmp=pow(a,b/2);
	return (tmp*1ll*tmp)%mod;
}

bool check(int r){
	int x=mod-1;
	for (int i=1;i*i<=mod;i++)
		if (x%i==0)
			if (pow(r,i)==1 || (i!=1 && pow(r,x/i)==1))
				return false;
	return true;
}

int find_root(){
	for (int i=1;;i++)
		if (check(i))
			return i;
	assert(false);
}

vector<int> find_log(int a,int b){
	assert(a!=1);
	int n=(int)sqrt(mod*1.0);
	if (n*n<mod)
		n++;
	vector<pair<int,int> > pv;
	vector<pair<int,int> > qv;
	int tmp=b;
	for (int i=1;i<=n;i++)
	{
		tmp=(tmp*1ll*a)%mod;		
		qv.pb(mp(tmp,i));
	}
	a=pow(a,n);
	tmp=a;
	for (int i=1;i<=n;i++)
	{
		pv.pb(mp(tmp,i));
		tmp=(tmp*1ll*a)%mod;
	}
	sort(pv.begin(),pv.end());
	sort(qv.begin(),qv.end());
	int ptr=0;
	vector<int> ans;
	for (int i=0;i<n;i++)
		{
			for (;ptr<n && qv[ptr].first<pv[i].first;ptr++);
			int tmp=ptr;
			for (;ptr<n && pv[i].first==qv[ptr].first;ptr++){
				int tmp=pv[i].second*n-qv[ptr].second;
				ans.pb(tmp);				
			}
			ptr=tmp;
		}                                         	
	return ans;
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int k,a;
  cin>>mod>>k>>a;
  k%=mod-1;
  a%=mod;
  if (a==0){
  	printf("1\n0\n");
  	return 0;
  }
  if (k==0){
  	if (a!=1){
  		printf("0\n");
  		return 0;
  	}
  	printf("%d\n",mod-1);
  	for (int i=1;i<mod;i++)
  		printf("%d\n",i);
  	return 0;
  }
  
  int root=find_root();
 	vector<int> ans=find_log(pow(root,k),a);
 	int sz=ans.size();
 	for (int i=0;i<sz;i++)
		ans[i]=pow(root,ans[i]);
 	sort(ans.begin(),ans.end());
 	ans.erase(unique(ans.begin(),ans.end()),ans.end());
 	sz=ans.size();
 	cout<<sz<<endl;
 	for (int i=0;i<sz;i++)
 		printf("%d ",ans[i]);
 	printf("\n");
  return 0;
}