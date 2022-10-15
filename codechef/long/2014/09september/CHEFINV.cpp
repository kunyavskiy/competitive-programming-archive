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

#define TASKNAME "CHEFINV"

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


struct Req {
	int x, l, r, coef;
	ll* to;
	Req(int x, int l, int r, int coef, ll& to) : x(x), l(l), r(r), coef(coef), to(&to) {}
	bool operator<(const Req& r) const {
		return x < r.x;
	}
};

vector<Req> rs;

vector<int> a;
vector<ll> ans;
ll tot;

vector<int> bit;

ll get(int r) {
	ll ans = 0;
	for (; r != -1; r = (r & (r + 1)) - 1)
		ans += bit[r];
	return ans;
}

ll get(int l, int r) {
	return get(r) - get(l - 1);
}

void upd(int r) {
	for (; r < (int)bit.size(); r = (r | (r+1)))
		bit[r]++;
}


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  	int n, m;
  	scanf("%d%d",&n,&m);
  	a.resize(n);
  	ans.resize(m);
  	bit.resize(n);
  	for (int i = 0; i < n; i++)
  		scanf("%d",&a[i]);

  	{
  	vector<int> as = a;
  	sort(as.begin(), as.end());
  	as.erase(unique(as.begin(), as.end()), as.end());
  	for (int i = 0; i < n; i++)
  		a[i] = lower_bound(as.begin(), as.end(), a[i]) - as.begin();
  	}

  	for (int i = 0; i < n; i++)
  		if (a[i] != n-1)
	  		rs.pb(Req(i, a[i]+1, n-1, 1, tot));
	for (int i = 0; i < m; i++) {
		int l, r;
		scanf("%d %d",&l, &r);
		--l, --r;
		if (l > r) swap(l, r);
		if (a[l] < a[r]) {
			rs.pb(Req(l, a[l], a[l], -1, ans[i]));
			rs.pb(Req(r, a[l], a[l], +1, ans[i]));
			rs.pb(Req(l, a[r], a[r], -1, ans[i]));
			rs.pb(Req(r, a[r], a[r], +1, ans[i]));
			rs.pb(Req(l, a[l]+1, a[r]-1, -2, ans[i]));
			rs.pb(Req(r, a[l]+1, a[r]-1, +2, ans[i]));
		} else if (a[r] < a[l]) {
			rs.pb(Req(l, a[r], a[r], +1, ans[i]));
			rs.pb(Req(r, a[r], a[r], -1, ans[i]));
			rs.pb(Req(l, a[l], a[l], +1, ans[i]));
			rs.pb(Req(r, a[l], a[l], -1, ans[i]));
			rs.pb(Req(l, a[r]+1, a[l]-1, +2, ans[i]));
			rs.pb(Req(r, a[r]+1, a[l]-1, -2, ans[i]));
		}
	}
	sort(rs.begin(), rs.end());
	int ptr = 0;

	for (int i = 0; i < n; i++) {
		while (ptr < (int)rs.size() && rs[ptr].x == i) {
			*rs[ptr].to += rs[ptr].coef * get(rs[ptr].l, rs[ptr].r);
			ptr++;
		}
		upd(a[i]);
	}

	eprintf("tot = "LLD"\n", tot);

	for (int i = 0; i < m; i++)
		printf(LLD"\n", ans[i] + tot);
      
    return 0;
}