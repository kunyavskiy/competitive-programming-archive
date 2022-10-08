//#include <iostream>
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
#include <sstream>
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

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "D"

typedef long long ll;
typedef long double ld;

bool isPrime(int x){
	for (int i = 2; i*i <= x; i++)
		if (x % i == 0)
			return false;
	return true;
}

vector<int> p;

int maxv;
ll ans = -1;
int n;

ll gcd(ll a,ll b){
	return b?gcd(b,a%b):a;
}

ll lcm(ll a,ll b){
	return a/gcd(a,b) * b;
}

void go(int pos,ll x,ll val){
	eprintf("%d "LLD" "LLD"\n",pos,x,val);
	if (x >= maxv) return;
	if (val == n)
		ans = max(ans,x);
	if (n % val != 0 || pos == (int)p.size())
		return;
	go(pos+1,x,val);
	val = lcm(val,p[pos] - 1);
	x = x * p[pos];
	while (x < maxv && n % val == 0){
		go(pos+1,x,val);
		x *= p[pos];
		val *= p[pos];
	}
}




int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	scanf("%d %d",&n,&maxv);

  	p.pb(2);

  	for (int i = 1; i*i <= n; i++){
  		if (n % i == 0){
  			if (isPrime(i+1)) p.pb(i+1);
  			if (isPrime(n/i+1)) p.pb(n/i+1);
  		}
  	}

  	sort(p.begin(),p.end());

  	p.erase(unique(p.begin(),p.end()),p.end());

  	go(0,1,1);

  	printf(LLD"\n",ans);
      
    TIMESTAMP(end);
    return 0;
}