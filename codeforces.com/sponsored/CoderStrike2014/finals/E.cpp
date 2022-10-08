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

const ld eps = 1e-9;


bool cmp(const pair<ld, int>& a, const pair<ld, int>& b){
	if (fabs(a.first - b.first) < eps) return a.second > b.second;
	return a.first < b.first;
}


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  	int n, d;
  	scanf("%d %d",&n, &d);

  	vector<pair<ld, int> > evs;

  	int cur = 0;

  	for (int i = 0; i < n; i++){
  		int x, y, r;
  		scanf("%d %d %d",&x,&y,&r);

  		ld dst = sqrt(x*x + y*y);

  		int lk = (dst - r) * 1.0 / d - 5; 
  		int rk = (dst + r) * 1.0 / d + 5;

  		lk = max(lk, 1);

  		for (int r2 = d*lk; r2 <= d*rk; r2 += d) {
  			if (r + r2 < dst - eps) continue;
  			if (r + dst < r2 - eps) continue;
	  		ld ang = atan2(y, x);
	  		ld cosdang = (-r*r + (x*x + y*y) + r2*r2) / (2 * dst * r2);
	  		cosdang = max(-ld(1.0), cosdang);
	  		cosdang = min(ld(1.0), cosdang);
  			ld dang = acos(cosdang);
  			ld lang = ang - dang;
  			ld rang = ang + dang;
  			while (lang < 0) lang += 2*M_PI;
  			while (rang < 0) rang += 2*M_PI;
  			while (lang >= 2*M_PI) lang -= 2*M_PI;
  			while (rang >= 2*M_PI) rang -= 2*M_PI;

//  			eprintf("%d: %lf %lf\n", r2, (double)lang, (double)rang);

  			if (lang > rang)
  				cur++;
  			evs.pb(mp(lang, 1)), evs.pb(mp(rang, -1));
  	    }
  	}
  	int ans = cur;
  	sort(evs.begin(), evs.end(), cmp);

  	for (int i = 0; i < (int)evs.size(); i++)
  		cur += evs[i].second, ans = max(ans, cur);

  	printf("%d\n", ans);      
    return 0;
}