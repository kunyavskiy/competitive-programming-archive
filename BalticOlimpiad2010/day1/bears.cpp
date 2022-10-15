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
#define filename "bears"
#define y1 botva
using namespace std;

struct seg{
	int x1,x2,y1,y2;
	void norm(){
		if (x1>x2)
			swap(x1,x2);
		if (y1>y2)
			swap(y1,y2);
	}	
};

seg segs[6000];

bool intersec(seg s,int x1,int y1,int x2,int y2){
	if (s.x1==s.x2){
		if (s.x1<x1 || s.x1>x2)
			return false;
		if (s.y2<y1)
			return false;
		if (s.y1>y2)
			return false;
		if (s.y1>=y1 && s.y2<=y2)
			return false;
		return true;
	}
	if (s.y1<y1 || s.y1>y2)
		return false;
	if (s.x2<x1)
		return false;
	if (s.x1>x2)
		return false;
	if (s.x1>=x1 && s.x2<=x2)
		return false;
	return true;	
}

int x,y;
int n;

bool check(int d){
	int y1;
	int x1=y1=-(d-1);
	int y2;
	int x2=y2=(d-1);
	for (;;){
		bool q=false;
		for (int i=0;i<n;i++)
			if (intersec(segs[i],x1,y1,x2,y2)){
				q=true;
				x1=min(x1,segs[i].x1);
				y1=min(y1,segs[i].y1);
				y2=max(y2,segs[i].y2);
				x2=max(x2,segs[i].x2);
			}
		if (!q)
			break;
	}
	return (x<x1) || (x>x2) || (y<y1) || (y>y2);
}

int main()
{
  freopen(filename".in","r",stdin);
  freopen(filename".out","w",stdout);
	scanf("%d %d",&x,&y);
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		scanf("%d %d %d %d",&segs[i].x1,&segs[i].y1,&segs[i].x2,&segs[i].y2);
		segs[i].norm();
	}
	int l=0;
	int r=1000100;
	for (;r-l>1;){
		int m=(r+l)/2;
		if (check(m))
			l=m;
		else
			r=m;
	}  
  cout<<l<<endl;
  return 0;
}