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

struct event{
	int64 x;
	int type;
	int64 yl,yr;
	int num;
	event(int64 X,int64 Yl,int64 Yr,int Num,int Type){
		x=X;
		yl=Yl;
		yr=Yr;
		type=Type;
		num=Num;
	}
	event(){
		x=yl=type=yr=num=0;
	}
};


bool operator<(const event& a,const event& b){
	if (a.x!=b.x)
		return a.x<b.x;
	if (a.type!=b.type)
		return a.type<b.type;
	return false;
}

event evs[310000];
int64 ys[310000];


int ans[100100];

int fen[500100];
int n,ysz;

int sum(int r){
	int ans=0;
	for (;r!=-1;r=(r&(r+1))-1)
		ans+=fen[r];
	return ans;
}

int sum(int l,int r){
	return sum(r)-sum(l-1);
}

void update(int l,int d){
	for (;l<=ysz;l=(l|(l+1)))
		fen[l]+=d;
}


int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
 	int k;
  scanf("%d %d",&n,&k);
  k++;
  for (int i=0;i<n;i++){
  	int X,Y,w;
  	int64 x,y;
  	scanf("%d %d %d",&X,&Y,&w);
  	x=X+Y;
  	y=X-Y;
  	evs[i*3]=event(x,y,y,i,0);
  	evs[i*3+1]=event(x-w,y-w,y+w,i,-1);
  	evs[i*3+2]=event(x+w,y-w,y+w,i,1);
  	ys[i*3]=y;
  	ys[i*3+1]=y-w;
  	ys[i*3+2]=y+w;
  }
  sort(evs,evs+3*n);
	sort(ys,ys+3*n);
	ysz=unique(ys,ys+3*n)-ys;
	for (int i=0;i<3*n;i++)
		{
			int64* tmp=lower_bound(ys,ys+ysz,evs[i].yl);
3			evs[i].yl=tmp-ys;
			tmp=lower_bound(ys,ys+ysz,evs[i].yr);
			evs[i].yr=tmp-ys;			
		}

	for (int i=0;i<3*n;i++){
		if (evs[i].type==0)
			ans[evs[i].num]=sum(evs[i].yl);
		else
		{
			update(evs[i].yl,-evs[i].type);
			update(evs[i].yr+1,evs[i].type);
		}
	}
	
	int kol=0;
	for (int i=0;i<n;i++){
			if (ans[i]>=k)
				kol++;
		}
	printf("%d\n",kol);
	for (int i=0;i<n;i++)
		if (ans[i]>=k)
			printf("%d ",i+1);
	printf("\n");  
  return 0;
}