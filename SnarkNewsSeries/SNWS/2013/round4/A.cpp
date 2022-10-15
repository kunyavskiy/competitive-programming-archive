#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>
#define mp make_pair
#define pb push_back

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "cars"

typedef long long ll;
typedef long double ld;

ll fib[100];

ll up(ll a,ll b){
	return a/b + !!(a%b);
}


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	ll n;
  	cin >> n;
  	ll ans = 0;

  	fib[1] = 1;
  	fib[2] = 2;
  	int cnt = 2;
  	while (fib[cnt] < 1000000000000000000LL){
  		fib[cnt+1] = fib[cnt] + fib[cnt-1];
  		cnt++;
  	}

  	while (cnt > 0){
  		if (n >= fib[cnt]){
  			ll tmp = up(n - fib[cnt],cnt);
  			ans += tmp;
  			n -= tmp*cnt;
		}
		cnt--;
  	}

  	cout << ans << endl;
      
    return 0;
}