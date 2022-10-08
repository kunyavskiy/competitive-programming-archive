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


vector<int> f[2];
map<int, int> cnt[2];

int ans = 0;
ll aways;

void update(int res, ll ways){
//	eprintf("%d %I64d\n", res, ways);
	if (ans > res) return;
	if (ways <= 0) return;
	if (ans < res) ans = res, aways = 0;
	aways += ways;
}

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif
  	int n,m;
  	scanf("%d %d",&n, &m);


  	for (int i = 0; i < m; i++){
  		int s, t;
  		scanf("%d %d",&s,&t);
  		f[s].pb(t);
  		cnt[s][t]++;
  	}

  	for (int j = 0; j < 2; j++) {
  		sort(f[j].begin(), f[j].end());
  		if (f[j].empty()) continue;
  		if (f[j].back() == f[j][0])
			update(2*(f[j].back() - f[j][0]), f[j].size() * 1LL * (f[j].size() - 1)* 1LL *(f[j].size() - 2) / 6);
		else 
			update(2*(f[j].back() - f[j][0]), cnt[j][f[j][0]] * 1LL * cnt[j][f[j].back()] * 1LL * (f[j].size() - 2) -
			  cnt[j][f[j][0]] * 1LL * cnt[j][f[j].back()] * 1LL * (cnt[j][f[j][0]] + cnt[j][f[j].back()] - 2));
  	}

	for (int step = 0; step < 2; step++){
		f[0].swap(f[1]);
		cnt[0].swap(cnt[1]);
		if (f[0].size() < 2) continue;
		if (f[1].size() < 1) continue;
		for (int i = 0; i < (int)f[1].size(); i++) {
			int le = upper_bound(f[0].begin(), f[0].end(), f[1][i]) - f[0].begin();
			int ge = f[0].end() - lower_bound(f[0].begin(), f[0].end(), f[1][i]);
			int eq = upper_bound(f[0].begin(), f[0].end(), f[1][i]) - lower_bound(f[0].begin(), f[0].end(), f[1][i]);
//			eprintf("f[i] = %d, %d %d %d\n",f[1][i], le, ge, eq);
			update(2*n, le * 1LL * ge - eq * 1LL* (eq + 1) / 2);
		}
		if (f[1].back() < f[0][0])
			update(2*n - (f[0][0] - f[1].back()), cnt[1][f[1].back()] * 1LL * (cnt[0][f[0][0]] *  1LL * f[0].size() - cnt[0][f[0][0]] * 1LL * (cnt[0][f[0][0]] + 1) / 2));
		if (f[1][0] > f[0].back())
			update(2*n - (f[1][0] - f[0].back()), cnt[0][f[0].back()] * 1LL * (cnt[1][f[1][0]] *  1LL * f[1].size() - cnt[1][f[1][0]] * 1LL * (cnt[1][f[1][0]] + 1) / 2));
	}

	eprintf("%d\n", ans);
	printf(LLD"\n", aways);
    return 0;
}