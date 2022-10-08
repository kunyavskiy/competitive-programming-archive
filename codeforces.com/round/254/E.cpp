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

const int inf = 1e9;

vector<int> isums(vector<int> v) {
	vector<int> res(v.size()+1);
	for (int i = 0; i < (int)v.size(); i++)
		res[i+1] = res[i] + (v[i] >= 0);
	return res;
}

struct Item {
	int tot;
	int size;
	vector<int> dp;

	void swap(Item& r) {
		::swap(tot, r.tot);
		::swap(size, r.size);
		dp.swap(r.dp);
	}

	void mergeMe(Item& r, int val) {
		if (dp.size() < r.dp.size()) swap(r);
		tot += r.tot;
		size += r.size;
//		vector<int> lf = isums(dp);
//		vector<int> rg = isums(r.dp);
		vector< vector<int> > add(dp.size() + r.dp.size() - 1);
		vector< vector<int> > rem(dp.size() + r.dp.size() - 1);
		for (int i = 0; i < (int)dp.size(); i++)
			for (int j = 0; j < (int)r.dp.size(); j++) {
				int cnt = min(size - i, r.tot - j) + min(r.size - j, tot - i);
				add[i+j].pb(min(dp[i], r.dp[j]));
				rem[i+j+cnt].pb(min(dp[i], r.dp[j]));
			}
		dp = vector<int>(dp.size() + r.dp.size() - 1, -inf);
		multiset<int> s;
		for (int i = 0; i < (int)dp.size(); i++) {
			for (int j = 0; j < (int)add[i].size(); j++)
				s.insert(add[i][j]);
			for (int j = 0; j < (int)rem[i].size(); j++)
				s.erase(s.find(rem[i][j]));
			if (!s.empty()) dp[i] = *(--s.end());
		}
		for (int i = 1; i < (int)dp.size(); i++)
			dp[i] = min(dp[i], val);

	}
	Item(int val) {
		tot = val;
		size = 1;
		dp.resize(2);
		dp[0] = inf;
		dp[1] = 0;
	}
};

struct Dsu {
	vector<Item> v;
	vector<int> p;

	Dsu(vector<int> vals) {
		int n = vals.size();
		for (int i = 0; i < n; i++) {
			v.pb(Item(vals[i]));
			p.pb(i);
		}
	}

	int get(int x) {
		if (p[x] == x) return x;
		return p[x] = get(p[x]);
	}

	void join(int a, int b, int val) {
		a = get(a);
		b = get(b);
		assert(a != b);
		p[a] = b;
		v[b].mergeMe(v[a], val);
	}

	void print(int a) {
		a = get(a);
		vector<int> x = v[a].dp;
		for (int i = 0; i < (int)x.size(); i++)
			eprintf("%d ", x[i]);
		eprintf("; tot = %d\n", v[a].tot);
	}
};



int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

    int n;
    while (scanf("%d",&n) == 1) {
    	int m = n - 1;
	  	vector< pair<int, pair<int, int> > >  es(m);
	  	vector<int> xs(n);
  		for (int i = 0; i < m; i++)
  			scanf("%d %d %d",&es[i].first, &es[i].second.first, &es[i].second.second);
  		sort(es.begin(), es.end());
  		for (int i = 0; i < n; i++)
  			scanf("%d",&xs[i]);
  		Dsu dsu(xs);
  		for (int i = 0; i < m; i++) {
  			dsu.print(es[i].second.first - 1);
  			dsu.print(es[i].second.second - 1);
  			dsu.join(es[i].second.first - 1, es[i].second.second - 1, es[i].first);
  			dsu.print(es[i].second.second - 1);
  			eprintf("\n");
  		}
  		printf("%d\n", dsu.v[dsu.get(0)].dp[n]);
  	}

      
  return 0;
}