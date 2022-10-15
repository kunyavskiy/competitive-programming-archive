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

struct point{
	int x,y;
	point(){x=y=0;};
	point(int X,int Y){
		x=X;
		y=Y;
	}
};

struct dpoint{
	ld x,y;
	dpoint(){x=y=0;};
	dpoint(ld X,ld Y){
		x=X;
		y=Y;
	}
	dpoint(const point& a){
		x=a.x;
		y=a.y;
	}
};

enum evtype {_ver,_seg};

int64 operator*(const point& a,const point& b){
	return a.x*1ll*b.y-a.y*1ll*b.x;
}

ld dest(const dpoint& a,const dpoint& b)
{
	return sqrtl((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

struct event{
	point p;
	evtype type;
	int num;
	event(){p=point(),type=_seg,num=-1000;};
	event (point P,evtype t,int Num)
	{
		p=P;
		type=t;
		num=Num;
	}
};

bool operator<(const event& a,const event& b){
	int64 vp=a.p*b.p;
	if (vp!=0)
		return vp>0;
	if (a.p.x!=0)
		return abs(a.p.x)<abs(b.p.x);
	return abs(a.p.y)<abs(b.p.y);
}

bool ypred(const event& a){
	return a.p.y>0 || (a.p.y==0 && a.p.x>0);
}

vector<event> evs;
vector<point> mn;
bool used[100000];
int n;

dpoint intersec(const point& p1,int num){
	int64 a1=p1.y;
	int64 b1=-p1.x;
	int64 c1=0;
	int64 a2=mn[num].y-mn[(num+1)%n].y;
	int64 b2=-mn[num].x+mn[(num+1)%n].x;
	int64 c2=-a2*mn[num].x-b2*mn[num].y;
	assert(a1*b2-b1*a2!=0);
	dpoint res;
	res.x=-(c1*b2-c2*b1)*1.0/(a1*b2-a2*b1);
	res.y=-(a1*c2-a2*c1)*1.0/(a1*b2-a2*b1);
	return res;
}


int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int m;
  scanf("%d %d",&n,&m);
  mn.resize(n);
  for (int i=0;i<n;i++)
  {
		scanf("%d %d",&mn[i].x,&mn[i].y);
		evs.pb(event(mn[i],_ver,i));
	}
	if (mn[0]*mn[1]<0)
		reverse(mn.begin(),mn.end());
	int kol=0;
	for (int i=0;i<m;i++)
	{
		event tmp;
		scanf("%d %d",&tmp.p.x,&tmp.p.y);
		tmp.type=_seg;
		tmp.num=i;
		event tmp1=tmp;
		scanf("%d %d",&tmp1.p.x,&tmp1.p.y);
		if (tmp1.p*tmp.p==0)
		{
			--i,--m;
			continue;		
		}
		evs.pb(tmp);
		evs.pb(tmp1);
		if (tmp1.p.y*1ll*tmp.p.y>0){
			used[i]=false;
			continue;
		}
		if (tmp1.p.y==0){
				used[i]=(tmp1.p.x>0) && tmp.p.y<0;
				kol+=used[i];
				continue;
		}
		if (tmp.p.y==0){
				used[i]=(tmp.p.x>0) && tmp1.p.y<0;
				kol+=used[i];
				continue;
		}
		int64 a=tmp.p.y-tmp1.p.y;
		int64 b=tmp1.p.x-tmp.p.x;
		int64 c=a*tmp.p.x+b*tmp.p.y;
		used[i]=(c>0 && a>0) || (c<0 && a<0);
		kol+=used[i];	
	}
	ld ans=0;
	dpoint start;
	int ver=-1;
	for (int i=0;i<n;i++)
		if (mn[i].y>0 || (mn[i].y==0 && mn[i].x>0)){
			if (ver==-1 || mn[i]*mn[ver]>0)
				ver=i;
		}
	if (ver==0)
		rotate(mn.begin(),mn.begin()+n-1,mn.end());
	else
		rotate(mn.begin(),mn.begin()+ver-1,mn.end());
	ver=0;
	start=intersec(point(1,0),0);
	vector<event>::iterator iter=partition(evs.begin(),evs.end(),ypred);
	sort(evs.begin(),iter);
	sort(iter,evs.end());
	dpoint gstart=start;
	for (int i=0;i<n+2*m;i++){
		if (evs[i].type==_ver){
			ver++;
			ver%=n;
			if (kol==0)
				ans+=dest(start,mn[ver%n]);
			start=mn[ver%n];
			continue;
		}
		int num=evs[i].num;
		if (used[num]){
			kol--;
			if (kol==0)
				start=intersec(evs[i].p,ver);
			used[num]=false;
			continue;
		}
		if (kol==0)
			ans+=dest(start,intersec(evs[i].p,ver));
		kol++;
		used[num]=true;
	}
	if (kol==0)
		ans+=dest(start,gstart);		
	ld len=0;
	for (int i=0;i<n;i++)
		len+=dest(mn[i],mn[(i+1)%n]);
	ans=len-ans;
	cout<<fixed;
	cout.precision(15);
	cout<<ans<<endl;
  return 0;
}