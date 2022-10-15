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

#define TASKNAME "1710"

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
typedef double ld;

#undef assert
#define assert(x) if (!(x)) { int t = 1/ 0; printf("%d\n", t);}



ld dist(int* x, int* y, int i, int j){
	return sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
}

int dist2(int* x, int* y, int i, int j){
	return (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
}


ld angle(int* x, int* y, int i, int j, int k){
	return acos(((x[j] - x[i]) * (x[k] - x[i]) + (y[j] - y[i]) * (y[k] - y[i]))/ dist(x, y, i, j) / dist(x, y, i, k));
}

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

	int x[3], y[3];
	for (int i = 0; i < 3; i++)
		scanf("%d %d",&x[i],&y[i]);


	if (dist2(x, y, 1, 2) >= dist2(x, y, 0, 1) || dist2(x,y,0,1) == dist2(x,y,1,2) + dist2(x,y,0,2)) {
		printf("YES\n");
	} else {
		printf("NO\n");
		ld cang = angle(x, y, 2, 0, 1);
		ld aang = angle(x, y, 0, 1, 2);
		ld bang = cang - aang;
		assert(bang > 1e-9);
		printf("%.18lf %.18lf\n", cos(bang)*dist(x, y, 0, 1),sin(bang)*dist(x, y, 0, 1));
		printf("%.18lf %.18lf\n", 0.0, 0.0);
		printf("%.18lf %.18lf\n", dist(x, y, 1, 2), 0.0);
	}
		

      
    return 0;
}