#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <queue>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define setval(a,v) memset(a,v,sizeof(a))

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const int  MOD = 1000000007;
const int  MAXN = 1000020;

long long res=1ll;
bool used[MAXN];
long long f[MAXN];

int main(void)
{                            
  int n;
  scanf("%d", &n);

  for (int i=2; i<MAXN; i++)
    if (!used[i])
      for (ll j=i*1LL*i; j<MAXN; j+=i)
        used[j]=1;
       
  f[0]=1;
  f[1]=1;

  for (int i=2; i<MAXN; i++)
    f[i]=(f[i-1]+f[i-2])%MOD;


  for (int i=2; i<=n; i++)
    if (!used[i])
    {
      ll cnt = 1LL;
      for (int j=i; j<=n; j+=i)
      {
        int t=j;
        ll cnt2=0;
        while (t%i==0)
          cnt2++, t/=i;
        cnt+=cnt2*f[n-j];
      }
      cnt%=MOD;
      res=(res*1LL*cnt)%MOD;
    }
  cout << res << endl;
  return 0;
}
