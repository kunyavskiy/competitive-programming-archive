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

#define next next_i_love_std

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

#define TASKNAME "1772"

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

int next[2][MAXN];
int cost[2][MAXN];

ll dp[MAXN];

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  int ptr = 1;
  set<pair<int, int> > s;
  int n, st, k;
  scanf("%d %d %d",&n,&st,&k);
  s.insert(mp(st, 0));

  for (int i = 0; i < k; i++){
  	int l, r;
  	scanf("%d %d",&l,&r);
  	int vl = (l == 1 ? -1 : ptr++);
	int vr = (r == n ? -1 : ptr++);
	while (true){
		set<pair<int, int> > :: iterator it = s.lower_bound(mp(l, -1));
		if (it == s.end() || it->first > r) break;
		next[0][it->second] = vl; cost[0][it->second] = abs(it->first - (l - 1));
		next[1][it->second] = vr; cost[1][it->second] = abs(it->first - (r + 1));
		s.erase(it);
	}
	if (vl != -1) s.insert(mp(l-1, vl));
	if (vr != -1) s.insert(mp(r+1, vr));
  }

  for (set<pair<int,int> >::iterator it = s.begin(); it != s.end(); it++) {
  	  next[0][it->second] = -2;
  }

  memset(dp, 1, sizeof(dp));
  dp[0] = 0;
  ll ans = 1e18;

  for (int i = 0; i < ptr; i++){
  	if (next[0][i] == -2) {
  		ans = min(ans, dp[i]);
  		continue;
  	}
  	for (int j = 0; j < 2; j++)
  		if (next[j][i] != -1)
  			dp[next[j][i]] = min(dp[next[j][i]], dp[i] + cost[j][i]);
  }

  printf(LLD"\n", ans);

      
  return 0;
}