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
#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define taskname "b"

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
typedef double dbl;

#define taskname "b"

const int inf = 1000000000;
const ld eps = 1e-9;

struct pnt
{
  int x, y;

  pnt( int _x = 0, int _y = 0 ) : x(_x), y(_y) { }

  inline pnt operator + ( const pnt &p ) const { return pnt(x + p.x, y + p.y); }
  inline pnt operator - ( const pnt &p ) const { return pnt(x - p.x, y - p.y); }

  inline ll operator * ( const pnt &p ) const { return (ll)x * p.y - (ll)y * p.x; }

  inline bool operator < ( const pnt &p ) const { return x < p.x || (x == p.x && y < p.y); }

  inline ll d2() const { return (ll)x * x + (ll)y * y; }
  inline dbl ang() const { return atan2((dbl)y, (dbl)x); }
};

typedef vector <pnt> vpnt;

inline bool pless( const pnt &a, const pnt &b )
{
  ll x = a * b;
  return x != 0 ? x < 0 : a.d2() < b.d2();
}

vpnt ConvexHull( vpnt p )
{
  int n = sz(p), mi = 0;
  assert(n > 0);
  forn(i, n)
    if (p[mi] < p[i])
      mi = i;
  swap(p[0], p[mi]);
  for (int i = 1; i < n; i++)
    p[i] = p[i] - p[0];
  sort(p.begin() + 1, p.end(), pless);

  int rn = 0;
  vpnt r(n);
  r[rn++] = p[0];
  for (int i = 1; i < n; i++)
  {
    pnt q = p[i] + p[0];
    while (rn >= 2 && (r[rn - 1] - r[rn - 2]) * (q - r[rn - 2]) >= 0)
      rn--;
    r[rn++] = q;
  }
  r.resize(rn);
  return r;
}

vpnt P;
ll res;

ll dist (int f, int s)
{
  s%=(int)P.size();
  return (P[f].x-P[s].x)*1ll*(P[f].x-P[s].x)+(P[f].y-P[s].y)*1ll*(P[f].y-P[s].y);
}

int main(){
  int n, i, j=0, x, y;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  scanf("%d",  &n);
  for (i=0; i<n; i++)
    scanf("%d%d", &x, &y), P.pb(pnt(x,y));
  P=ConvexHull(P);

/*  for (int i = 0; i < (int)P.size(); i++)
  	cerr << P[i].x <<" "<<P[i].y<<endl;
  cerr<<endl<<endl;*/

  for (i=0; i<(int)P.size(); i++){
  	res = max(res,dist(i,j));
    while (dist(i,j)<=dist(i,j+1)){
//      cerr << i <<" "<<j<<endl;
      res=max(res,dist(i,j+1)), j++;
    }
  }
  cout<<res<<endl;
  return 0;
}

