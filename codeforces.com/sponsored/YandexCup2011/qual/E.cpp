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
#include <stack>
#define mp make_pair
#define pb push_back                     
                                                                       
using namespace std;

typedef long long int64;
typedef double ld;

struct point;
struct pol;
struct triangle;
struct line;
struct seg;
struct pointonpol;


const ld eps=1E-09;

inline bool between(ld a,ld b,ld c)
{
 return a>=min(b,c)-eps && a<=max(b,c)+eps; 
}

struct point
{
  ld x, y;
  point (ld _x=0,ld _y=0)
    {
      x=_x;
      y=_y;
    }
};
      
struct pol{
  ld lx, rx;
  pol(ld _lx=0,ld _rx=0)
  {
     lx=_lx;
     rx=_rx;
  }
  inline ld width()
  {
    return rx-lx;
  }
};

struct triangle{
  point a,b,c;
  triangle (point _a=point(),point _b=point(),point _c=point())
  {
    a=_a;
    b=_b;
    c=_c;
  }
};

struct seg{
  point a, b;
  seg (point _a=point(),point _b=point())
  {
    a=_a;
    b=_b;
  }
  inline point middle()
  {
    return point ((a.x+b.x)/2,(a.y+b.y)/2);
  }
  ld left()
  {
    return min(a.x,b.x);
  } 
  ld right()
  {
    return max(a.x,b.x);
  }
};

struct line{
  ld a,b,c;
  line (ld _a=0,ld _b=0,ld _c=0)
  {
    a=_a;
    b=_b;
    c=_c;
  }
  line (point x,point y)
  {
    a=x.y-y.y;
    b=y.x-x.x;
    c=-a*x.x-b*x.y;
  }
  line (seg a)
  {
    *this=line(a.a,a.b);
  }
  inline ld y(ld x)
  {          
    return (-(a*x+c)/b);
  }

};


struct pointonpol{
  ld y;
  bool start;
  pointonpol(ld _y=0,bool _start=false)
  {
    y=_y;
    start=_start;
  }
};
           
bool operator< (pointonpol a,pointonpol b)
{
  return a.y<b.y;
}

bool operator<(point a,point b)
{
  return a.x<b.x;
}


vector<triangle> ts;
vector<point> is;

inline pair<bool,pointonpol> interseq(pol a,seg b)
{
  if (!between(a.lx,b.left(),b.right()))
    return mp(false,pointonpol());         
  if (!between(a.rx,b.left(),b.right()))
    return mp(false,pointonpol());
      
  line s(b);                                         
  if (abs(s.b)<eps)
    return mp(false,pointonpol());                   
  return mp(true,pointonpol(s.y((a.lx+a.rx)/2)));
}

inline vector<pointonpol> interseq(pol a)
{
  vector<pointonpol> res;
  int sz=ts.size();
  for (int i=0;i<sz;i++)
  {
    int kol=0;
    pair<bool,pointonpol> p;
    p=interseq(a,seg(ts[i].a,ts[i].b));
    if (p.first)
      {
        kol++;
        res.pb(p.second);
      }
    p=interseq(a,seg(ts[i].c,ts[i].b));
    if (p.first)
      {
        kol++;
        res.pb(p.second);
      }     
    p=interseq(a,seg(ts[i].a,ts[i].c));
    if (p.first)
      {
        kol++;
        res.pb(p.second);
      }
    //assert(kol==0 || kol==2);
    if (kol==2)
      if (res[res.size()-1].y<res[res.size()-2].y+eps)
        res[res.size()-1].start=true;
      else
        res[res.size()-2].start=true;
  }            
  sort(res.begin(),res.end());
  return res;
}

inline ld len(vector<pointonpol> a)
{   
  int kol=0;
  ld l;
  ld res=0;
  int sz=a.size();
  for (int i=0;i<sz;i++)
    {
      if (kol==0)
        l=a[i].y;
      if (a[i].start)
        kol++;
      else
        kol--;
      //assert(kol>=0);
      if (kol==0)
        res+=a[i].y-l;
    }
 return res;
}

inline void interseq(seg a,seg b)
{
  line l1(a),l2(b);
  ld d=l1.a*l2.b-l2.a*l1.b;
  if (abs(d)<eps)
    return;
  point p((l2.c*l1.b-l1.c*l2.b)/d,(-l2.c*l1.a+l1.c*l2.a)/d);
  if (!between(p.x,a.a.x,a.b.x))
    return;
  if (!between(p.x,b.a.x,b.b.x))
    return;
  if (!between(p.y,a.a.y,a.b.y))
    return;
  if (!between(p.y,b.a.y,b.b.y))
    return;                                                 
  is.pb(p);
  return;
}

bool operator==(point a,point b)
{
  return (abs(a.x-b.x)<eps && abs(a.y-b.y)<eps);
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  
  int n,h,f;
  cin>>n>>h>>f;
  
  for (int i=0;i<n;i++){
  	ld l,r;
  	cin>>l>>r;
  	ld l1,r1;
  	l1 = l * (f+h)/(f-h);
  	r1 = r * (f+h)/(f-h);
  	ts.pb(triangle(point(-h,l),point(-h,r),point(h,l1)));
  	ts.pb(triangle(point(-h,r),point(h,l1),point(h,r1)));
  	ts.pb(triangle(point(h,l),point(h,r),point(-h,l1)));
  	ts.pb(triangle(point(h,r),point(-h,l1),point(-h,r1)));
  }

	n*=4; 
  
  
  for (int i=0;i<n;i++)
  {
    is.pb(ts[i].a);
    is.pb(ts[i].b);
    is.pb(ts[i].c);
    for (int j=i+1;j<n;j++)
    {
      interseq(seg(ts[i].a,ts[i].b),seg(ts[j].a,ts[j].b));
      interseq(seg(ts[i].a,ts[i].b),seg(ts[j].b,ts[j].c));
      interseq(seg(ts[i].a,ts[i].b),seg(ts[j].c,ts[j].a));
      interseq(seg(ts[i].b,ts[i].c),seg(ts[j].a,ts[j].b)); 
      interseq(seg(ts[i].b,ts[i].c),seg(ts[j].b,ts[j].c));
      interseq(seg(ts[i].b,ts[i].c),seg(ts[j].c,ts[j].a));
      interseq(seg(ts[i].c,ts[i].a),seg(ts[j].a,ts[j].b));
      interseq(seg(ts[i].c,ts[i].a),seg(ts[j].b,ts[j].c));
      interseq(seg(ts[i].c,ts[i].a),seg(ts[j].c,ts[j].a));
    }
  }
  sort(is.begin(),is.end());              
  vector<point>::iterator iter;
  iter=unique(is.begin(),is.end());
  is.resize(iter-is.begin());
  ld res=0;
  int sz=is.size();
  for (int i=1;i<sz;i++)
    {
      pol p(is[i-1].x,is[i].x);
      if (abs(p.width())<1E-13)
         continue;
      res=res+len(interseq(p))*p.width();
    }                     
  printf("%.10lf",res);
  return 0;
}