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
  cin>>n>>k;
  int ans,ansnum;
  ans=cnt(2);
  ansnum=2;
  for (int i=3;i<n+2;i++){
  	int tmp=cnt(i);
  	if (tmp>ans){
  		ans=tmp;
  		ansnum=i;
  	}
  }
  printf("%d %d\n",ansnum,ans);	
  return 0;
}