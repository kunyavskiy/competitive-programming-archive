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

#define TASKNAME "F"

typedef long long ll;
typedef long double ld;


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	int x1,y1,x2,y2;
  	scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
  	
  	ld r1 = sqrt(x1*1LL*x1 + y1*1LL*y1);
  	ld r2 = sqrt(x2*1LL*x2 + y2*1LL*y2);

  	ld ans = 0;
  	ans += abs(r1 - r2);
	
	ld ang1 = (x1*1LL*x1 + y1*1LL*y1 != 0)?atan2(y1,x1):0;
	ld ang2 = (x2*1LL*x2 + y2*1LL*y2 != 0)?atan2(y2,x2):0;

	ld dang = abs(ang1 - ang2);
	dang = min(dang, 2*M_PI - dang);

	ans += dang * min(r1, r2);
	ans = min(ans, r1 + r2);

	printf("%.18lf\n", (double)ans);
      
    TIMESTAMP(end);
    return 0;
}