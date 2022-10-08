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



const int MAXN = 51000;

int x[MAXN], y[MAXN];
int lx[MAXN], rx[MAXN], ly[MAXN], ry[MAXN];

int n,m;


struct event{
	int x, ly, ry;
	int ty;

	event(int x, int ly, int ry, int ty):x(x), ly(ly), ry(ry), ty(ty){}

	bool operator<(const event& e) const{
		if (x != e.x) return x < e.x;
		return ty > e.ty;
	}
};

bool check(int len){
	vector<event> evs;
	for (int i = 0; i < n; i++)
		if (lx[i] + len <= rx[i] - len){
			evs.pb(event(lx[i] + len, x[i], x[i], 1));
			evs.pb(event(rx[i] - len, x[i], x[i], -1));
		}

	for (int i = 0; i < m; i++)
		if (ly[i] + len <= ry[i] - len){
			evs.pb(event(y[i], ly[i]+len, ry[i] - len, 0));
		}

	sort(evs.begin(), evs.end());

	multiset<int> s;

	for (int i = 0; i < (int)evs.size(); i++) {
		if (evs[i].ty == 1) {
//			eprintf("insert %d at %d\n", evs[i].ly, evs[i].x);
			s.insert(evs[i].ly);
		}
		else if (evs[i].ty == -1) {
//			eprintf("erase %d at %d\n", evs[i].ly, evs[i].x);
		    s.erase(s.find(evs[i].ly));
		}else {                                              
			assert(evs[i].ty == 0);
//			eprintf("request %d %d at %d\n", evs[i].ly, evs[i].ry, evs[i].x);
			if (s.lower_bound(evs[i].ly) != s.upper_bound(evs[i].ry))
				return true;
		} 
	}
	return false;
}

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  	scanf("%d %d",&n,&m);
  	for (int i = 0; i < n; i++)
  		scanf("%d %d %d",&x[i], &lx[i], &rx[i]), rx[i] += lx[i];
  	for (int i = 0; i < m; i++)
  		scanf("%d %d %d",&ly[i], &y[i], &ry[i]), ry[i] += ly[i];

  	int L = 0;
  	int R = 500000000;

//  	check(2);
//  	return 0;

  	while (R - L > 1){
  		int M = (L + R) / 2;
  		if (check(M))
  			L = M;
  		else
  			R = M;
  	}

  	printf("%d\n",L);
      
    return 0;
}