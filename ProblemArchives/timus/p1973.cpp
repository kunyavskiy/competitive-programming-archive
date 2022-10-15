#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <list>
#include <set>
#include <map>
#include <sstream>
//#include <iostream>

#define pb push_back
#define mp make_pair
#define TASKNAME ""

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#ifndef LOCAL
#undef assert
void assert(bool x) {
  if (!x) printf("%d\n", 5 / 0);
}
void assert2(bool x) {
  if (!x) {
    int *tmp = new int[1];
    tmp[int(1e5)] = 100 / 23;
  }
}
#else
#define assert2 assert
#endif

#define TIMESTAMP(x) eprintf("[" #x "] Time = %.3lfs\n",clock()*1.0/CLOCKS_PER_SEC)

#ifdef linux
#define LLD "%lld"
#else
#define LLD "%I64d"
#endif

#define sz(x) ((int)(x).size())

using namespace std;

typedef long double ld;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;

const int inf = 1e9;
const double eps = 1e-9;
const double INF = inf;
const double EPS = eps;

struct point
{
  ld x, y;
  point ()
  {
    x=0, y=0;
  }
  point (ld _x, ld _y)
  {
    x=_x, y=_y;
  }
};

ld operator ^ (point a, point b)
{
  return a.x*b.y-a.y*b.x;
}

point operator - (point a, point b)
{
  return point(a.x-b.x,a.y-b.y);
}

const ld c = 0.14814814668;
int n;
ld W[1100], S, res;
point A[1100];

int main(){     
  int i, j;
  double x, y;
  #ifdef LOCAL
  freopen(TASKNAME".in","r",stdin);
  freopen(TASKNAME".out","w",stdout);
  #endif
  scanf("%d", &n);
  for (i=0; i<n; i++)
    scanf("%lf%lf", &x, &y), A[i]=point(x,y);
  for (i=n-1; i>=0; i--)
    A[i]=A[i]-A[0];
  for (i=0; i<n-2; i++)
    W[i]=fabs((A[i+2]^A[i+1])/2.0), S+=W[i];// eprintf("%.8lf\n", (double)W[i]);
  for (i=0; i<n-2; i++)
    res+=c*(W[i]*W[i])*W[i];
  for (i=0; i<n-2; i++)
    for (j=i+1; j<n-2; j++)
    {
      res+=W[i]*W[j]*fabs((A[i+1].x+A[i+2].x)*(A[j+1].y+A[j+2].y)-(A[i+1].y+A[i+2].y)*(A[j+1].x+A[j+2].x))/9.0;
      //eprintf("%.8lf\n", (double)(fabs((A[i+1].x+A[i+2].x)*(A[j+1].y+A[j+2].y)-(A[i+1].y+A[i+2].y)*(A[j+1].x+A[j+2].x))/9.0));
    }
  res/=S*S;
  printf("%.8lf\n", (double)res);
  TIMESTAMP(end);
  return 0;
}
