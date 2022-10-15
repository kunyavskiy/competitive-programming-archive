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

long long a, n, res;
long long D[50];
int e;

int main(){
  int i, cnt, j;
  long long li, tmp, ta, p;
  #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
  #endif
  cin>>a>>n;
  ta=a;
  while (ta%2ll==0)
    ta/=2ll;
  for (li=2; li*li<=ta; li++)
    if (ta%li==0ll)
    {
      D[e++]=li;
      while (ta%li==0ll)
        ta/=li;
    }
  if (ta!=1ll)
    D[e++]=ta;
  for (i=0; i<(1<<e); i++)
  {
    for (p=1ll, cnt=0, j=0; j<e; j++)
      if (i&(1<<j))
        p*=D[j], cnt++;
    if (a%2ll==0ll)
      tmp=((n/p)+1ll)/2ll;
    else
      tmp=(n/2ll)/p;
    if (cnt&1)
      res-=tmp;
    else
      res+=tmp;
  }
  cout<<n-res<<endl;
  PRINT_TIME;
  return 0;
}
