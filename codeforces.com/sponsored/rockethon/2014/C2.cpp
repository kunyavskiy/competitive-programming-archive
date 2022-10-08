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


const int MAXN = 210000;

int p[MAXN];
int e[MAXN];
int n,k;

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif
    scanf("%d%d",&n,&k);
    --k;

    for (int i = 0; i < n; i++) 
    	scanf("%d%d",&p[i], &e[i]);

    ll ans = 1LL<<60;

    
    for (int i = 0; i <= n; i++){
    	vector<int> ty1, ty2;
    	int win = 0;
    	for (int j = 0; j < n; j++)
    		if (p[j] > i)
    			ty1.pb(e[j]), win++;
    		else if (p[j] < i - 1)
    			ty1.pb(e[j]);
    		else
    			ty2.pb(e[j]);

    	int canlose = k - win;

    	if (canlose < 0) continue;
    	canlose = min(canlose, (int)ty2.size());
    	int needwin = (int)ty2.size() - canlose;    
    	if (needwin > i) continue;

    	if (needwin != 0) eprintf("%d\n", needwin);
    	sort(ty2.begin(), ty2.end());
    	ll curans = 0;
    	for (int j = 0; j < (int)ty2.size(); j++)
    	    if (j < needwin)
    	    	curans += ty2[j];
    	    else
    	    	ty1.pb(ty2[j]);
    	sort(ty1.begin(), ty1.end());
    	for (int j = 0; j + needwin < i; j++)
    		curans += ty1[j];
    	ans = min(ans, curans);	
    }

    if (ans == (1LL<<60))
    	ans = -1;

    printf(LLD"\n", ans);
      
    return 0;
}