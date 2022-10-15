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

#define taskname "j"

const int inf = 1000000000;
const ld eps = 1e-9;

double a, b, c;

struct point
{
  double x, y, z, p;
  int id;
  point ()
  {
    x=0, y=0, z=0, id=-1, p=0;
  }
  point (double _x, double _y, double _z, int _id)
  {
    x=_x, y=_y, z=_z, id=_id;
    double d=x*a+y*b+z*c;
    double x1=x-a*d, y1=y-b*d, z1=z-c*d;
    p=sqrt(x1*x1+y1*y1+z1*z1);
    if (a*x1+b*y1+c*z1<0)
      p=-p;
  }
};

bool operator < (point f, point s)
{
  return f.p<s.p;
}


point P[31000];


inline double dist (int fi, int si)
{
  point f=P[fi], s=P[si];
  return sqrt((f.x-s.x)*(f.x-s.x)+(f.y-s.y)*(f.y-s.y)+(f.z-s.z)*(f.z-s.z));
}

double A[31000];
int Res[31000];

inline void update (int f, int s, double d)
{
  if (A[f]>d)
    A[f]=d, Res[P[f].id]=P[s].id;
}

int main(){
  int i, l, r, n, _x, _y, _z;
  double dl, dr, tmp;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  //srand(time(NULL));
  srand(239);
  a=rand()+1, b=rand()+1, c=rand()+1;
  double d=sqrt(a*a+b*b+c*c);
  a/=d, b/=d, c/=d;
  scanf("%d", &n);
  for (i=0; i<n; i++)
    scanf("%d%d%d", &_x, &_y, &_z), P[i]=point(_x,_y,_z,i);
  sort(P,P+n);
  for (i=0; i<n; i++)
    A[i]=1e18;
  for (i=0; i<n; i++)
  {
    l=i-1, r=i+1, dl=(l>=0)?(P[i].p-P[l].p):(1e17), dr=(r<n)?(P[r].p-P[i].p):(1e17);
    while (l>=0 || r<n)
    {
      if (dl<=dr)
      {
        if (A[i]<=dl)
          break;
        tmp=dist(i,l);
        update(i,l,tmp), update(l,i,tmp);  
        l--, dl=(l>=0)?(P[i].p-P[l].p):(1e17);
        continue;  
      }
      if (A[i]<=dr)
        break;
      tmp=dist(i,r);
      update(i,r,tmp), update(r,i,tmp);  
      r++, dr=(r<n)?(P[r].p-P[i].p):(1e17);
    }
  }
  for (i=0; i<n; i++)
    printf("%d ", Res[i]+1);
  printf("\n");
  return 0;
}

