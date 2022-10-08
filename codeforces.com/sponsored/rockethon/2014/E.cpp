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


class Solver {
	int n;
	vector< vector<int> > g;
	vector< vector<ll> > w;
	vector<ll> w1;
	vector<ll> w2;

	int addv(){
		g.pb(vector<int>());
		w.pb(vector<ll>());
		return n++;
	}

public:

	Solver(int n):n(n),g(n), w(n), w1(n),w2(n){}
	void adde(int u, int v, ll len){        
		g[u].pb(v);w[u].pb(len);
		g[v].pb(u);w[v].pb(len);
	}

	void setw(int u, int ty, ll len){
		if (ty) w1[u] = len;
		else w2[u] = len;
	}

	ll best;

	pair<ll,ll> dfs(int v, int p){
		pair<ll,ll> res;
		res = mp(w1[v], w2[v]);
		best = max(best, w1[v] + w2[v]);
		for (int i = 0; i < (int)g[v].size(); i++){
			int to = g[v][i];
			if (to == p) continue;
			pair<ll,ll> dn = dfs(to, v);
			dn.first += w[v][i];
			dn.second += w[v][i];
//			eprintf("v = %d, to = %d "LLD" "LLD" "LLD" "LLD"\n",  v, to, res.first, res.second, dn.first, dn.second);
			best = max(best, dn.first + res.second);
			best = max(best, dn.second + res.first);
			res.first = max(res.first, dn.first);
			res.second = max(res.second, dn.second);
		}
		return res;
	}

	ll solve(){
		best = 0;
		dfs(0, -1);
		return best;
	}
};

const int MAXN = 110000;


int n[3];
vector<int> g[3][MAXN];
vector<int> sz[3];
vector<ll> sumd[3];


void dfs1(int gr, int v, int p){
	sz[gr][v] = 1;
	for (int i = 0; i < (int)g[gr][v].size(); i++){
		int to = g[gr][v][i];
		if (to == p) continue;
		dfs1(gr, to, v);
		sz[gr][v] += sz[gr][to];
		sumd[gr][v] += sumd[gr][to] + sz[gr][to];
	}
}

void dfs2(int gr, int v, int p){
	for (int i = 0; i < (int)g[gr][v].size(); i++){
		int to = g[gr][v][i];
		if (to == p) continue;
		sumd[gr][to] = sumd[gr][v] - sz[gr][to] + (n[gr] - sz[gr][to]);
		dfs2(gr, to, v);
	}
}



int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  	scanf("%d%d%d",&n[0],&n[1],&n[2]);

  	for (int i = 0; i < 3; i++){
  		for (int j = 0; j < n[i] - 1; j++){
  			int u, v;
  			scanf("%d%d",&u,&v);
  			--u, --v;
  			g[i][u].pb(v);
  			g[i][v].pb(u);
  		}
  		sz[i] = vector<int>(n[i]);
  		sumd[i] = vector<ll>(n[i]);
  		dfs1(i, 0, -1);
  		dfs2(i, 0, -1);
  	}

  	ll best = 0;

  	for (int mid = 0; mid < 3; mid++){
//  		if (mid != 0) continue;
  		ll ans = 0;
  		vector<int> other;
  		for (int j = 0; j < 3; j++)	
  			if (j != mid) {
  				ans += *max_element(sumd[j].begin(), sumd[j].end()) * (n[0] + n[1] + n[2] - n[j]);
//  				eprintf(LLD"\n", ans);
  				other.pb(j);
  			}

  		Solver s(n[mid]);

  		ans += n[other[0]] * 1LL * (n[other[1]] + n[mid]);
  		ans += n[other[1]] * 1LL * (n[other[0]] + n[mid]);
//  		eprintf(LLD"\n", ans);


  		for (int i = 0; i < n[mid]; i++){
  			s.setw(i, 0, sumd[mid][i] * n[other[0]]);
  			s.setw(i, 1, sumd[mid][i] * n[other[1]]);
  			for (int j = 0; j < (int)g[mid][i].size(); j++)
  				if (i <= g[mid][i][j])
	  				s.adde(i, g[mid][i][j], n[other[0]] * 1LL * n[other[1]]);
  		}


  		ans += s.solve();
//  		eprintf("s.solve() = "LLD"\n", s.solve());
//		eprintf(LLD"\n", ans);
  		best = max(best, ans);  			
  	}


  	ll add = 0;
  	for (int i = 0; i < 3; i++)
  		for (int j = 0; j < n[i]; j++)
	  		add += sumd[i][j];

	assert(add % 2 == 0);
	add /= 2;

	best += add;

	printf(LLD"\n", best);
    return 0;
}