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

#define TASKNAME "A"

typedef long long ll;
typedef long double ld;


ld calc(int n,int p,int c){
	vector<int> num, den;
	for (int i = p-c+1; i <= n - c; i++) num.pb(i);
	for (int i = p+1; i <= n; i++) den.pb(i);
	ld res = 1;
	while (!num.empty() || !den.empty()){
		if (!den.empty() && (res > 1 || num.empty()))
			res /= den.back(), den.pop_back();
		else
			res *= num.back(), num.pop_back();
	}
	return res;
}

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	int sp,sn,cp;
  	sp = sn = cp = 0;
  	int n;
  	scanf("%d",&n);

  	for (int i = 0; i < n; i++){
  		int a;
  		scanf("%d",&a);
  		if (a >= 0)
  			sp += a, cp++;
  		else
  			sn += a;
  	}

  	if (cp == n){
  		printf("%d\n", sp);
  		return 0;
  	}

  	ld ans = 0;
  	for (int i = 1; i <= cp; i++) {
		ans += calc(n, cp, i) * sp / cp;
//		eprintf("%d %lf\n", i, (double)calc(n, cp, i));
	}

  	ans += sn * 1.0/ (n - cp);

  	printf("%.18lf\n", (double)ans);
      
    TIMESTAMP(end);
    return 0;
}