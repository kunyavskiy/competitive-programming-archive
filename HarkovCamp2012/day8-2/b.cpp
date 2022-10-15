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

#define taskname "b"

const int inf = 2100000000;
const ld eps = 1e-9;

#ifdef LOCAL
double tt=clock();
#endif
               
struct point 
{
  int x, y;
  point ()
  {
    x=0, y=0;
  }
  point (int _x, int _y)
  {          
    x=_x, y=_y;
  }
}P[61000];

point P2[21000];
int ep;

inline bool cmpx (point f, point s)
{
  if (f.x!=s.x)
    return f.x<s.x;
  return f.y<s.y;
}

inline bool cmpy (point f, point s)
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
  int l, r;
  int xmin, xmax, ymin, ymax, upd;                              
  point mid;
}T[121000];

void build (int v, bool _tp, int lb, int rb)
{
  int i;
  T[v].l=-1, T[v].r=-1, T[v].tp=_tp, T[v].upd=0;
  if (_tp)
  //	sort(P+lb,P+rb,cmpx);
    nth_element(P+lb,P+(lb+rb)/2,P+rb,cmpx);
  else
   //	sort(P+lb,P+rb,cmpy);
    nth_element(P+lb,P+(lb+rb)/2,P+rb,cmpy);

  T[v].xmin=inf, T[v].xmax=-inf, T[v].ymax=-inf, T[v].ymin=inf;
  for (i=lb; i<rb; i++)
  {
    T[v].xmin=min(T[v].xmin,P[i].x), T[v].xmax=max(T[v].xmax,P[i].x);
    T[v].ymin=min(T[v].ymin,P[i].y), T[v].ymax=max(T[v].ymax,P[i].y);
  }
  if (rb-lb>1)
  {
    T[v].mid=P[(lb+rb)/2];
    T[v].l=e, build(e++,!_tp,lb,(lb+rb)/2);
    T[v].r=e, build(e++,!_tp,(lb+rb)/2,rb);
  }
}

void push (int v)
{
  int idl=T[v].l, idr=T[v].r;
  T[idl].upd+=T[v].upd, T[idr].upd+=T[v].upd, T[v].upd=0;
}

int updlx,updly;

void update (int v)
{
  tree& Tv = ::T[v];
  if (updlx<=Tv.xmin && updly<=Tv.ymin)
  {    
    Tv.upd++;
    return;
  }
  if (updlx>Tv.xmax || updly>Tv.ymax)
    return;
  update(Tv.l);
  update(Tv.r);
}

inline int get (int v, point l)
{
  while (T[v].l!=-1)
  {
    push(v);
    if (!T[v].tp)
      (cmpy(l,T[v].mid))?(v=T[v].l):(v=T[v].r);
    else
      (cmpx(l,T[v].mid))?(v=T[v].l):(v=T[v].r);
  }
  return T[v].upd;
}

/*void print ()
{
  printf("\n\n");
  printf("%d\n", e);
  for (int v=0; v<e; v++)
    printf("v=%d l=%d r=%d tp=%d upd=%d\n", v, T[v].l, T[v].r, T[v].tp, T[v].upd);
}   */

bool operator == (point f, point s)
{
  return f.x==s.x && f.y==s.y;
}

int norm(ll a){
	if ( a >= 2000000100LL)
		return 2000000101LL;
	if ( a <= -2000000100LL)
		return -2000000101LL;
	return (int)a;
}

int n;

int solve (ll len)
{  	
//  cerr << len << endl;
  int i;
  ep=0,e=1;
  for (i=0; i<n; i++)
  {
    P[ep++]=point(-P2[i].x,P2[i].y);
    P[ep++]=point(-P2[i].x,norm(P2[i].y+len));
    P[ep++]=point(norm(len-P2[i].x),P2[i].y);
	assert(ep <= 60000);
  }
  //cerr << ep << endl;
  sort(P,P+ep,cmpx);
  ep=unique(P,P+ep)-P;

  build(0,0,0,ep);
  //cerr <<"!!!!!!!"<<endl;
  int ans = 0;
  for (i=0; i<n; i++)
  {
    ans-=get(0,point(-P2[i].x,P2[i].y));
    ans+=get(0,point(-P2[i].x,norm(P2[i].y+len)));
    ans+=get(0,point(norm(len-P2[i].x),P2[i].y));
    updlx=-P2[i].x;
    updly=P2[i].y;
    update(0);
  }
  return ans;
}

bool cmp (point f, point s)
{
  if (f.y-f.x!=s.y-s.x)
    return f.y-f.x<s.y-s.x;
  return cmpy(f,s);
}

int main(){
  int i, m;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  scanf("%d%d", &n, &m);
  if (m==(n*(n-1))/2)
  {
    puts("-1");
    return 0;
  }
  for (i=0; i<n; i++)
    scanf("%d%d", &P2[i].x, &P2[i].y);
  sort(P2,P2+n,cmp);
  if (solve(0)>m)
  {
    puts("0");
    return 0;
  }
  int l=0, r=(int)(2e9)+1000;
  while (r-l>1)
    (solve((l+r*1LL)/2ll)<=m)?(l=(l+r*1LL)/2ll):(r=(l+r*1LL)/2ll);
  int q=r;
  l=0, r=(int)(2e9)+1000;
  while (r-l>1)
    (solve((l+r*1LL)/2ll)<m)?(l=(l+r*1LL)/2ll):(r=(l+r*1LL)/2ll);
  cout<<q-r<<endl;
  return 0;
}

