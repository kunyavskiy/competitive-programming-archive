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

#define taskname "a"

const int inf = 1000000000;
const ld eps = 1e-9;

double tt=clock();

multiset <double> S[3000];
double x[3000], y[3000], res, tmp[3000];
int n;
bool u[3000];

inline double dist (int i, int j)
{
  return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}

int main(){
  int tst, n, i, id, nx, ny;
  char c;               
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  scanf("%d", &n);
  for (tst=0; tst<n; printf("%.8lf\n", res), tst++)
  {
    //cerr<<tst<<endl;
    scanf(" %c", &c);
    if (c=='+')
    {
      u[tst]=1, scanf("%d%d", &nx, &ny), x[tst]=nx, y[tst]=ny;
      for (i=0; i<tst; i++)
        if (u[i])
          tmp[i]=dist(i,tst);
      for (i=0; i<tst; i++)
        if (u[i])
          S[i].insert(tmp[i]);
      for (i=0; i<tst; i++)
        if (u[i])
          S[tst].insert(tmp[i]);
    }
    else
    {
      scanf("%d%d", &nx, &ny);
      for (id=0; ; id++)
        if (u[id] && nx==x[id] && ny==y[id])
          break;
      u[id]=0;
      for (i=0; i<tst; i++)
        if (u[i])
          S[i].erase(S[i].lower_bound(dist(i,id)-eps));
    }
    for (res=0.0, i=0; i<=tst; i++)
      if (u[i] && (S[i].size()))
        res+=(*(--S[i].end()));
  }
  cerr<<(clock()-tt)/CLOCKS_PER_SEC<<endl;
  return 0;
}

