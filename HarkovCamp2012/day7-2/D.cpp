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

#define taskname "d"
#define mod (1000000007ll)

const int inf = 1000000000;
const ld eps = 1e-9;

struct matrix 
{
  long long A[3][3];
};

matrix operator * (matrix a, matrix b)
{
  int i, j, k;
  matrix c;
  for (i=0; i<3; i++)
    for (j=0; j<3; j++)
    {
      c.A[i][j]=0;
      for (k=0; k<3; k++)
        c.A[i][j]+=a.A[i][k]*b.A[k][j];
      c.A[i][j]%=mod;
    }
  return c;
}

matrix deg (matrix a, int d)
{
  if (d==0)
  {
    memset(a.A,0,sizeof(a.A));
    a.A[0][0]=1, a.A[1][1]=1, a.A[2][2]=1;
    return a;
  }
  if (d&1)
    return a*deg(a,d-1);
  return deg(a*a,d/2);
}

long long deg2 (long long v, int d)
{
  if (d==0)
    return 1ll;
  if (d&1)
    return (v*deg2(v,d-1))%mod;
  return deg2((v*v)%mod,d/2);
}

int main(){
  int tst, n;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  for (scanf("%d", &tst); tst>0; tst--)
  {
    scanf("%d", &n);
    matrix a;
    a.A[0][0]=2ll, a.A[0][1]=1ll, a.A[0][2]=1ll;
    a.A[1][0]=2ll, a.A[1][1]=2ll, a.A[1][2]=1ll;
    a.A[2][0]=0ll, a.A[2][1]=0ll, a.A[2][2]=1ll;
    a=deg(a,n-1);
    long long tmp=(mod-deg2(2,n)+1ll)%mod;
    printf("%d\n", (int)((a.A[0][0]+a.A[0][1]+a.A[0][2]+tmp)%mod));
  }
  return 0;
}

