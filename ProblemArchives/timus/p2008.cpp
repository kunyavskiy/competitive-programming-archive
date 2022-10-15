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

#define TASKNAME "2008"

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

const int g = 98;
const double lg = 9.8;
int v;

bool can(ll x, ll y){
	eprintf("%lf < %lf\n", (x * x + y * y)* lg * lg , (v*v - y * lg) * (v*v - y * lg));
	bool res =  (x * x + y * y) * g * g <= (10LL * v * v - y * g) * (10LL * v * v - y * g) && 10L*v*v - y*g >= 0;
//	eprintf("res = %d\n\n", (int)res);
	return res;
}


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

    int x1, y1, x2, y2, x3, y3;
    scanf("%d%d%d%d%d%d%d",&v,&x3,&y3,&x1,&y1,&x2,&y2);

    if (can(x1 - x2, y1 - y2) && can(x2 - x1, y2 - y1) && (can(x3 - x1, y3 - y1) || can(x3 - x2, y3 - y2)))
    	puts("Yes\n");
    else	
    	puts("No\n");      
  return 0;
}