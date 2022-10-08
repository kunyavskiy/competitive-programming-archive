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

#define TASKNAME "B"

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


int n,m,cnt;

void solve(){
	for (int i = 0; i < 9; i++)
	for (int j = i+1; j < 9; j++)
 	for (int k = j+1; k < 9; k++){
 		int n = ::n;
 		int m = ::m;
 		if (i % 3 >= m || i / 3 >= n) continue;
 		if (j % 3 >= m || j / 3 >= n) continue;
 		if (k % 3 >= m || k / 3 >= n) continue;

 		vector<int> xs, ys;
 		xs.pb(i / 3), xs.pb(j / 3), xs.pb(k / 3);
 		ys.pb(i % 3), ys.pb(j % 3), ys.pb(k % 3);

 		sort(xs.begin(), xs.end()), xs.erase(unique(xs.begin(), xs.end()), xs.end());
 		sort(ys.begin(), ys.end()), ys.erase(unique(ys.begin(), ys.end()), ys.end());

 		ll tot = ll(n) * ys.size() + ll(m) * xs.size() - xs.size() * ys.size() - 3;
 		
 		if (tot == cnt){
 			printf("%d %d %d %d %d %d\n", i / 3 + 1, i % 3 + 1, j / 3 + 1, j % 3 + 1, k / 3 + 1, k % 3 + 1);
 			return;
 		}
 	}
 	printf("IMPOSSIBLE\n");
}

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

     int tst;
     scanf("%d",&tst);
     while (tst-->0) {
     	scanf("%d %d %d",&n,&m,&cnt);
     	solve();
     }
      
  return 0;
}