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

#define TASKNAME "C"

typedef long long ll;
typedef long double ld;

map<pair<int,int> , ll > ans;

ll solve(int n,int m){
	if (n == 1 && m == 1) return 0;
	if (ans.find(mp(n,m)) != ans.end())
		return ans[mp(n,m)];
	ll& res = ans[mp(n,m)];
	res = 1LL<<60;
	if (n % 2 == 0)
		res = min(res, solve(n/2,m));
	else if (n != 1)
		res = min(res, solve(n/2,m)/* + solve(1,m)*/ + m);

	if (m % 2 == 0)
		res = min(res, solve(n, m/2));
	else if (m != 1)
		res = min(res, solve(n, m/2)/* + solve(n,1)*/ + n);

	return res;
}


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
  	int tst;
  	scanf("%d",&tst);

  	for (int i = 0; i < tst; i++){
  		int n,m;
  		scanf("%d %d",&n,&m);
  		printf(LLD"\n",solve(n,m));
  	}
      
  TIMESTAMP(end);
  return 0;
}