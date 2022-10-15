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

bool check(int64 a){
	if (a<2)
		return false;
	for (int i=2;i*i<=a;i++)
		if (a%i==0)
			return false;
	return true;
}

int64 next(int64 a){
	for (;!check(a);++a);
	return a;
}

int64 st10(int a){
	int64 res=1;
	for (int i=0;i<a;i++)
		res*=10;
	return res;
}

void solve(int d,string n){
	int64 ans=1LL<<60LL;
	int sz=n.size();
	if (d+d>sz)
		ans=next(st10(d-1))*1LL*st10(d)+next(st10(d-1));
	for (int i=d;i+d<=sz+1;i++){
		int i1=max(sz-i,d);
		int64 tmp=0;
		if (i+i1<=sz)
			tmp=next(atoi(string(n.begin(),n.begin()+i).data()))*1LL*st10(i1)+next(st10(i1-1));
		else
			tmp=next(st10(i-1))*1LL*st10(i1)+next(st10(i1-1));
		ans=min(ans,tmp);
		i1++;
		if (i+i1<=sz)
			tmp=next(atoi(string(n.begin(),n.begin()+i).data()))*1LL*st10(i1)+next(st10(i1-1));
		else
			tmp=next(st10(i-1))*1LL*st10(i1)+next(st10(i1-1));
		ans=min(ans,tmp);		
	}
	cout<<ans<<endl;
}


int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
	int d;
	string n;
	while (cin>>d>>n)
		solve(d,n);
  return 0;
}