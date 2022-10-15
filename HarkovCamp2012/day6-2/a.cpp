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

#define taskname "a6"

const int inf = 1000000000;
const ld eps = 1e-9;

const ll MOD = 1000000007;

ll L,R,K;

ll mult(ll a,ll b){
	a %= MOD;
	b %= MOD;
	return (a*b)%MOD;
}

ll add(ll a,ll b){
	return (a+b)%MOD;
}

/*bool check(int a){
	for (int i = 2; i*i <= a; i++)
		if (a % i == 0)
			return false;
	return true;
}                */

ll calc(ll n,ll p){
	ll a = 1;
	for (int i = 0; i < 4; i++){
		a = a*n%p;
	}
	return a;
}

ll deg (ll v, ll d, ll p)
{
  if (d==0)
    return 1ll;
  if (d&1)
    return (v*deg(v,d-1,p))%p;
  return deg((v*v)%p,d/2,p);
}

bool check (ll v, ll p)
{
  v=deg(v,(p-1)/5,p);
  return (v!=1ll) && (v!=0ll);
}

bool u[12345678];
bool u2[2100000];

int main(){
  #ifdef LOCAL
  	int START = clock();
  #endif	

  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);

  cin >> K >> L >> R;

  ll ans = 0;
  if (K <= 4){
	for (ll i = L; i <= R; i++)
		ans = add(ans,mult(i,K));
	cout << ans << endl;
	return 0;
  }

  vector<int> primes;
  primes.pb(5);
  u[0]=1, u[1]=1;
  for (int i=2; i<K; i++)
    if (!u[i])
    {
      if (i%5==1)
        primes.pb(i);
      if (i<5000)
        for (int j=i*i; j<K; j+=i)
          u[j]=1;
    }
  /*cerr<<primes.size()<<endl;
  for (int i = 2; primes.size() <= 30 && i*5+1 < K; i++)
  	if (check(i*5+1))
  		primes.pb(i*5+1);*/


  #ifdef LOCAL
  	cerr << (clock()-START)*1.0/CLOCKS_PER_SEC << endl;
  #endif

  for (int i=0; i<(int)primes.size(); i++)
  {
    int p=primes[i];
    int a=rand()%p;
    if (p==5)
      a=2;
    else
    {
      while (!check(a,p))
        a=rand()%p;
    }
    int b=deg(a,(p-1)/5,p), c=1;
    for (int j=1; j<5; j++)
    {
      c=(c*1ll*b)%p;
      ll y=(L/p)*p;
      y+=c;
      while (y<L)
        y+=p;
      while (y<=R)
      {  
        int tmp=(int)(y-L);
        if (!u2[tmp])
          u2[tmp]=1, ans=add(ans,mult(y,p)); 
        y+=p;
      }
    }
  }

  /*for (ll i = L; i <= R; i++){
  	if (i% 10000 == 0)
  		cerr << i <<endl;

  	for (int j = 0; j < (int)primes.size(); j++)
  		if (primes[j] == K || calc(i,primes[j]) == 0){
  			ans = add(ans,mult(i,primes[j]));
  			break;
  		}	
  }  */

	for (ll i = 0; i <= R-L; i++)
	   if (!u2[i])
		ans = add(ans,mult(i+L,K));
  cout << ans << endl;
  #ifdef LOCAL
  	cerr << (clock()-START)*1.0/CLOCKS_PER_SEC << endl;
  #endif
  return 0;
}

