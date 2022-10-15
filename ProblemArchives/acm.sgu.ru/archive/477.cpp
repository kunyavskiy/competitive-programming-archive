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

int p[5100];
int q[5100];

int t1[5100];
int t2[5100];

int n,m,d;

bool cmp(const pair<int,int>& a,const pair<int,int> &b){
	if (a.first!=b.first)
		return a.first<b.first;
	return a.first>b.second;
}

pair<int,int> ev[11000];
pair<int,int> f[11000];
pair<int,int> s[11000];

int merge(int* p,pair<int,int>* ans,int t,int n){
	int sz=0;
	for (int i=0;i<n;i++){
		if (sz==0 || ans[sz-1].second<p[i]-t)
			{
				ans[sz].first=p[i]-t;
				ans[sz].second=p[i]+t;
				++sz;
			}
		else
			ans[sz-1].second=p[i]+t;
	}	
	return sz;
}

bool intersec(int sz1,int sz2){
	int ptr1=0;
	int ptr2=0;
	for (;ptr1<sz1 && ptr2<sz2;){
		pair<int,int> isec;
		isec.first=max(f[ptr1].first,s[ptr2].first);
		isec.second=min(f[ptr1].second,s[ptr2].second);
		if (isec.second-isec.first>d)
			return false;
		if (f[ptr1].second<s[ptr2].second)
			++ptr1;
		else
			++ptr2;			
	}
	return true;
}

bool check(int t1,int t2){
	int sz1=merge(p,f,t1,n);
	int sz2=merge(q,s,t2,m);
	return intersec(sz1,sz2);
};

void solve(){

	if (check(1,1)==false)
		{
			printf("No solution\n");
			return;
		}
	t1[0]=1;
	for (int i=0;i<n-1;i++)
		t1[i+1]=(p[i+1]-p[i]+1)/2;
	sort(t1,t1+n);
		
	t2[0]=1;
	for (int i=0;i<m-1;i++)
		t2[i+1]=(q[i+1]-q[i]+1)/2;
	sort(t2,t2+m);
	int ptr1=0;
	int ptr2=m-1;
	int ans=-1,anst1=-1,anst2=-1;
	for (;ptr1<n;++ptr1)
	{
		for (;ptr2>=0 && check(t1[ptr1],t2[ptr2])==false;ptr2--);
		if (ptr2<0)
			break;
		if (ans<ptr1+ptr2){
			ans=ptr1+ptr2;
			anst1=t1[ptr1];
			anst2=t2[ptr2];
		}
	}
	printf("%d %d\n",anst1,anst2);
}


int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
   
  scanf("%d %d %d",&n,&m,&d);
  for (int i=0;i<n;i++)
  	scanf("%d",&p[i]);
  for (int j=0;j<m;j++)
  	scanf("%d",&q[j]);
  	
  solve();
  return 0;
}