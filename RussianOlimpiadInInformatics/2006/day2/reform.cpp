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
	point(){
		x=y=0;
	}
	point(int X,int Y){
		x=X;
		y=Y;
	}
};

point operator+ (point a,point b){
	return point(a.x+b.x,a.y+b.y);
}

point operator-(point a,point b){
	return point(a.x-b.x,a.y-b.y);
}


point operator*(point a,int b){
	return point(a.x*b,a.y*b);
}

point operator/(point a,int b){
	return point(a.x/b,a.y/b);
}

int64 operator*(point a,point b){
	return a.x*1ll*b.y-a.y*1ll*b.x;
}


struct row;
struct seg;

struct line{
	point p;
	point v;
	line(){
		p=v=point();
	}
	line(point a,point b){
		p=a;
		v=b-a;
	}
	line(const row& r);
	line(const seg& s);
};

struct row{
	point p;
	point v;
	row(){
		p=v=point();
	}
	row(point a,point b){
		p=a;
		v=b-a;
	}
};


struct seg{
	point p;
	point v;
	seg(){
		p=v=point();
	}
	seg(point a,point b){
		p=a;
		v=b-a;
		if (v.y<0)
		{
			p=b;
			v=a-b;
		}
	}
};

line::line(const row& r){
	p=r.p;
	v=r.v;
};


line::line(const seg& s){
	p=s.p;
	v=s.v;
};

int64 opr(int64 a00,int64 a01,int64 a10,int64 a11){
	return a00*a11-a10*a01;
}

bool intersec(const line& a,const line &b,ld &t1,ld &t2){
	int64 d1=opr(a.v.x,-b.v.x,a.v.y,-b.v.y);
	if (d1==0)
		return false;
	int64 d2=opr(b.p.x-a.p.x,-b.v.x,b.p.y-a.p.y,-b.v.y);
	int64 d3=opr(a.v.x,b.p.x-a.p.x,a.v.y,b.p.y-a.p.y);
	t1=d2*1.0/d1;
	t2=d3*1.0/d1;
	return true;	
}

const ld eps=1E-09;

bool intersec(const row& a,const seg& b){
	if (b.v.y==0)
		return false;
	ld t1,t2;
	intersec(line(a),line(b),t1,t2);
	return (t1>eps) && (t2>-eps) && (t2<1-eps);
}

bool intersec(const seg& a,const seg& b){
	if (a.v*b.v==0){
		if (a.v.x!=0){
			int l=max(min(a.p.x,a.p.x+a.v.x),min(b.p.x,b.p.x+b.v.x));
			int r=min(max(a.p.x,a.p.x+a.v.x),max(b.p.x,b.p.x+b.v.x));
			return l<r;
		}
		int l=max(min(a.p.y,a.p.y+a.v.y),min(b.p.y,b.p.y+b.v.y));
		int r=min(max(a.p.y,a.p.y+a.v.y),max(b.p.y,b.p.y+b.v.y));
		return l<r;
		
	}
	ld t1,t2;
	intersec(line(a),line(b),t1,t2);
	return (t2>eps) && (t2<1-eps) && (t2>eps) && (t2<1-eps);	
}

typedef vector<point> polygon;

bool check(const point& a,const seg &b){
	point v=a-b.p;
	if (v*b.v!=0)
		return false;
	point v1=a-(b.p+b.v);
	return v1.x*v.x+v1.y*v.y<=0;
}

bool check(const point& a,const polygon& b){
	row r(a,a+point(1,0));
	int n=b.size();
	int k=0;
	for (int i=0;i<n;i++)
		if (intersec(r,seg(b[i],b[(i+1)%n])))
			k++;
	for (int i=0;i<n;i++)
		if (check(a,seg(b[i],b[(i+1)%n])))
			return false;
	return k&1;	
}

bool check(const seg& a,const polygon& b){
	point p;
	p=a.p+a.v/2;
	if (!check(p,b))		
		return false;
	int n=b.size();
	for (int i=0;i<n;i++)
		if (intersec(a,seg(b[i],b[(i+1)%n])))
			return false;
	return true;
}

void norm(polygon &a){
	int n=a.size();
	for (int i=0;i<n;i++){
		if ((a[i]-a[(i+n-1)%n])*(a[(i+1)%n]-a[i])==0)
			{
				a.erase(a.begin()+i);
				--n;
				--i;
			}			
	}
}

bool oneline(const seg& a,const seg& b){
	if (a.v*b.v!=0)
		return false;
	point p1=a.p;
	point p2=a.p+a.v;
	point p3=b.p;
	line l1(p1,p2);
	line l2(p1,p3);
	if (l1.v*l2.v!=0)
		return false;
	return true;
}

void triangulate(polygon a,vector<seg> &ans){
	norm(a);
	int n=a.size();
	if (n==3)
		return;
	for (int i=0;i<n;i++)
		for (int j=i+2;j<n;j++)
			if (check(seg(a[i],a[j]),a))
				{
					bool q=false;
					for (int di=-1;di<2;di+=2)
						for (int dj=-1;dj<2;dj+=2)
							if ((j+dj+n)%n!=i || (i+di+n)%n!=j)
								q|=oneline(seg(a[i],a[(i+di+n)%n]),seg(a[j],a[(j+dj+n)%n]));
					if (q)
					{
						ans.pb(seg(a[i],a[j]));
						polygon p1;
						for (int k=i;k<=j;k++)
							p1.pb(a[k]);
						polygon p2;
						for (int k=0;k<=i;k++)
							p2.pb(a[k]);
						for (int k=j;k<n;k++)
							p2.pb(a[k]);
						triangulate(p1,ans);
						triangulate(p2,ans);
						return;
					}
				}
	while( n>3){
		for (int i=0;i<n;i++)
			if (check(seg(a[i],a[(i+2)%n]),a))
			{
				ans.pb(seg(a[i],a[(i+2)%n]));
				a.erase(a.begin()+(i+1)%n);
				--n;
				break;
			}
	}
	return;
}

int main()
{
  freopen("reform.in","r",stdin);
  freopen("reform.out","w",stdout);
  int n;
  scanf("%d",&n);
  polygon a(n);
  for (int i=0;i<n;i++)
  {
	 scanf("%d %d",&a[i].x,&a[i].y);
	 a[i].x*=2;
	 a[i].y*=2;
  }
  vector<seg> ans;
  triangulate(a,ans);
  printf("%d\n%d\n",ans.size()+1,ans.size());
  for (int i=0;i<ans.size();i++)
	printf("%d %d %d %d\n",ans[i].p.x/2,ans[i].p.y/2,(ans[i].p.x+ans[i].v.x)/2,(ans[i].p.y+ans[i].v.y)/2);
  return 0;
}