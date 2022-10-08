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
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME ""
#define TASKMOD "dbg"

typedef long long ll;
typedef long double ld;

void PreCalc(){
}

map<ll, ll> cache;

ll get(ll n, pair<ll, ll> x) {
  if (cache.find(n) != cache.end()) return cache[n];
  ll& ans = cache[n];

  ll minv = (n - 1) / 2;
  ll maxv = n / 2;
  if (make_pair(minv, maxv) >= x) {
    ans = 1 + get((n - 1) / 2, x) + get(n / 2, x);
  } else {
    ans = 0;
  }
  return ans;
}

void solve(){
  ll n, k;
  scanf("%lld %lld", &n, &k);

  ll l = 0, r = n;

  while (r - l > 1) {
    ll m = (l + r) / 2;
    cache.clear();
    if (get(n, {m, 0}) >= k) {
      l = m;
    } else {
      r = m;
    }
  }

  ll minv = l;
  
  l = minv, r = n;

  while (r - l > 1) {
    ll m = (l + r) / 2;
    cache.clear();
    if (get(n, {minv, m}) >= k) {
      l = m;
    } else {
      r = m;
    }
  }

  printf("%lld %lld\n", l, minv);
}


int main(){
  //freopen(TASKNAME"-"TASKMOD".in","r",stdin);
  //freopen(TASKNAME"-"TASKMOD".out","w",stdout);
	
  PreCalc();
  TIMESTAMP(PreCalc);	

  char buf[1000];
  int testNum;
  fgets(buf, sizeof buf, stdin);
  sscanf(buf,"%d",&testNum);

  for (int testId = 1; testId <= testNum; testId++){
  	if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
	  	TIMESTAMPf("Test %d",testId);
  	printf("Case #%d: ",testId);
  	solve();                        
  }
      
  TIMESTAMP(end);
  return 0;
}
