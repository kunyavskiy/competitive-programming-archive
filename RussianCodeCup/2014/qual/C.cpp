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

#define TASKNAME "C"

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


vector<ll> v;

void solve(int n, int m) {
	int tmp = min(n, m);
	v.pb(tmp * 1LL * (tmp - 1) / 2);
	v.pb(n * 1LL * m - tmp - v.back());
}

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif


  int tst;
  scanf("%d",&tst);

  while (tst-->0){
  	 int n,m,x,y;
  	 scanf("%d %d %d %d",&n,&m,&x,&y);
  	 v.clear();
  	 solve(x - 1, y - 1);
  	 solve(x - 1, m - y);
  	 solve(n - x, y - 1);
  	 solve(n - x, m - y);
  	 sort(v.rbegin(),v.rend());
  	 while (!v.empty() && v.back() == 0) v.pop_back();
  	 sort(v.begin(), v.end());
  	 printf("%d", v.size());
  	 for (int i = 0; i < (int)v.size(); i++)
  	 	printf(" "LLD, v[i]);
  	 printf("\n");
  }

      
  return 0;
}