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

const int MAXN =  100000;

vector<int> g[MAXN];
vector<int> ans;
bool needout;

int dfs(int v, int p = -1) {
	vector<int> undone;
	bool any = false;
//	bool have2 = false;
	for (int j = 0; j < (int)g[v].size(); j++){
		int u = g[v][j];
		if (u == p) continue;
		int temp = dfs(u, v);
//		if (temp == -2)
//			have2 = true;
		if (temp >= 0)
			undone.pb(temp);
		else
			any = true;
	}

	if (undone.size() > 1) {
		for (int i = 1; i < (int)undone.size(); i++)
			ans.pb(undone[i]);
		needout = true;
		any = true;
//		have2 = false;
	}
//	eprintf("%d %d %d\n", p, undone.size(), needout);
//	if (p == -1 && undone.size() == 1 && g[v].size() == 2 && have2)
//		ans.pb(undone[0]);
//	if (undone.size() == 0 && g[v].size() == 1 && have2) return -2;
//	if (undone.size() == 1 && g[v].size() == 1 && have2) return -2;
//	if (undone.size() > 1) return -2;
	if (any) return -1;
	if (undone.size() == 1)
		return undone[0];
	return v;		
}


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  	int n;
  	scanf("%d",&n);
  	for (int i = 0; i < n-1; i++) {
  		int a, b;
  		scanf("%d %d",&a,&b);
  		--a, --b;
  		g[a].pb(b);
  		g[b].pb(a);
  	}

  	if (n == 2) {
  		printf("1\n1\n");
  		return 0;
  	}

  	for (int i = 0; i < n; i++)
  		if (g[i].size() >= 3) {
  			dfs(i);
  			assert(ans.size());
  			printf("%d\n", ans.size());
  			for (int j = 0; j < (int)ans.size(); j++)
  				printf("%d ", ans[j]+1);
  			printf("\n");
  			return 0;
  		}
  	for (int i = 0; i < n; i++)
  		if (g[i].size() == 1) {
  			printf("1\n%d\n", i+1);
  			return 0;
  		}
  	
  	assert(false);
      
    return 0;
}