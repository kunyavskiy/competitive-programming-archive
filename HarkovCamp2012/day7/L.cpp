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
#define sd (1<<10)

const int inf = 1000000000;
const ld eps = 1e-9;

int A[2*sd+10][2*sd+10];

inline int get (int id, int l, int r)
{
  int res=-inf;
  while (l<r)
  {
    if (l&1)
      res=max(res,A[id][l]), l++;
    if (r&1)
      r--, res=max(res,A[id][r]);
    l/=2, r/=2;
  }
  return res;
}

inline void add (int id, int x, int v)
{
  A[id][x]=v, x/=2;
  while (x>0)
    A[id][x]=max(A[id][2*x],A[id][2*x+1]), x/=2;
}

inline void add1 (int id, int x)
{
  while (x>0)
    A[id][x]=max(A[2*id][x],A[2*id+1][x]), x/=2;
}

int main(){
  int n, m, q, i, j, x1, x2, y1, y2, x, y, v;
  char c;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  scanf("%d%d%d", &n, &m, &q);
  memset(A,255-63,sizeof(A));
  //cerr<<A[0][0]<<endl;
  for (i=0; i<n; i++)
    for (j=0; j<m; j++)
      scanf("%d", &A[i+sd][j+sd]);
  for (i=sd; i<2*sd; i++)
    for (j=sd-1; j>0; j--)
      A[i][j]=max(A[i][2*j],A[i][2*j+1]);
  for (i=sd-1; i>0; i--)
    for (j=1; j<2*sd; j++)
      A[i][j]=max(A[2*i][j],A[2*i+1][j]);
  while (q>0)
  {
    q--;
    scanf(" %c", &c);
    if (c=='?') 
    {
      scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
      x1+=sd, y1+=sd, x2+=sd, y2+=sd, x1--, x2--;
      int res=-inf;
      while (x1<y1)
      {
        if (x1&1)
          res=max(res,get(x1,x2,y2)), x1++;
        if (y1&1)
          y1--, res=max(res,get(y1,x2,y2));
        x1/=2, y1/=2;
      }
      printf("%d\n", res);
    }
    else
    {
      scanf("%d%d%d", &x, &y, &v);
      x+=sd-1, y+=sd-1;
      add(x,y,v), x/=2;
      while (x>0)
        add1(x,y), x/=2;
    }
  }
  return 0;
}

