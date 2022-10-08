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

const ld eps=1E-6;


struct point{
  ld x,y;
  point (ld _x=0,ld _y=0)
  {
    x=_x;
    y=_y;
  }  
};

struct circle{
  int x,y;
  ld r;
  circle (int _x=0,int _y=0,ld _r=0)
  {
    x=_x;
    y=_y;
    r=_r;
  }
  bool in(point a)
  {
  	return r*r-((a.x-x)*(a.x-x)+(a.y-y)*(a.y-y))>-eps;
  }
};

struct line{
  ld a,b,c;
  line (ld _a,ld _b,ld _c)
  {
    a=_a;
    b=_b;
    c=_c;
  }
};

circle operator-(circle a,point b)
{
  a.x-=b.x;
  a.y-=b.y;
  return a;      
}

point operator+(point a,point b)
{
  a.x+=b.x;
  a.y+=b.y;
  return a;
}
           

vector<point> interseq(circle A,line B)
{
  ld r=A.r;
  ld a=B.a;
  ld b=B.b;
  ld c=B.c;
  ld d=(a*a+b*b)*r*r-c*c;
  vector<point> res;
  if (d>eps)
    {
      d=sqrtl(d);
  		ld aabb=a*a+b*b;
      res.pb(point((-a*c+b*d)/(aabb),(-b*c-a*d)/(aabb)));
      res.pb(point((-a*c-b*d)/(aabb),(-b*c+a*d)/(aabb)));
      return res;
    }
  if (fabsl(d)<eps)
    {
      res.pb(point(-a*c/(a*a+b*b),-b*c/(a*a+b*b)));
      return res;
    }
  return res;   
}

vector<point> interseq(circle a,circle b)
{
  vector<point> res;
  res.clear();
  point sdvig(a.x,a.y);
  a=a-sdvig;
  b=b-sdvig;               
  line l(2*b.x,2*b.y,b.r*b.r-b.x*b.x-b.y*b.y-a.r*a.r);
  res=interseq(a,l);
  for (int i=0;i<res.size();i++)
    res[i]=res[i]+sdvig;
  return res;
}

circle a,b,c;

bool check(ld d1,ld d2,ld d3,ld write=false)
{
	a.r=d1;
	b.r=d2;
	c.r=d3;
	if (write);
	vector<point> aaa=interseq(a,b);
	if (write)
		cerr<<aaa.size()<<endl;
	if (aaa.size()==0)
		return false;
	if (!write)
	{	
		if (aaa.size()==1)
			return c.in(aaa[0]);
		if (aaa.size()==2)
			return c.in(aaa[0]) || c.in(aaa[1]);
	}
	else
	{
		if (c.in(aaa[0]))
			{
				cout.precision(7);
				cout<<fixed;
				cout<<aaa[0].x<<" "<<aaa[0].y<<endl;
				return true;
			}
		if (aaa.size()==1)
			return false;
		if (c.in(aaa[1]))
			{
				cout.precision(7);
				cout<<fixed;
				cout<<aaa[1].x<<" "<<aaa[1].y<<endl;
				return true;
			}
		return false;
	}
}



int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int r1,r2,r3;
	scanf("%d %d %d",&a.x,&a.y,&r1);
  scanf("%d %d %d",&b.x,&b.y,&r2);
  scanf("%d %d %d",&c.x,&c.y,&r3);
  ld l=r1;
  ld r=100000.0;
  cerr.precision(15);
  for (;r-l>1E-16;)
  {
  	//cerr<<l<<" "<<r<<endl;
  	ld m=(l+r)/2;
  	if (check(m,m*r2/r1,m*r3/r1))
  		r=m;
  	else
  		l=m;
  }
 	ld m=(l+r)/2;
 	check(m,m*r2/r1,m*r3/r1,true);    
  return 0;
}