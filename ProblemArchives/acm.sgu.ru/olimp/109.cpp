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

struct line;
struct seg;

const ld eps=1E-09;

struct point{
	ld x,y;
	point()
	{
		x=y=0;
	}
	point (ld _x, ld _y)
	{
		x=_x;
		y=_y;
	}                  
	int pointgen(line a,line b);   
};

istream& operator>> (istream& is,point& p)
{
	is>>p.x>>p.y;
	return is;
}

ostream& operator<< (ostream& is,point& p)
{
	is<<fixed;
	is.precision(15);
	is<<p.x<<" "<<p.y<<endl;;
	return is;
}

bool operator<(point a,point b)
{
	return (a.x-b.x>eps) || (abs(a.x-b.x)<eps && (a.y-b.y>eps));
}

bool operator==(point a,point b)
{
	return abs(a.x-b.x)<eps && abs(a.y-b.y)<eps;
}


struct line{
	ld a, b, c;
	line (ld _a,ld _b,ld _c)
	{
		a=_a;
		b=_b;
		c=_c;
	}
	line(point X,point Y)
	{
		 a=Y.y-X.y;
		 b=X.x-Y.x;
		 c=-a*X.x-b*X.y;
	}
	line(seg S);
};

struct seg{
	point p1,p2;
	seg(point _p1,point _p2)
	{
		p1=_p1;
		p2=_p2;
	}
} ;

line::line(seg S)
{
	*this=line(S.p1,S.p2);
}

int point::pointgen(line a,line b)
{
	ld d=a.a*b.b-a.b*b.a;
//	cerr<<d<<endl;
	if (abs(d)<eps)
	{
		y=x=(1.0/0)-(1.0/0);
		if ((abs(a.a*b.c-a.c*b.a)<eps)   && (abs(a.b*b.c-a.c*b.b)<eps)) 
			return 2;
		else
			return 0;
	}
	x=-(b.b*a.c-b.c*a.b)/d;
	y=-(a.a*b.c-a.c*b.a)/d;
	return 1;
}

vector<point> points;

void interseq(seg S1,seg S2)
{
	line l1(S1);
	line l2(S2);     
	point p;
	int r=p.pointgen(l1,l2);
//	cerr<<r<<endl;     
	if (r==0)
		return;
	if (r==2)
	{
		seg S3(point(0,0),point(0,0));
		S3.p1.x=max(min(S1.p1.x,S1.p2.x),min(S2.p1.x,S2.p2.x));
		S3.p2.x=min(max(S1.p1.x,S1.p2.x),max(S2.p1.x,S2.p2.x));
		S3.p1.y=max(min(S1.p1.y,S1.p2.y),min(S2.p1.y,S2.p2.y));
		S3.p2.y=min(max(S1.p1.y,S1.p2.y),max(S2.p1.y,S2.p2.y));
		if (S3.p1==S3.p2)
		{
			points.pb(S3.p1);
			return;
		}
		if ((S3.p1.x<S3.p2.x) && (S3.p1.y<S3.p2.y))
			{        
				cout<<"-1"<<endl;
				exit(0);
			}
		return;
	}
//	cerr<<p;
	if (p.x<min(S1.p1.x,S1.p2.x)-eps)
		return;
	if (p.x>max(S1.p1.x,S1.p2.x)+eps)
		return;
	if (p.x<min(S2.p1.x,S2.p2.x)-eps)
		return;
	if (p.x>max(S2.p1.x,S2.p2.x)+eps)
		return;
	if (p.y<min(S1.p1.y,S1.p2.y)-eps)
		return;
	if (p.y>max(S1.p1.y,S1.p2.y)+eps)
		return;
	if (p.y<min(S2.p1.y,S2.p2.y)-eps)
		return;
	if (p.y>max(S2.p1.y,S2.p2.y)+eps)
		return;
	points.pb(p);
	return;
}

      

int main()
{
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  point p1,p2,p3;
  point P1,P2,P3;
  cin>>p1>>p2>>p3>>P1>>P2>>P3;
  interseq(seg(p1,p2),seg(P1,P2));
  interseq(seg(p1,p2),seg(P1,P3));
  interseq(seg(p1,p2),seg(P2,P3));
  interseq(seg(p1,p3),seg(P1,P2));
  interseq(seg(p1,p3),seg(P1,P3));
  interseq(seg(p1,p3),seg(P2,P3));
  interseq(seg(p2,p3),seg(P1,P2));
  interseq(seg(p2,p3),seg(P1,P3));
  interseq(seg(p2,p3),seg(P2,P3));
  sort(points.begin(),points.end());
  points.erase(unique(points.begin(),points.end()),points.end());
  if (points.size()>=10)
  	{
  		cout<<-1<<endl;
  		return 0;
  	}
  cout<<points.size();
  return 0;
}