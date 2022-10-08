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

struct three{
	int mask1,mask2, sum;
	three(int m1,int m2,int s){
		mask1=m1;
		mask2=m2;
		sum=s;
	}
};

bool operator<(const three& a,const three& b){
	if (a.mask1!=b.mask1)
		return a.mask1<b.mask1;
	if (a.mask2!=b.mask2)
		return a.mask2<b.mask2;
	return a.sum<b.sum;
}

map<three,int> t;
int base;

int calc(int mask1,int mask2,int sum){

	if (sum<0)
		return 0;
	
	if (sum==0)
		return 1;
	
	if (t.find(three(mask1,mask2,sum))!=t.end())	
		return t[three(mask1,mask2,sum)];
		
	int ans=0;
		
	for (int f=0;f<base;f++)
		if (mask1 & (1<<f))
			for (int s=0;s<base;s++)
				if (mask2 & (1<<s)){
					ans=ans+calc(((mask1 & (~(1<<f))) | 1),(mask2 & (~(1<<s))),sum-f*base-s);
					ans%=1000000007;
				}
	if (sum==100)
		ans++;
	return t[three(mask1,mask2,sum)]=ans;					
}


void solve(){
	t.clear();
	int n;
	cerr<<"!"<<endl;
	cin>>n>>base;
	cerr<<n<<" "<<base<<endl;
	cout<<calc((1<<base)-1,(1<<base)-1,n)<<endl;
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
			cerr<<"SOLVED:"<<i<<endl;
		}


  return 0;
}