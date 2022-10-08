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

#define TASKNAME "A"

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


const int MAXK = 5000;
const int MAXN = 510;
bitset<MAXK> know[2][MAXN];
bitset<MAXK> have;


vector<int> g[MAXN];
vector<int> how[MAXN];
vector<int> mt;
vector<int> bmt;
vector<bool> used;

int dfs(int v) {
	if (used[v]) return false;
	used[v] = true;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (mt[to] == -1 || dfs(mt[to])) {
			mt[to] = v;
			return true;
		}
	}
	return false;
}


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  	int n, m, k;
  	scanf("%d%d%d",&n,&m,&k);
  	for (int i = 0; i < n; i++) {
  		int cnt;
  		scanf("%d",&cnt);
  		for (int it = 0; it < cnt; it++) {  
  			int x;
  			scanf("%d",&x);
  			x--;
  			know[0][i][x] = 1;
  		}
  		have |= know[0][i];
  	}
  	for (int i = 0; i < m; i++) {
  		int cnt;
  		scanf("%d",&cnt);
  		for (int it = 0; it < cnt; it++) {
  			int x;
  			scanf("%d",&x);
  			x--;
  			know[1][i][x] = 1;
  		}
  	}

  	vector<int> need;
  	for (int i = 0; i < k; i++)
  		if (!have[i])
  			need.pb(i);
  	if ((int)need.size()> m) {
  		printf("2\n");
  		return 0;
  	}
  	eprintf("k=%d\n", k);

	for (int j = 0; j < n; j++)
  		for (int q = 0; q < m; q++) {
  			bitset<MAXK> temp = know[1][q] & ~know[0][j];
  			if (temp.count() != 1)
  				continue;
  			for (int i = 0; i < (int)need.size(); i++)
  				if (temp[need[i]]) {
  					g[j].pb(i), how[j].pb(q);
  					eprintf("%d can %d[%d] by %d\n", j, i, need[i], q);
  				}
  		}
  	
  	mt.resize(need.size(), -1);
  	bmt.resize(n, 0);
  	for (int i = 0; i < n; i++) {
  		used = vector<bool>(n, 0);
  		dfs(i);
  	}

  	for (int i = 0; i < (int)mt.size(); i++)
  		if (mt[i] == -1) {
  			printf("2\n");
  			return 0;
  		} else 
  			bmt[mt[i]] = how[mt[i]][find(g[mt[i]].begin(), g[mt[i]].end(), i) - g[mt[i]].begin()];
  		


	printf("1\n");
	for (int i = 0; i < n; i++)
		printf("%d%c", bmt[i]+1, " \n"[i==n-1]);
    return 0;
}