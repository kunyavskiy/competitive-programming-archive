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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "KMHAMHA"

#ifdef LOCAL
static struct __timestamper {
	~__timestamper(){
		TIMESTAMP(end);
	}
} __TIMESTAMPER;
#endif

typedef long long ll;
typedef long double ld;

const int MAXN = 1100;

vector<int> g[MAXN];
int mt[MAXN];
bool used[MAXN];

bool dfs(int v){
    if (used[v]) return false;
    used[v] = true;
    for (int i = 0; i < (int)g[v].size(); i++){
    	int to = g[v][i];
    	if (mt[to] == -1 || dfs(mt[to])){
    		mt[to] = v;
    		return true;
    	}    		
    }
    return false;
}

void solve(){
	int n;
	scanf("%d",&n);
	map<int,int> xs,ys;

	for (int i = 0; i < n; i++){
		int x,y;
		scanf("%d %d",&x,&y);
		if (xs.find(x) == xs.end()){
	    	int tmp = xs.size();
	    	xs[x] = tmp;
	    	g[tmp].clear();
		}
		x = xs[x];
		if (ys.find(y) == ys.end()){
	    	int tmp = ys.size();
	    	ys[y] = tmp;
	    	mt[tmp] = -1;
		}
		y = ys[y];
		g[x].pb(y);
	}

	int ans = 0;

	for (int i = 0; i < (int)xs.size(); i++){
		memset(used, 0, sizeof(used[0]) * xs.size());
		ans += dfs(i);
	}
	printf("%d\n", ans);	
}

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

    int t;
    scanf("%d",&t);
    while (t-->0) solve();
      
  return 0;
}