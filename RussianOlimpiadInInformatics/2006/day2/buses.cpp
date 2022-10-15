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

int d[200000];
int ed[200000];
int ea[200000];

struct event{
	int time;
	int num;
	int type;
	event(){time=num=type=0;};
	event(int t,int n,int Type){
		time=t;
		num=n;
		type=Type;
	}
};

event evs[400000];

void readtime(int &a){
	string s;
	cin>>s;
	int h,m;
	sscanf(s.data(),"%d:%d",&h,&m);
	a=h*60+m;
}

bool operator<(const event& a,const event& b){
	if (a.time!=b.time)
		return a.time<b.time;
	if (a.type!=b.type)
		return a.type==1;
	return a.num<b.num;
}

int main()
{
  freopen("buses.in","r",stdin);
  freopen("buses.out","w",stdout);
  int n,m;
  scanf("%d %d",&n,&m);
  int k=0;
  for (int i=0;i<m;i++)
  {
  	event tmp,tmp1;  	
  	scanf("%d",&tmp.num);
  	--tmp.num;
  	readtime(tmp.time);
  	scanf("%d",&tmp1.num);
  	--tmp1.num;
  	tmp.type=-1;
  	tmp1.type=1;
  	readtime(tmp1.time);
  	evs[k++]=tmp;
  	evs[k++]=tmp1;
  	if (tmp1.time<tmp.time){
		  event per1,per2;
	  	per1.time=0;
		  per2.time=23*60+59;
		  per1.type=-1;
	  	per2.type=1;
	  	per1.num=per2.num=tmp.num+n;
	  	evs[k++]=per1;
	  	evs[k++]=per2;
	  }
  }
  n=2*n;
  sort(evs,evs+k);
	for (int i=0;i<k;i++)
		{
			ed[evs[i].num]+=evs[i].type;
			d[evs[i].num]=min(d[evs[i].num],ed[evs[i].num]);
			ea[evs[i].num]+=evs[i].type;
			ea[evs[i].num]=max(ea[evs[i].num],0);
		}
	int kol=0;
	for (int i=0;i<n;i++)
	{
		if (ea[i]<-d[i])
			{
				printf("-1");
				return 0;
			}
		else
			kol+=-d[i];
	}
	printf("%d",kol);
  return 0;
}