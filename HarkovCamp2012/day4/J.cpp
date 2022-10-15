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
#define linf ((long long)1e17)
#define maxp ((long long)2e14)

const int inf = 1000000000;
const ld eps = 1e-9;

ll deg (ll a, int d)
{
  ll res=1ll;
  for (int i=0; i<d; i++)
  {
    if (res>=linf/a)
      return linf;
    res*=a;
  }
  return res;
}

ll msqrt(ll a, int d)
{
  ll b=(long long)pow((double)a,1.0/((double)d));
  assert(b>=0);
  while (deg(b,d)<a)
    b++;
  while (deg(b,d)>a)
    b--;
  return b;
}

ll solve(ll a)
{
  if (a<=1ll)
    return a;
  ll res=msqrt(a,2);
  for(int i=3; (1ll<<i)<=a; i++)
  {
    //cerr<<i<<endl;
    for (ll j=2; i*log((double)j)<=2.0*log((double)a) && deg(j,i)<=a; j++)
    {
      //if (i>5)
      //  cerr<<j<<endl;
      ll x=deg(j,i);
      bool fl=1;
      for (int k=2; k<i; k++)
        if (deg(msqrt(x,k),k)==x)
        {
         fl=0;
         break;
        }
      if (fl)
        res++;
    }
  }
  return res;
}

ll solven(ll a)
{
  cerr<<a<<endl;
  if (a<=1ll)
    return a;
  ll res=msqrt(a,3);
  for(int i=5; (1ll<<i)<=a; i+=2)
  {
    //cerr<<i<<endl;
    for (ll j=2; i*log((double)j)<=2.0*log((double)a) && deg(j,i)<=a; j++)
    {
      //if (i>5)
      //  cerr<<j<<endl;
      ll x=deg(j,i);
      bool fl=1;
      for (int k=3; k<i; k+=2)
        if (deg(msqrt(x,k),k)==x)
        {
         fl=0;
         break;
        }
      if (fl)
        res++;
    }
  }
  return res;
}

ll solve2 (long long a)
{
  if (a>=0)
    return solve(a)+1+solven(maxp);
  return solven(maxp)-solven(-a-1);
}

int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  ll a,b;
  cin >> a >> b;
  if (a>b)
  {
    puts("0");
    return 0;
  }
  cout << solve2(b) - solve2(a-1) << endl;
  return 0;
}

