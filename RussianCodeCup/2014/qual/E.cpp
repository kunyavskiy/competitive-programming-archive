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

#define ws ws_i_love_std

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

#define TASKNAME "E"

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

const int MAXN = 5e5;

vector<int> g[MAXN];
vector<int> l[MAXN];
vector<int> r[MAXN];
int sz[MAXN];
int n,m;

struct item {
	int w, l, r;
	item(int w, int l, int r):w(w), l(l), r(r){};
};

vector<item> ws;


int dfs(int v, int p){
	sz[v] = 1;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (to == p) continue;
		int tmp = dfs(to, v);
		ws.pb(item(min(m + 1LL , tmp * 2LL * (n - tmp)), l[v][i], r[v][i]));
		sz[v] += tmp;
	}
	return sz[v];
}

const int MOD = 1000000007;

void solve(){
	for (int i = 0; i < n; i++)
		g[i].clear(), l[i].clear(), r[i].clear();
	ws.clear();	
  	for (int i = 0; i < n - 1; i++) {
  		int a, b, l, r;
  		scanf("%d %d %d %d",&a,&b,&l,&r);
  		--a, --b;
  		g[a].pb(b), ::l[a].pb(l), ::r[a].pb(r);
  		g[b].pb(a), ::l[b].pb(l), ::r[b].pb(r);
  	}

  	dfs(0, -1);
  	int tot = 0;
  	for (int i = 0; i < (int)ws.size(); i++) {
  		tot = min(m + 1LL, tot + ws[i].w * 1LL * ws[i].l);
//  		eprintf("%d %d %d\n", ws[i].w, ws[i].l, ws[i].r);
  	}
  	eprintf("%d\n", tot);
  	if (tot > m) {
  		printf("0\n");
  		return;
  	}

//  	eprintf("\n\n");

  	vector<int> dp(m+1);
  	dp[0] = 1;
  	int minv, maxv;
  	minv = maxv = 0;
  	for (int i = 0; i < (int)ws.size(); i++) {
  		maxv = min(m * 1LL, maxv + ws[i].w * 1LL* ws[i].r);
  		vector<int> sums(m+1);
  		for (int j = minv; j <= maxv; j++){
  			int lf = max(-1LL, j - (ws[i].r + 1) * 1LL * ws[i].w);
  			int rg = max(-1LL, j - ws[i].l * 1LL * ws[i].w);
  			sums[j] = (j < ws[i].w ? 0 : sums[j - ws[i].w]) + dp[j];
  			if (sums[j] >= MOD) sums[j] -= MOD;
  			dp[j] = (rg == -1 ? 0 : sums[rg]) - (lf == -1 ? 0 : sums[lf]);
  			if (dp[j] < 0) dp[j] += MOD;
  		}
  		minv += ws[i].w * ws[i].l;
  	}
  	printf("%d", dp[m]);

}


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  	while (scanf("%d %d",&n,&m) == 2)
	  	solve();
      
    return 0;
}