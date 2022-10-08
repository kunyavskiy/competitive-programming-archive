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

const int MAXN = 510000;

int n;
int prev[MAXN];
int next[MAXN];
int v[MAXN];


int get(int pos) {
	if (prev[pos] == -1 || next[pos] == n) 
		return 0;
	else {
		if (v[pos] < min(v[prev[pos]], v[next[pos]]))
			return 1e9;
		return min(v[prev[pos]], v[next[pos]]);
    }
}


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

    while (scanf("%d",&n) == 1) {
    	for (int i = 0; i < n; i++) {
    		scanf("%d",&v[i]);
    		prev[i] = i - 1;
    		next[i] = i + 1;
    	}

    	set< pair<int, int> > s;
    	s.insert(mp(get(0), 0));
    	s.insert(mp(get(n-1), n - 1));
    	for (int i = 1; i < n - 1; i++) 
    		s.insert(mp(get(i), i));
    	ll ans = 0;
    	while ((int)s.size() > 2) {
    		int pos = (--s.end())->second;
    		assert(0 < pos && pos < n-1);
    		ans += min(v[prev[pos]], v[next[pos]]);
    		s.erase(--s.end());

    		s.erase(mp(get(prev[pos]), prev[pos]));
    		s.erase(mp(get(next[pos]), next[pos]));

    		next[prev[pos]] = next[pos];
    		prev[next[pos]] = prev[pos];

    		s.insert(mp(get(prev[pos]), prev[pos]));
    		s.insert(mp(get(next[pos]), next[pos]));    		    		
    	}
    	printf(LLD"\n", ans);
    }
    return 0;
}