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

int64 cnt[100000];
int n,p;

int check(int64 a){
	int64 res=0;
	for (int i=0;i<n;i++)
		res+=min(a,cnt[i]);
	if (res>=a*p)
		return p;
	if (res<=(a-1)*p)
		return 0;
	return res%p;	
}

int main()
{
  freopen("trees.in","r",stdin);
  freopen("trees.out","w",stdout);
  scanf("%d %d",&n,&p);
  for (int i=0;i<n;i++)
  	{
  		int a;
  		scanf("%d",&a);
  		cnt[i]=a;
  	}
  int64 l=0;
  int64 r=(int64)(1E+15);
  for (;r-l>1;){
  	int64 m=(l+r)/2;
  	int tmp=check(m);
  	if (tmp==p)
  		l=m;
  	else
  		r=m;
  }  
  cout<<(l*p+check(l+1))<<endl;
  return 0;
}