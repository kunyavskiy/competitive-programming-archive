#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <iterator>

#define mp make_pair
#define pb push_back
#define sqr(a) ((a) * (a))
#define zero(a) memset (a, 0, sizeof(a))
#define sz(a) (int)(a.size())

#ifdef LOCAL
	#define LLD "%I64d"
#else 
	#define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int uint;

#define taskname "k"

const int inf = 1500000000;
const ld eps = 1e-9;
               
struct point 
{
  int x, y, v;
  point ()
  {
    x=0, y=0, v=0;
  }
  point (int _x, int _y, int _v)
  {
    x=_x, y=_y, v=_v;
  }
}P[270000];

bool cmpx (point f, point s)
{
  if (f.x!=s.x)
    return f.x<s.x;
  return f.y<s.y;
}

bool cmpy (point f, point s)
{
  if (f.y!=s.y)
    return f.y<s.y;
  return f.x<s.x;
}

int e=1;

struct tree 
{
  //vector <point> V;
  bool tp;
  int l, r, xmin, xmax, ymin, ymax, upd, ans;                              
}T[600000];

void build (int v, bool _tp, int lb, int rb)
{
  //cerr<<"?????? "<<v<<" "<<lb<<" "<<rb<<endl;
  int i;
  T[v].l=-1, T[v].r=-1, T[v].tp=_tp, T[v].upd=inf;
  if (_tp)
    sort(P+lb,P+rb,cmpx);
  else
    sort(P+lb,P+rb,cmpy);
  //T[v].V(P+lb,P+rb);
  T[v].xmin=inf, T[v].xmax=-inf, T[v].ymax=-inf, T[v].ymin=inf;
  for (i=lb; i<rb; i++)
  {
    T[v].xmin=min(T[v].xmin,P[i].x), T[v].xmax=max(T[v].xmax,P[i].x);
    T[v].ymin=min(T[v].ymin,P[i].y), T[v].ymax=max(T[v].ymax,P[i].y);
  }
  if (rb-lb>1)
  {
    T[v].l=e, build(e++,!_tp,lb,(lb+rb)/2);
    T[v].r=e, build(e++,!_tp,(lb+rb)/2,rb);
    T[v].ans=min(T[T[v].l].ans,T[T[v].r].ans);
  }
  else
    T[v].ans=P[lb].v;
}

void push (int v)
{
  if (T[v].upd==inf)
    return;
  int idl=T[v].l, idr=T[v].r;
  if (idl!=-1 && idr!=-1)
    T[idl].upd=T[v].upd, T[idr].upd=T[v].upd, T[idl].ans=T[v].upd, T[idr].ans=T[v].upd;
  T[v].ans=T[v].upd;
  T[v].upd=inf;
}

void update (int v, point l, point r)
{
  if (l.x<=T[v].xmin && r.x>=T[v].xmax && l.y<=T[v].ymin && r.y>=T[v].ymax)
  {    
    T[v].upd=l.v, T[v].ans=l.v;
    return;
  }
  if (r.x<T[v].xmin || l.x>T[v].xmax || r.y<T[v].ymin || l.y>T[v].ymax)
    return;
  push(v);
  update(T[v].l,l,r);
  update(T[v].r,l,r);
  T[v].ans=min(T[T[v].l].ans,T[T[v].r].ans);
}

int get (int v, point l, point r)
{
  push(v);
  if (l.x<=T[v].xmin && r.x>=T[v].xmax && l.y<=T[v].ymin && r.y>=T[v].ymax)
    return T[v].ans;
  if (r.x<T[v].xmin || l.x>T[v].xmax || r.y<T[v].ymin || l.y>T[v].ymax)
    return inf;
  return min(get(T[v].l,l,r),get(T[v].r,l,r));
}

int main(){
  int i, n, x1, y1, x2, y2, v, q;
  char c;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  scanf("%d", &n);
  for (i=0; i<n; i++)
    scanf("%d%d%d", &P[i].x, &P[i].y, &P[i].v);
  build(0,0,0,n);
  //for (i=0; i<e; i++)
  //  cerr<<i<<" "<<T[i].l<<" "<<T[i].r<<"     "<<T[i].ans<<" "<<T[i].upd<<endl;
  scanf("%d", &q);
  while (q>0)
  {
    q--, scanf(" %c", &c);
    //cerr<<q<<" "<<c<<endl;
    if (c=='=')
    {
      scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &v);
      if (x1>x2 || y1>y2)
        continue;
      update(0,point(x1,y1,v),point(x2,y2,v));
    }
    else
    {
      scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
      if (x1>x2 || y1>y2)
      {
        puts("NO");
        continue;
      }
      int ans=get(0,point(x1,y1,-inf),point(x2,y2,inf));
      //cerr<<ans<<endl;
      if (ans==inf)
        puts("NO");
      else
        printf("%d\n", ans);
    }
  }
  return 0;
}

