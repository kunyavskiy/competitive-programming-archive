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

bool pr[1001000];

void PreCalc(){
	int maxn=1000000;
	memset(pr,true,sizeof(pr));
	pr[0]=pr[1]=0;
	for (int i=2;i<=maxn;i++)
		{
			if (pr[i]==true){
				for (int j=i;i*1ll*j<=maxn;j++)
					pr[i*j]=false;
			}
		}
}

int s[10];
int d,k;
int ans;


int64 gcd (int64 a, int64 b, int64 & x, int64 & y)
{
	if (a == 0)
	{
		x = 0; y = 1;
		return b;
	}
	int64 x1, y1;
	int64 d = gcd (b%a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

bool check(int p){	

	for (int i=0;i<k;i++)
		if (s[i]>p-1)
			return true;
			
	if (k==1)
		return false;		
	if (k==2){
		for (int a=0;a<p;a++){	
			int b=(s[1]-a*s[0]+10000000*1ll*p)%p;
			int ts=s[0];
			bool q=true;
			for (int i=1;i<k;i++){
				ts=(ts*a+b)%p;
				if (ts!=s[i]){
					q=false;
					break;
				}
			}
			if (q){
				int nans=(ts*a+b)%p;
				if (nans!=ans && ans!=-1)
					return false;
				ans=nans;
			}
		}
		return true;
	}
	
	int64 a,pm1;
	
	int64 tmp=(s[0]-s[1]+10000000*1ll*p)%p;	
	gcd(tmp,p,a,pm1);
	
	a%=p;
	
	a=(a*1ll*(s[1]-s[2])+10000000*1ll*p)%p;
	
	assert((a*(s[0]-s[1])+10000000*1ll*p)%p==((s[1]-s[2])+10000000*1ll*p)%p);
	
	
	int b=(s[1]-a*s[0]+10000000*1ll*p)%p;
	int ts=s[0];
	bool q=true;
	for (int i=1;i<k;i++){
		ts=(ts*a+b)%p;
			if (ts!=s[i]){
				q=false;
				break;
			}
		}
	if (q){
			int nans=(ts*a+b)%p;
			if (nans!=ans && ans!=-1)
				return false;
			ans=nans;
	}
	
	return true;
}

void solve(){

	cin>>d>>k;
	for (int i=0;i<k;i++){
		cin>>s[i];
	}
	int tmp=1;
	for (int i=0;i<d;i++)
		tmp*=10;
	d=tmp;
	ans=-1;
	
	
	for (int i=0;i<k-1;i++)
		if (s[i]==s[i+1]){
			printf("%d\n",s[i]);
			return;
		}
		
	
	for (int i=0;i<d;i++)
		if (pr[i] && !check(i)){
			printf("I don't know.\n");
			return;
		}

	if (ans==-1){
			assert(false);
			return;	
	}	
	
	printf("%d\n",ans);
	return;
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
			if (i%10==0)
				cerr<<"SOVED:"<<i<<endl;
		}


  return 0;
}