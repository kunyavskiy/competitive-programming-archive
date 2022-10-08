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


struct Dsu {
	vector<int> p;
	vector<int> size;

	Dsu(int n): p(n, 0), size(n, 1) {}

	void join(int a, int b) {
		a = get(a);
		b = get(b);
		p[a] = b;
		size[b] += size[a];
	}

	int get(int a) {
		if (a == p[a]) return a;
		return p[a] = get(p[a]);
	}
};

const int MAXN = 2100;
Dsu dsu;
vector<int> g[MAXN];
int tin[MAXN];
int tup[MAXN];

void dfs(int v, int p) {
	tin[v] = timer++;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (to == p) continue;
		if (tin[to] != -1) {
			dsu.join(to, v);
			tup[v] = min(tup[v], tin[to]);
			continue;
		}
		dfs(to, v);
		tup[v] = min(tup[v], tup[to]);
		if (tup[to] > tin[v])
			dsu.join(to, v);
	}
}


vector<int> g2[MAXN];
vector<int> size[MAXN];

const int INF = (int)1e9;


pair<int, int> calc(int v, int p) {
	pair<int, int> ans = mp(size[v] * size[v], size[v]);
	for (int to : g2[v]) {
		if (to == p) continue;
		pair<int, int> ans2 = calc(to, v);
		ans.second += ans2.second;
		ans.first 
	}
}

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif
  	memset(tin, -1, sizeof(tin));
  	int n, m;
  	scanf("%d%d",&n,&m);
  	dsu = Dsu(n);

  	for (int i = 0; i < m; i++) {
  		int a, b;
  		scanf("%d%d",&a,&b);
  		--a,--b;
  		g[a].pb(b);
  		g[b].pb(a);
  	}

  	dfs(0, -1);


  	for (int i = 0; i < n; i++){
  		size[i] = dsu.size(i);
  		for (int to : g[v][i])
  			if (dsu.get(i) != dsu.get(to)) {
  				g[dsu.get(i)].pb(dsu.get(to));
  				g[dsu.get(to)].pb(dsu.get(i));
  			}		
  	}

  	int ans = 0;
  	for (int i = 0; i < n; i++)
  		if (dsu.get(i) == i)
  			ans = max(ans, calc(i, -1));

  	printf("%d\n", ans);      
    return 0;
}