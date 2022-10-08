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

const int MAXN = 110000;

vector<int> g[MAXN];
vector<int> w[MAXN];
vector<int> a, b;
vector<int> color;

bool fail;

void dfs(int v, int c) {
	if (color[v] == c) return;
	if (color[v] != -1) {
		fail = true;
		return;
	}
	color[v] = c;
	for (int i = 0; i < (int)g[v].size(); i++)
		dfs(g[v][i], c ^ w[v][i]);
}

void solve(){
	int n, m;
	scanf("%d %d",&n,&m);
	a = vector<int>(n);
	b = vector<int>(n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d",&a[i], &b[i]);
		g[i].clear();
		w[i].clear();
	}
	color = vector<int>(n, -1);
	fail = false;
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d %d",&u,&v);
		u--, v--;
		bool ok0, ok1;
		ok0 = (a[u] > a[v]) || (b[u] > b[v]);
		ok1 = (a[u] > b[v]) || (b[u] > a[v]);
		if (ok0 && ok1) continue;
		if (!ok0 && !ok1) fail = true;
		g[u].pb(v), g[v].pb(u);
		w[u].pb(ok1), w[v].pb(ok1);
	}
	int curc = 0;
	for (int i = 0; i < n; i++)
		if (color[i] == -1)
			dfs(i, curc), curc += 2;
	vector<int> ccnt(curc);
	for (int i = 0; i < n; i++) {
		assert(0 <= color[i] && color[i] < curc);
		ccnt[color[i]]++;
	}
	int ans = 0;
	for (int i = 0; i < curc; i+=2)
		ans = ans + min(ccnt[i], ccnt[i+1]);
	if (fail) 
		printf("-1\n");
	else {
		printf("%d", ans);
		for (int i = 0; i < n; i++)
			if (mp(ccnt[color[i]], color[i]) < mp(ccnt[color[i]^1], color[i]^1))
				printf(" %d", i+1);
		printf("\n");
	}
}

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  	int tst;
  	scanf("%d",&tst);
  	while (tst-->0) {
  		solve();
  	}

      
  return 0;
}