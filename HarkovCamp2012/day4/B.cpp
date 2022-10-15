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
#define maxp (239017ll)

const int inf = 1000000000;
const ld eps = 1e-9;

long long Deg[210000], Hash[210000];
char s[210000];
int n;
int M[210000];

long long gethash (int l, int r)
{
  return Deg[200500-l]*(Hash[r]-Hash[l]);
}

bool eq (int len, int s)
{
  return Deg[s]*Hash[len]==Hash[s+len]-Hash[s];
}

long long gethash2 (int l, int r, int d)
{
  //cerr<<l<<" "<<r<<" "<<d<<endl;
  if (d>=r)
    return gethash(l,r-1);
  if (d<l && d!=r)
    return gethash(l+1,r);
  if (d==r-1)
    return gethash(l,r-1);
  return gethash(l,d)+Deg[d-l]*(gethash(d+1,r));
}

int main(){
  int i, n, p, l, r, m, tst;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  for (Deg[0]=1ll, i=1; i<210000; i++)
    Deg[i]=Deg[i-1]*maxp;
  for (scanf("%d ", &tst); tst>0; tst--)
  {
    memset(M,-1,sizeof(M));
    scanf("%d %s", &n, s);
    for (i=1; i<=n; i++)
      Hash[i]=Hash[i-1]+((long long)s[i-1])*Deg[i];
    for (p=1; ;p++)
    {
      if (M[p]==-1)
      {
        l=0, r=n-p+1;
        while (r-l>1)
          m=(r+l)/2, (eq(m,p))?(l=m):(r=m);
        M[p]=l;
      }
      l=M[p];
      //cerr<<p<<" "<<l<<endl;
      // cerr<<"????????"<<endl;
      if (l==n-p)
      {
        printf("%d\n", p);
        break;
      }
        //cerr<<"????????"<<endl;
      //cerr<<gethash2(0,n-p,l)<<" "<<gethash2(p,n,l)<<" "<<p<<endl;
      if (gethash2(0,n-p,l)==gethash2(p,n,l))
      {
        printf("%d\n", p);
        break;
      }
        //cerr<<"????????"<<endl;
      if (gethash2(0,n-p,l+p)==gethash2(p,n,l+p))
      {
        printf("%d\n", p);
        break;
      }
        //cerr<<"????????"<<endl;
      if (gethash(1,n-p)==gethash(p+1,n))
      {
        printf("%d\n", p);
        break;
      }
        //cerr<<"????????"<<endl;

      l=0, r=n-p;
      while (r-l>1)
        m=(r+l)/2, eq(m,p+1)?(l=m):(r=m);
      M[p+1]=l;
      //cerr<<l<<endl;
      if (l<=p && gethash2(0,n-p,l)==gethash(p+1,n))
      {
        printf("%d\n", p);
        break;
      }
    }
  }
  return 0;
}

