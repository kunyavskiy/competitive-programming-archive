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

#define ends ends_i_love_std

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "D"

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

int n, m;
vector<int> a;
vector<int> b;

vector<int> ends;
vector<int> starts;
vector<int> sums;

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

    while (scanf("%d%d",&n,&m) == 2){
    	a = vector<int>(n);
    	b = vector<int>(m);
    	for (int i = 0; i < n; i++)
    		scanf("%d",&a[i]);
    	for (int i = 0; i < m; i++)
    		scanf("%d",&b[i]);
    	sort(a.begin(), a.end());
    	sort(b.begin(), b.end());
    	for (int i = 0; i < n; i++){
    		if (i == 0 || a[i] != a[i-1] + 1) starts.pb(i);
    		if (i == n-1 || a[i] + 1 != a[i+1]) ends.pb(i);
    	}
    	vector<int> dp(m+1, n+1);
    	dp[0] = 0;
    	for (int i = 0; i < m; i++){
    		for (int j = m; j > 0; j--) {
    			if (dp[j-1] == n+1) continue;
    			int id = lower_bound(a.begin(), a.end(), b[j]) - a.begin();
    			if (id != n) {
    				vector<int>::iterator iter = lower_bound(ends.begin(), ends.end(), id);
    				assert(iter != ends.end());
    				if (a[id] - (*iter - dp[j-1]) <= b[i])
    					dp[j] = min(dp[j], *iter + 1);
    			}
    			id--;
    			if (id == -1) continue;
    			if (id < dp[j] - 1) ct
    			id += b[j] - a[id];
    			if (id >= n) continue;
  				vector<int>::iterator iter = lower_bound(ends.begin(), ends.end(), id);
  				assert(iter != ends.end());
				dp[j] = min(dp[j], *iter + 1);
    		}
    	}

    	for (int i = m; ; i--)
    		if (dp[i] <= n){
    			printf("%d\n", i);
    			break;
    		}
    }

      
  return 0;
}