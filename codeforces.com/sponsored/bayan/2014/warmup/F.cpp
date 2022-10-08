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

#define TASKNAME "F"

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


void compress(vector<pair<int,int>>& xs){
  	sort(xs.begin(), xs.end());
  	xs.erase(unique(xs.begin(), xs.end()), xs.end());
  	xs[0].second = 0;
  	for (int i = 1; i < (int)xs.size(); i++)
  		if (xs[i].first == xs[i-1].first + 1)
  			xs[i].second = xs[i-1].second + 1;
  		else
  			xs[i].second = xs[i-1].second + 2;
}

struct segment{ 
	int l, r, id;
	segment(){}
	segment(int l, int r, int id = -1):l(l), r(r), id(id){}
	bool operator<(const segment& r) const {
		return l < r.l;
	}
};

const int MAXN = 1<<19;
set<segment> tree[MAXN];
bool treeempty[MAXN];
segment s[MAXN];
segment sy[MAXN];
bool alive[MAXN];

void add(int v, int l, int r, int L, int R, segment what, bool rem) {
	if (r < L || R < l) return;
	if (L <= l && r <= R) {
		eprintf("add %d to %d [rem = %d]\n", what.id, v, (int)rem);
		if (rem)
			tree[v].erase(what);
		else
			tree[v].insert(what);
		treeempty[v] = tree[v].empty() && (l == r || (treeempty[2*v] && treeempty[2*v+1]));
		return;
	}
	add(2*v, l, (l+r)/2, L, R, what, rem);
	add(2*v+1, (l+r)/2+1, r, L, R, what, rem);
	treeempty[v] = tree[v].empty() && treeempty[2*v] && treeempty[2*v+1];
}

vector<int> getans;

void get(int v, int l, int r, int L, int R, segment s) {
	if (r < L || R < l) return;
	eprintf("get from %d\n", v);
	if (!tree[v].empty()){
		auto it = tree[v].upper_bound(s);
		if (it != tree[v].begin()) it--;
		if (it->r < s.l) it++;
		while (it != tree[v].end() && it->l <= s.r)
			getans.pb(it->id), it++;
	}
	if (L <= l && r <= R) {
		if (treeempty[v] || l == r) return;
	}
	get(2*v, l, (l+r)/2, L, R, s);
	get(2*v+1, (l+r)/2+1, r, L, R, s);	
}

int lst;





int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

    int n;
    scanf("%d",&n);
  	vector<pair<int, int>> v(n);
  	vector<pair<int,int>> xs, ys;
  	for (auto& x : v) {
  		scanf("%d%d",&x.first, &x.second);
  		xs.pb(mp(x.first, -1));
  		ys.pb(mp(x.second, -1));
  	}
  	compress(xs), compress(ys);
  	for (auto& x : v) {
  		x.first = lower_bound(xs.begin(), xs.end(), mp(x.first,-1))->second;
  		x.second = lower_bound(ys.begin(), ys.end(), mp(x.second,-1))->second;
  	}

  	memset(treeempty, 1, sizeof(treeempty));

  	lst = 2;
  	while (lst <= ys.back().second+1) lst *= 2;

  	eprintf("lst = %d\n", lst);

  	int cnt = 0;
  	int ans = 0;
  	for (auto& x : v) {
		int lx = x.first, rx = lx + 1;
		int ly = x.second, ry = ly + 1;

		while (true) {
			getans.clear();
			get(1, 0, lst-1, ly, ry, segment(lx, rx));
			if (getans.empty()) break;
			sort(getans.begin(), getans.end());
			getans.erase(unique(getans.begin(), getans.end()), getans.end());
			for (int v : getans){
				if (!alive[v]) continue;
				alive[v] = 0;
				ans--;
				add(1, 0, lst-1, sy[v].l, sy[v].r, s[v], true);
				lx = min(lx, s [v].l);
				rx = max(rx, s [v].l);
				ly = min(ly, sy[v].l);
				ry = max(ry, sy[v].l);
			}
		}

		ans++;
		sy[cnt] = segment(ly, ry, cnt);
		s [cnt] = segment(lx, rx, cnt);
		alive[cnt] = true;
		add(1, 0, lst-1, ly, ry, s[cnt], false);
		eprintf("[%d,%d]x[%d,%d]\n", lx, rx, ly, ry);
		cnt++;
		eprintf("================\n");
  	}  	

    printf("%d\n", ans);  
    return 0;
}