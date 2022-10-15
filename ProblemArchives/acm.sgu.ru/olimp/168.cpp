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
#define fileinout
using namespace std;

struct point{
  int x, y;
  point(int _x=0,int _y=0)
  {
    x=_x;
    y=_y;
  }
};

point operator+(point a,point b)
{
  return point(a.x+b.x,a.y+b.y);
}

point operator-(point a,point b)
{
  return point(a.x-b.x,a.y-b.y);
}

struct ray{
  point a, b;
  ray(point _a,point _b){
    a=_a;
    b=_b;
  }
  pair<bool,ld> getx(int y)
  {
    int A=b.y-a.y;
    int B=a.x-b.x;
    int C=-a.x*A-a.y*B;
    //cerr<<A<<" "<<B<<" "<<C<<endl;
    ld res=((ld)(-C-B*y))/A;
    if ((b.x-a.x)*(res-a.x)>0)
      return mp(true,res);
    else
      return mp(false,res);
  }
  pair<bool,ld> gety(int x)
  {
    int A=b.y-a.y;
    int B=a.x-b.x;
    int C=-a.x*A-a.y*B;
    ld res=((ld)(-C-A*x))/B;
    if ((b.y-a.y)*1ll*(res-a.y)>0)
      return mp(true,res);
    else
      return mp(false,res);
  }
  bool on(point p)
  { int A=b.y-a.y;
    int B=a.x-b.x;
    int C=-a.x*A-a.y*B;
    if (A*1ll*p.x+B*1ll*p.y+C==0)
      if ((p.x-a.x)*1ll*(b.x-a.x)>0)
        return true;
    return false;
  }
};


int main()
{
  //#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
//  #endif
  int n,m;
  scanf("%d %d",&n,&m);
  point st;
  scanf("%d %d",&st.x,&st.y);
  for (int x1=-2*n;x1<=3*n;x1+=5*n)
    for (int y1=-2*m;y1<=3*m;y1+=5*m)
    {                         
      point to=point(x1,y1);
      //cerr<<x1<<" "<<y1<<endl;
      ray r(st,to);     
      bool q=true;
      for (int x2=-2*n;x2<=3*n && q;x2+=n)
        for (int y2=-2*m;y2<=3*m && q;y2+=m)
          if (x2!=x1 || y2!=y1)
            if (r.on(point(x2,y2)))
              q=false;
      if (q==true)
      {
        // cerr<<"!"<<endl;
         printf("YES\n");
         pair<bool,ld> ttmp=r.gety(n);
         cout<<fixed;
         cout.precision(7);
         if (ttmp.first)
         {
           ld tmp=ttmp.second;
           if ((x1>0) && (tmp<m) && (tmp>0))
           {                                      
              cout<<n<<" "<<tmp<<endl;
              return 0;
           }
         }              
         ttmp=r.gety(0);
         if (ttmp.first)
         {
           ld tmp=ttmp.second;
           if ((x1<0) && (tmp<m) && (tmp>0))
           {
              cout<<0<<" "<<tmp<<endl;
              return 0;
           }
         }
         ttmp=r.getx(m);
         if (ttmp.first)
         {                                         
           ld tmp=ttmp.second;         
           if ((y1>0) && (tmp<n) && (tmp>0))
           {
              cout<<tmp<<" "<<m<<endl;          
              return 0;    
           }
         }
         ttmp=r.getx(0);
         if (ttmp.first)
         {
           ld tmp=ttmp.second;
           if ((y1<0) && (tmp<n) && (tmp>0))
           {                                    
              cout<<tmp<<" "<<0<<endl;
              return 0;
           }                         
         }
        assert(false); 
      } 
    }
  printf("NO\n");
  return 0;
}