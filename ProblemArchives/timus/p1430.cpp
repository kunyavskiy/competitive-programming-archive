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

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  ll a,b,n;
  cin >> a >> b>>n;

  ll ans = n;

  for (ll i = 0; i <= a && a*i <= n; i++)
  	ans = min(ans, (n-a*i)%b);
  for (ll i = 0; i <= b && b*i <= n; i++)
  	ans = min(ans, (n-b*i)%a);

//  cout << ans << endl;
  for (ll i = 0; i <= a && a*i <= n; i++)
  	if (ans == (n-a*i)%b){
  		cout << i <<" "<<(n-a*i)/b << endl;
  		return 0;
  	}
  for (ll i = 0; i <= b && b*i <= n; i++)
  	if (ans == (n-b*i)%a){
  		cout << (n-b*i)/a<<" "<<i << endl;
  		return 0;
  	}


  return 0;
}