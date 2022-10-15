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

#define taskname "e6"

const int inf = 1000000000;
const ld eps = 1e-9;

ll deg (ll p, int d)
{
  ll ans=1;
  while (d>0)
    ans*=p, d--;
  return ans;
}

void solve ()
{           
  ll l, r;
  cin>>l>>r;
  int n=2;
  ll a0=l, a1=r;
  int t=2;
  while (n==t)
  {
    t++;
    ll k, d;
    for (ll p=1; p<100; p++)
    {
      if (log((double)r)*2.0<((double)(t))*log((double)(p+1)))
        break;
      d=deg(p,t);
      k=(l+d-1ll)/d;
      if (r>=k*deg(p+1,t))
      {
        n=t, a0=k*d, a1=(a0/p)*(p+1);
        break;
      }
    }
  }
  cout<<n<<" "<<a0<<" "<<a1<<endl;
}

int main(){
  int tst;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  for (scanf("%d", &tst); tst>0; tst--)
    solve();
  return 0;
}

