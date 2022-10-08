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

int t[3000][10];
int cost[3000];
int m[3000];

const int inf=1<<27;

int cnt(int pos,int dec,int l,int r){
	if (t[pos][dec]!=-1)
		return t[pos][dec];
	if (l==r){
		if (m[l]-dec<=0)
			return 0;
		return inf;
	}
	int tmp=cnt(pos*2,dec,l,(l+r)/2)+cnt(pos*2+1,dec,(l+r)/2+1,r);
	tmp=min(tmp,cost[pos]+cnt(pos*2,dec+1,l,(l+r)/2)+cnt(pos*2+1,dec+1,(l+r)/2+1,r));
	if (tmp>inf)
		tmp=inf;
	return t[pos][dec]=tmp;	
}

void solve(){
	int p;
	cin>>p;
	int n=(1<<p);
	for (int i=0;i<n;i++)
	{
		scanf("%d",&m[i]);
		m[i]=p-m[i];
	}
	for (int i=p-1;i>=0;--i){
		int st=1<<i;
		for (int j=0;j<(1<<i);j++)
			scanf("%d\n",&cost[st+j]);		
	}
	setval(t,-1);
	cout<<cnt(1,0,0,n-1)<<endl;
}

int main()
{
  int t;
  cin>>t;
  for (int i=0;i<t;i++){
  	printf("Case #%d: ",i+1);
  	solve();
  }
  return 0;
}