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

#define TASKNAME "2003"

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




int main(){              
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

    int n;
    scanf("%d",&n);

    vector<int> ps;
    for (int i = 0; i < n; i++){
    	int x;
    	scanf("%d",&x);
    	for (int j = 2; j * j <= x; j++){
    		if (x % j == 0){
    			ps.pb(j);
    			while (x % j == 0) x /= j;
    		}
    	}
    	if (x > 1) ps.pb(x);
    }

    sort(ps.begin(), ps.end());
    int ans = !ps.empty();
    for (int i = 0; i < (int)ps.size() - 1; i++)
    	if (ps[i] == ps[i+1]) ans = 2;
    for (int i = 0; i < (int)ps.size() - 2; i++)
    	if (ps[i] == ps[i+2]) ans = 3;

    if (ans == 3)
    	printf("infinity");
    else
    printf("%d\n", ans);
      
    return 0;
}