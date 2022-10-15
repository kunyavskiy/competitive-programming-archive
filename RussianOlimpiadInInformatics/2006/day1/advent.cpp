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

vector<int> ans;

int l[2000];
int h[2000];
int sl[2000];
int ss[2000];
int sh[2000];
bool used[2000];
bool give[2000];
int sum,n;
int ptl,pts,pth;

bool cmpl(int a,int b){
	return l[a]<l[b];
}

bool cmph(int a,int b){
	return h[a]>h[b];
}

bool cmps(int a,int b){
	return h[a]+l[a]>h[b]+l[b];
}

void nextl(){
	for (;ptl<n && used[sl[ptl]];ptl++);
}

void nexts(){
	for (;pts<n && used[ss[pts]];pts++);
}


void nexth(){
	for (;pth<n && used[sh[pth]];pth++);
}

bool iterate(int& H){
	nexts();
	for (;pts<n && h[ss[pts]]+l[ss[pts]]>=H;nexts())
	{
		used[ss[pts]]=give[ss[pts]]=true;		
		H-=h[ss[pts]];
		sum-=h[ss[pts]];
	}
	nextl();
	for (;ptl<n && sum+l[sl[ptl]]<H;nextl())
	{
		used[sl[ptl]]=true;
		give[sl[ptl]]=false;
		H-=h[sl[ptl]];
		sum-=h[sl[ptl]];		
	}
	nexth();
	if (pth==n)
		return false;
	used[sh[pth]]=true;
	give[sh[pth]]=false;
	H-=h[sh[pth]];
	sum-=h[sh[pth]];			
	return true;
}

int main()
{
	freopen("advent.in","r",stdin);
  freopen("advent.out","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		ss[i]=sh[i]=sl[i]=i;
	for (int i=0;i<n;i++)
	{
		scanf("%d %d",&h[i],&l[i]);
		sum+=h[i];
	}
	sort(ss,ss+n,cmps);
	sort(sl,sl+n,cmpl);
	sort(sh,sh+n,cmph);
	int th;
	scanf("%d",&th);
	for (;iterate(th););
	int kol=0;
	for (int i=0;i<n;i++)
		if (give[i])
			++kol;
	printf("%d\n",kol);
	for (int i=0;i<n;i++)
		if (give[i])
			printf("%d ",i+1);
	pts=pth=ptl=0;		
  return 0;
}