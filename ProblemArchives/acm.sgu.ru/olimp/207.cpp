#include <iostream>
#include <iterator>
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
	point(int X,int Y){
		x=X;y=Y;
	}
	point(){};
};

bool operator==(point a,point b){
	return a.x==b.x && a.y==b.y;
}

struct segment{
	point p1,p2;
	segment(){};
	segment(point A,point B){
		p1=A;p2=B;
	}
};

struct line{
	int a,b,c;
	line(point p1,point p2){
		a=p1.y-p2.y;
		b=p2.x-p1.x;
		c=-a*p1.x-b*p1.y;
	}
	line(segment s){
		a=s.p1.y-s.p2.y;
		b=s.p2.x-s.p1.x;
		c=-a*s.p1.x-b*s.p1.y;		
	}
};

int operator*(line a,point b){
	return a.a*b.x+a.b*b.y+a.c;
}

bool intersec(segment a,segment b){
	line l1(a);
	line l2(b);
	if (l1.a*l2.b==l1.b*l2.a){
		if (l1.a*l2.c==l1.c*l2.a && l1.b*l2.c==l1.c*l2.b){
			int lx=max(min(a.p1.x,a.p2.x),min(b.p1.x,b.p2.x));
			int rx=min(max(a.p1.x,a.p2.x),max(b.p1.x,b.p2.x));
			int ly=max(min(a.p1.y,a.p2.y),min(b.p1.y,b.p2.y));
			int ry=min(max(a.p1.y,a.p2.y),max(b.p1.y,b.p2.y));
			if (lx<rx && ly<=ry)
				return true;
			if (lx<=rx && ly<ry)
				return true;
			return false;
		}
		return false;
	}
	int64 d1=(l2*a.p1)*1LL*(l2*a.p2);
	int64 d2=(l1*b.p1)*1LL*(l1*b.p2);
	if (d1<0 && d2<=0)
		return true;
	if (d1<=0 && d2<0)
		return true;
	return false;
}

point p[15];
int per[100];
bool used[100];
int n;
int ans;

bool check(int ptr,segment s){
	for (int i=0;i<ptr;i++)
		if (intersec(s,segment(p[per[i]],p[per[i+1]])))
			return false;
	return true;
}

void perebor(int ptr){
//	for (int i=0;i<ptr;i++)
//		fprintf(stderr,"(%d,%d)%c",p[per[i]].x,p[per[i]].y," \n"[i==ptr-1]);
	if (ptr==n)
		{	
			if (check(ptr-1,segment(p[per[ptr-1]],p[0]))){
				ans+=per[1]<per[ptr-1];
//				cerr<<"!!!"<<endl;
			}
			return;
		}
	for (int i=0;i<n;i++)
		if (!used[i]){
			if (check(ptr-1,segment(p[per[ptr-1]],p[i]))){
				per[ptr]=i;
				used[i]=true;
				perebor(ptr+1);
				used[i]=false;
			}
		}
}


int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		{
			scanf("%d %d",&p[i].x,&p[i].y);
			per[i]=i;
		}
	per[0]=0;
	used[0]=1;
	perebor(1);
	cout<<ans<<endl;
    return 0;
}