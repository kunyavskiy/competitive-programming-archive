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

#define taskname "l"

const int inf = 1000000000;
const ld eps = 1e-9;

long double res, H, X[110], Y[110];
int Y2[110], e;
int n;

bool can (int id, long double h)
{
  int lf=id;
  int j;
  while (lf>1 && Y[lf-1]<h+Y[id])
    lf--;
  while (lf>1 && Y[lf-1]>Y[lf])
    lf--;
  int rt=id;
  while (rt<=n && Y[rt+1]<h+Y[id])
    rt++;
  while (rt<=n && Y[rt+1]>Y[rt])
    rt++;
  long double s=0.0, th=h+Y[id];
  for (j=lf; j<rt; j++)
  {
    long double miny=min(Y[j],Y[j+1]), maxy=max(Y[j],Y[j+1]);
    if (miny>=th)
      continue;
    if (maxy<=th)
      s+=(X[j+1]-X[j])*(th-(maxy+miny)/2.0);
    else
      s+=(th-miny)*(X[j+1]-X[j])*(maxy-miny)/(2.0*sqr(maxy-miny));
  }
  cerr<<
  return s<=H*(X[rt]-X[lf]);
}

int main(){
  int i;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  scanf("%d", &n), cin>>H; 
  for (i=1; i<=n+1; i++)
    cin>>X[i]>>Y[i], Y2[e++]=(int)Y[i];
  Y2[e++]=-(int)1e9, Y2[e++]=(int)2e9;
  sort(Y2,Y2+e);
  e=unique(Y2,Y2+e)-Y2;
  X[0]=X[1]-1.0, Y[0]=-1e9, X[n+2]=X[n+1]+1.0, Y[1]=1e9;
  for (i=1; i<=n+1; i++) 
  {
    if (i>1 && Y[i-1]<Y[i])
      continue;
    if (i<=n && Y[i+1]<Y[i])
      continue;
    for (int it2=0; it2<e-1; it2++)
    {
      if (Y2[it2+1]<=Y[i])
        continue;
      long double l=max((ld)0.0,(ld)Y2[it2]-Y[i]), r=(ld)Y2[it2+1]-Y[i];
      if (can(i,r))
      {
        res=max(res,r);
        continue;
      }
      for (int it=0; it<80; it++)
      {
        long double h=(l+r)/2.0;
        if (can(i,h))
          l=h;
        else
          r=h;    
      }  
      if (can(i,l))
      res=max(res,l);
    }
  }
  printf("%.8lf\n", (double)res);
  return 0;
}

