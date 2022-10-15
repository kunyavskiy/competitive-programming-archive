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

#define taskname "h"

const int inf = 1000000000;
const ld eps = 1e-9;

int SZ=250;
vector <int> V[410];
int A[110000];
char s[10];

int main(){  
  int i, j, n, m, y, k, l, x, v, res, nx, ny;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  scanf("%d%d", &n, &m);
  for (i=0; i<n; i++)
    scanf("%d", &A[i]);
  for (i=0; i<405; i++)
  {
    for (j=0; j<SZ; j++)
      V[i].pb(A[i*SZ+j]);
    sort(V[i].begin(),V[i].end());
  }
  for (j=0; j<m; j++)
  {
    scanf(" %s", s);
    if (s[0]=='G')
    {
      scanf("%d%d%d%d", &x, &y, &k, &l), x--;
      res=0;
      nx=min(y,((x+SZ-1)/SZ)*SZ);
      while (x<nx)
      {
        if (A[x]>=k && A[x]<=l)
          res++;
        x++;
      }
      ny=max(x,(y/SZ)*SZ);
      while (y>ny)
      {
        y--;
        if (A[y]>=k && A[y]<=l)
          res++;
      }
      if (x<y)
      {
        x/=SZ, y/=SZ;
        while (x<y)
          res+=(lower_bound(V[x].begin(),V[x].end(),l+1)-lower_bound(V[x].begin(),V[x].end(),k)), x++;
      }
      printf("%d\n", res);
      continue;
    }
    scanf("%d%d", &x, &v), x--;
    V[x/SZ].erase(lower_bound(V[x/SZ].begin(),V[x/SZ].end(),A[x]));
    A[x]=v, V[x/SZ].pb(v), sort(V[x/SZ].begin(),V[x/SZ].end());
  }
  return 0;
}

