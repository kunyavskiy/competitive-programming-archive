#include <iostream>
#include <cassert>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <memory.h>

#define pb push_back
#define mp make_pair

#define sqr(x) ((x)*(x))

using namespace std;

typedef long long int64;
typedef double ld;

const ld eps=1e-9;

int n;       


struct point{
  int x,y;
  point(int X,int Y){
     x=X;y=Y;                                                                          
  }
  point(){};
};

inline ld dist (const point& a,const point& b){
  return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y)+.0);
}

inline point operator-(const point& a,const point& b){
  return point(a.x-b.x,a.y-b.y);
}

struct seg{
  point p1,p2;                  
  seg(const point& P1,const point& P2){
    p1=P1;p2=P2;
  }
};

struct line{
  ld a,b,c;
  void norm(){
    ld nc=sqrt(a*a+b*b);
    a/=nc;
    b/=nc;
    c/=nc;
  }
  line(const point& p1,const point& p2){
     a=p1.y-p2.y;
     b=p2.x-p1.x;
     c=-a*p1.x-b*p1.y;
     norm();                            
  }
  line(const seg& s){
     a=s.p1.y-s.p2.y;
     b=s.p2.x-s.p1.x;
     c=-a*s.p1.x-b*s.p1.y;
     norm();                            
  }
};

inline int scal(const point& a,const point& b){
  return a.x*b.x+a.y*b.y;
}

inline int vect(const point& a,const point& b){
  return a.x*b.y-a.y*b.x;
}

inline ld dist(const line& a,const point& b){
  return a.a*b.x+a.b*b.y+a.c;
}
                         
inline ld dist(const seg &a,const point& b){
  if (scal(a.p2-a.p1,b-a.p1)>=0 && scal(a.p1-a.p2,b-a.p2)>=0)
     return abs(dist(line(a),b));
  return min(dist(b,a.p1),dist(b,a.p2));
} 

inline int sgn(ld a){
  if (a>eps)
    return 1;
  if (a<-eps)
    return -1;
  return 0;
}

bool interseced(const seg& a,const seg& b){
  line l1(a);
  line l2(b);
  if (sgn(dist(l2,a.p1))*sgn(dist(l2,a.p2)) >= 0)
    return false;
  if (sgn(dist(l1,b.p1))*sgn(dist(l1,b.p2)) >= 0)
    return false;
  return true;  
}

ld dist(const seg& a,const seg& b){
  if (interseced(a,b))
    return 0; 
  ld res=min(dist(b,a.p1),dist(b,a.p2));
  res=min(res,dist(a,b.p1));
  res=min(res,dist(a,b.p2));
  return res;
}

typedef vector<seg> polygon;

bool inside(const polygon& a,const point& b){
  /*seg s(b,point(23917,54387));
  int kol=0;
  int sz=a.size();
  for (int i=0;i<sz;i++){
    line l1(s);
    line l2(a[i]);
    if (interseced(a[i],s))
      kol++;
  }
  return kol%2;                   */
  int s1=0,s2=0;
  int sz=a.size();
  for (int i=0;i<sz;i++)
    s1+=vect(a[i].p1,a[i].p2);
  s1=abs(s1);
  for (int i=0;i<sz;i++)
    s2+=abs(vect(a[i].p1-b,a[i].p2-b));
  return s1==s2;
} 

ld dist (const point& a,const polygon& b){
  if (inside(b,a))
    return 0;
  int sz=b.size();
  ld dst=1e+100;
  for (int i=0;i<sz;i++)
    dst=min(dst,dist(b[i],a));
  return dst;
}
                                                             
ld dist (const polygon& a,const polygon& b){
  ld ans=1e+100;
  int sz1=a.size();
  int sz2=b.size();
  if (inside(b,a[0].p1) || inside(b,a[0].p2))
    return 0;
  if (inside(a,b[0].p1) || inside(a,b[0].p2))
    return 0;                        
//  for (int iter=0;iter<2;iter++){           
    int ptr1,ptr2;
    ptr1=ptr2=0;
    for (;ptr1<sz1;ptr1++){                                                                               
       for (int it=0;dist(b[ptr2],a[ptr1]) > dist(b[(ptr2+1)%sz2],a[ptr1])+eps && it<sz2;ptr2=(ptr2+1)%sz2,it++);                                           
       for (int it=0;dist(b[ptr2],a[ptr1]) > dist(b[(ptr2+sz2-1)%sz2],a[ptr1])+eps && it<sz2;ptr2=(ptr2+sz2-1)%sz2,it++);
       ans=min(ans,dist(b[ptr2],a[ptr1]));
    }                                                   
  //  swap(a,b);
  //  swap(sz1,sz2);
  //}           
  return ans;                                      
}

void read(polygon& v){
  int n;
  scanf("%d",&n);
  vector<point> vtmp;
  for (int i=0;i<n;i++){
    int x,y;
    scanf("%d %d",&x,&y);
    vtmp.pb(point(x,y));
  }
  for (int i=0;i<n;i++)
    v.pb(seg(vtmp[i],vtmp[(i+1)%n]));
}

ld g[110][110];

polygon p[110];
int start,finish;
                
void gengraf(){
  scanf("%d",&n);
  scanf("%d %d",&start,&finish);
  for (int i=1;i<=n;i++)
    read(p[i]);
  point st,en;

  for (int i=1;i<=n;i++){
    g[0][i]=g[i][0]=dist(st,p[i]);
    g[i][n+1]=g[n+1][i]=dist(en,p[i]);                           
  }
//  cerr<<"!!!!"<<endl;
  for (int i=1;i<=n;i++)
    for (int j=i+1;j<=n;j++){
      g[i][j]=g[j][i]=dist(p[i],p[j]);
      //cerr<<i<<" "<<j<<endl;
    }
 // cerr<<"!!!!"<<endl;
  n+=2;
  for (int i=0;i<n;i++)
    g[i][i]=0;
  g[0][n-1]=g[n-1][0]=dist(st,en);
}

ld d[110];
bool used[110];

ld dijkstra(){
  for (int i=0;i<n;i++)
    d[i]=1e+100;
  d[start]=0;
  for (int i=0;i<n;i++){
    int best=-1;
    for (int j=0;j<n;j++)
      if (!used[j])
        if (best==-1 || d[best]>d[j])
          best=j;   
    if (best==-1 || d[best]>1e+50)
      break;
    used[best]=true;
    for (int j=0;j<n;j++)
      if (d[j]>d[best]+g[best][j]){
        d[j]=d[best]+g[best][j];
//        cerr<<j<<" : "<<d[j]<<" From "<<best<<endl;
      }
  }
  return d[finish];
}

void clean(){
	memset(d,0,sizeof(d));
	memset(used,0,sizeof(used));
	memset(g,0,sizeof(g));
	for (int i = 0; i < 100; i++)
		p[i].clear();
}


int main(){
  #ifdef LOCAL
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  #endif
  int t;
  scanf("%d",&t);
  while (t-->0){
    clean();
  	gengraf();
  	cout.precision(10);
  	cout<<fixed<<dijkstra()<<endl;
  }
  return 0;
}
            