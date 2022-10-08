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

#define TASKNAME "N"

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


char encode(int x) {
	int y = 0;
//    y = y[:0] + x[0] + y[1:]
//    y = y[:1] + x[4] + y[2:]
//    y = y[:2] + x[3] + y[3:]
//    y = y[:3] + x[1] + y[4:]
//    y = y[:4] + x[2] + y[5:]
    y |= ((x >> 0) & 1) << 0;
    y |= ((x >> 1) & 1) << 4;
    y |= ((x >> 2) & 1) << 3;
    y |= ((x >> 3) & 1) << 1;
    y |= ((x >> 4) & 1) << 2;
    return y + 'a';
}


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif


  int n;
  scanf("%d",&n);

  for (int i = 0; i < n; i++) {
  	int x;
  	scanf("%d",&x);
  	printf("%c", encode(x));
  }
      
  return 0;
}