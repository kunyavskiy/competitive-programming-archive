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

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "A"

#ifdef LOCAL
static struct __timestamper {
    string what;
    __timestamper(const char* what) : what(what){};
    __timestamper(const string& what) : what(what){};
	~__timestamper(){
        TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;


bool check(int hp1, int at1, int def1, int hp2, int at2, int def2) {
	int dec1 = max(0, at2 - def1);
	int dec2 = max(0, at1 - def2);
	if (dec2 == 0) return false;
	int days = (hp2 + dec2 - 1) / dec2;
	return hp1 - days * dec1 > 0;
}

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif
  
  	int hp[2], atk[2], def[2];
  	int cost[3];
  	for (int i = 0; i < 2; i++)
  		scanf("%d%d%d",&hp[i], &atk[i], &def[i]);
  	for (int i = 0; i < 3; i++)
  		scanf("%d",&cost[i]);

  	int ans = 0x7fffffff;
  	for (int da = 0; da <= 10000; da++)
  	for (int db = 0; db <= 200; db++)
  	for (int dc = 0; dc <= 200; dc++)
  		if (check(hp[0] + da, atk[0] + db, def[0] + dc, hp[1], atk[1], def[1])) {
  			if (da * cost[0] + db * cost[1] + dc * cost[2] == 1990 && ans != 1990)
  				eprintf("%d %d %d\n", da, db, dc);
  			ans = min(ans, da * cost[0] + db * cost[1] + dc * cost[2]);
  		}

    printf("%d\n", ans);  
    return 0;
}