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

#define TASKNAME "1781"

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

int g[110][110];

int was[110];
vector<int> ts;
vector<int> res;
int n;

void dfs(int v){
	if (was[v] == 2) return;
	if (was[v] == 1){
		printf("-1\n");
		exit(0);
	}
	was[v] = 1;
	for (int i = 0; i < n; i++)
		if (g[v][i])
			dfs(i);
	was[v] = 2;
	ts.pb(v);
}


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif
  	scanf("%d",&n);
  	for (int i = 0; i < n; i++) {
  		for (int j = 0; j < n; j++)
  			scanf("%d",&g[i][j]);
  		g[i][i] = 0;
  	}

  	for (int i = 0; i < n; i++)
  		dfs(i);
  	reverse(ts.begin(), ts.end());
  	res = vector<int>(n);
  	for (int i = 0; i < n; i++)
  		res[i] = i;

  	vector<pair<int, int> > v;

  	for (int i = 0; i < n; i++)
  		if (res[i] != ts[i]){
  			for (int j = 0; j < n; j++)
  				if (res[j] == ts[i]){
  					v.pb(mp(i, j));
  					swap(res[i], res[j]);
  					break;
  				}
  		}
    printf("%d\n", v.size());
    for (int i = 0; i < (int)v.size(); i++)
    	printf("%d %d\n", v[i].first + 1, v[i].second + 1);  
    return 0;
}