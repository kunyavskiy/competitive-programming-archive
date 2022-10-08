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

typedef unsigned int uint;

const int MAXN = 50010;

int p[MAXN];
int coef[MAXN];
uint cnt[MAXN];
uint size[MAXN];
uint size2[MAXN];

vector<int> g[MAXN];
ll total = 0;

void dfs(int v) {
	size[v] = 1;
	for (int i = 0; i < (int)g[v].size(); i++) {
		dfs(g[v][i]);
		size[v] += size[g[v][i]];
		cnt[v] -= size2[g[v][i]];
	}
	size2[v] = size[v] * size[v];
	cnt[v] += size2[v];
	total += cnt[v] * ll(coef[v]);
}

void change_size(int v, uint val) {
	uint val2 = val*val;
	ll total1 = 0;
	total += (int)val2 * coef[v];
	for (; v != -1; v = p[v]) {
		size2[v] += 2 * size[v] * val + val2;
		cnt[v] += 2 * size[v] * val + val2;
		if (p[v] != -1) {
			cnt[p[v]] -= 2 * size[v] * val + val2;
		}
		total1 += 2 * (int)size[v] * ll(coef[v] - (p[v] == -1 ? 0 : coef[p[v]]));
		size[v] += val;
	}
	total += total1 * (int)val;
}

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  	int n;
  	scanf("%d",&n);
  	p[0] = -1;
  	for (int i = 1; i < n; i++) {
  		scanf("%d",&p[i]);
  		--p[i];
  		g[p[i]].pb(i);
  	}
  	for (int i = 0; i < n; i++)
  		scanf("%d",&coef[i]);
  	dfs(0);

  	int m;
  	scanf("%d",&m);
	printf("%.10lf\n",(double)total/n/n);
  	for (int i = 0; i < m; i++) {
  		int u, v;
  		if (scanf(" P %d %d",&v,&u) == 2) {
  			--u, --v;
  			int t;
  			for (t = u; t != v && t; t = p[t]){}
  			if (t == v) swap(u, v);
  			int tmp = size[v];
  			change_size(v, -tmp);
  			p[v] = u;
  			change_size(v, +tmp);
  		} else {
  			assert(scanf(" V %d %d",&u,&v) == 2);
  			--u;
  			total += (v - coef[u]) * (long long)(cnt[u]);
  			coef[u] = v;
  		}
  		printf("%.10lf\n",(double)total/n/n);
  	}

      
    return 0;
}