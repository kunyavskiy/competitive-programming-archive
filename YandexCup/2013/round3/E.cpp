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

#define TASKNAME "E"

typedef long long ll;
typedef long double ld;

const int MAXN = 100010;

vector<int> g[MAXN];
vector<int> gt[MAXN];

int cost[MAXN];
int comp[MAXN];
bool used[MAXN];

vector<int> ts;

void tops(int v){
	used[v] = true;
	for (int i = 0; i < (int)g[v].size(); i++){
		if (!used[g[v][i]])
			tops(g[v][i]);
	}
	ts.pb(v);
}

void dfs(int v,int c){
//	eprintf("%d %d\n",v,c);
	if (comp[v] != -1) return;
	comp[v] = c;
	for (int i = 0; i < (int)gt[v].size(); i++)
		dfs(gt[v][i],c);	
}

int d[MAXN];




int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
  	
  	int n,m;
  	scanf("%d %d",&n,&m);
  	for (int i = 0; i < n; i++)
  		scanf("%d",&cost[i]), comp[i] = -1;
  	cost[0] = 0;

  	for (int i = 0; i < m; i++){
  		int a,b;
  		scanf("%d %d",&a,&b);
  		--a,--b;
  		g[b].pb(a);
  		gt[a].pb(b);
  	}

  	for (int i = 0; i < n; i++)
  		if (!used[i])
	  		tops(i);

	assert((int)ts.size() == n);
	for (int i = n-1; i > 0; i--){
		dfs(ts[i], i);
	}

	for (int i = 0; i < n; i++)
		d[i] = 1 << 30;

	d[n-1] = 0;
	set<pair<int,int> > s;
	s.insert(mp(0, n-1));

	while (!s.empty()){
		int v = s.begin()->second;
		s.erase(s.begin());
		for (int i = 0; i < (int)g[v].size(); i++){
			int to = g[v][i];
			int nd = d[v] + cost[v] * (comp[v] != comp[to] || to == 0);
			if (d[to] > nd){
				s.erase(mp(d[to], to));
				d[to] = nd;
				s.insert(mp(d[to], to));
			}
		}
	}

	printf("%d\n", d[0]);
      
    TIMESTAMP(end);
    return 0;
}