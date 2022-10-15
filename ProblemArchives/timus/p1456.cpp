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

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif


#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

ll pow(ll a,ll b,ll n){
	if (b == 0)
		return 1;
	ll temp = pow((a*a)%n,b>>1,n);
	if (b&1)
		temp = (temp * a)%n;
	return temp;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  ll a,b,n;

  ll f = 1;
  cin >>a >> n;
  ll n0 = n;

  for (int i = 2; i * i <= n; i++){
  	if (n % i == 0){
  		f *= i-1;
  		n/=i;
  	}
  	while (n % i == 0)
  		f *= i, n/=i;
  }
  if (n-1)
  	f *= n-1;

  vector<int> d;

  n = n0;

  for (int i = 1; i*i <= f; i++)
  	if (f % i == 0)
  		d.pb(i),d.pb(f/i);

  sort(d.begin(),d.end());

  for (int i = 0; i < (int)d.size(); i++)
  	if (pow(a,d[i],n) == 1){
  		printf("%d\n",d[i]);
  		return 0;
  	}

  printf("0\n");

  return 0;
}