#ifndef LOCAL
   #pragma comment(linker, "/STACK:67108864")
#endif

#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <functional>
#include <iterator>
#include <time.h>
#include <assert.h>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <utility>

#define MPI 3.141592653589793238462643
#define eps 1e-8
#define inf ((int)1e9)
#define pb push_back
#define mp make_pair
#define zero(a) memset(a,0,sizeof(a))
#define sqr(x) ((x)*(x))

#if defined(__WIN32__) && defined(__GNUC__)
   #define LLD "%I64d"
#else
   #define LLD "%lld"
#endif

#ifndef __GNUC__
#define M_PI 3.1415926535897932384626433832795
#define prev prev_dsfdfgfhgfh
#define next next_mkdlsmfdgkl
#define hash hash_mdfdsgdhgfm
#undef assert
#define assert(x) if (!(x)) throw 1
#define sqrt(x) sqrt((double)(x))
#endif

#define mod (1000000007ll)

using namespace std;

typedef long long ll;
typedef double ld;

#ifdef LOCAL
	ld START = clock();
	#define TIME (clock()-START)/CLOCKS_PER_SEC
	#define PRINT_TIME cerr << "Time: "<< TIME <<"s"<< endl;
#else
  #define PRINT_TIME (void)0
#endif

long long F[5100], RF[5100];
long long res, Ca[5100], Cb[5100], Cc[5100];
int A[5100];

long long Cnk (int n, int k)
{
  return (((F[n]*RF[k])%mod)*RF[n-k])%mod;
}

long long deg (long long v, int d)
{
  if (d==0ll)
    return 1ll;
  if (d&1)
    return (deg(v,d-1)*v)%mod;
  return deg((v*v)%mod,d/2);
}

int main(){
  int i, n, a=0, b=-1, c=0, t, p, j, k;
  #ifdef LOCAL
  	freopen("input.txt", "r", stdin);
  	freopen("output.txt", "w", stdout);
  #endif
  scanf("%d%d", &n, &t);
  for (i=0; i<n; i++)
    scanf("%d", &A[i]);
  scanf("%d%d", &p, &k), p--;
  for (i=0; i<n; i++)
  {
    if (A[p]>A[i])
      a++;
    if (A[p]==A[i])
      b++;
    if (A[p]<A[i])
      c++;
  }
  for (i=1, F[0]=1, RF[0]=1; i<=n; i++)
    F[i]=(F[i-1]*((long long)i))%mod, RF[i]=deg(F[i],mod-2);
  for (i=0; i<=a; i++)
    Ca[i]=Cnk(a,i);
  for (i=0; i<=b; i++)
    Cb[i]=Cnk(b,i);
  for (i=0; i<=c; i++)
    Cc[i]=Cnk(c,i);
  for (i=0; i<=min(a,k-1); i++)
    for (j=0; j<=min(c,t-k); j++)
      if (i+j<t)
        res+=((Ca[i]*Cc[j])%mod)*Cb[t-i-j-1], res%=mod;
  printf("%d\n", (int)res);
  PRINT_TIME;
  return 0;
}
