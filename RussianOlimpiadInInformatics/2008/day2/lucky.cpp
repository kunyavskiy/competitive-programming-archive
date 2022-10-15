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

int64 n,k;

int cnt(int64 p){
	int64 n1=n;
	int kol=0;
	for (;n1%p==k;kol++)
		n1/=p;
	return kol;
}

int main()
{
  freopen("lucky.in","r",stdin);
  freopen("lucky.out","w",stdout);
 // ld tm=clock();
  cin>>n>>k;
  if (n==k){
		cout<<n+1<<" "<<1<<endl;
  	return 0;  	
  }
  if (n<k || n==1){
  	printf("2 0\n");
  	return 0;
  }
  int64 ans=0,ansnum=2;
  for (int64 i=1;i*i<=n-k;i++)
  if ((n-k)%i==0)
  {
  	if (i!=1){
	  	int tmp=cnt(i);
  		if (tmp>ans){
	  		ans=tmp;
	  		ansnum=i;
	  	}
	  }
  	int tmp=cnt((n-k)/i);
		if (tmp>ans){
  		ans=tmp;
  		ansnum=(n-k)/i;
  	}  	
  }
  cout<<ansnum<<" "<<ans<<endl;
 // cerr<<(clock()-tm)/CLOCKS_PER_SEC<<endl;
  return 0;
}