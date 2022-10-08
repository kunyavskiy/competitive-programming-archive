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

#define TASKNAME "C"

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


struct Block {
    vector<int> cols;
    vector<int> scols;
    vector<ll> sums;
    vector<ll> vals;
    int first, last;
    ll add;
    ll tot;

    void recalc() {
    	assert(first == -1);
    	scols = cols;
    	sort(scols.begin(), scols.end());
    	for (int i = 0; i < (int)scols.size(); i++)
    		sums[i+1] = sums[i] + scols[i];
    	tot = 0;
    	for (int i = 0; i < (int)vals.size(); i++)
    		tot += vals[i];

    }

    void push(){
    	if (first == -1) return;
//    	eprintf("PUSH!\n");
    	for (int i = 0; i < (int)cols.size(); i++) {
    		vals[i] += abs(cols[i] - first) + add;
    		cols[i] = last;
    	}
    	first = last = -1;
    	add = 0;
    	recalc();
    }

    void colorAll(int x){
    	if (first == -1) {
    		first = last = x;
    		int id = lower_bound(scols.begin(), scols.end(), x) - scols.begin();
    		tot += (id * 1LL * x - sums[id]) + (sums.back() - sums[id] - (cols.size() - id) * 1LL * x);
    	} else { 
    		add += abs(x - last);
    		tot += cols.size() * abs(x - last);
    		last = x;
    	}
    }

    void setColor(int pos, int x){
    	assert(first == -1);
        if (cols[pos]) {
	    	eprintf("set %d to %d from %d [%d]\n", pos, x, cols[pos], cols.size());
        	vals[pos] += abs(cols[pos] - x);
        	tot += abs(cols[pos] - x);
        }
    	cols[pos] = x;
    }

    ll getVal(int pos) {
    	assert(first == -1);
    	eprintf("get %d is %I64d\n", pos, vals[pos]);
    	return vals[pos];
    }
    void init(int size) {
       cols = vector<int>(size);
       scols = vector<int>(size);
       sums = vector<ll>(size+1);
       vals = vector<ll>(size);
       first = last = -1;
       tot = 0;
       add = 0;    	
    }
};

const int BSZ = 400;
const int MAXN = 110000;

Block bs[MAXN / BSZ];


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; i += BSZ)
    	bs[i / BSZ].init(min(BSZ, n - i));

    for (int i = 0; i < n; i++)
    	bs[i / BSZ].setColor(i % BSZ, i + 1);
    for (int i = 0; i < n; i += BSZ)
    	bs[i / BSZ].recalc();

    int q;
    scanf("%d",&q);
    for (int i = 0; i < q; i++) {
    	int ty, l, r;
    	scanf("%d%d%d",&ty,&l,&r);
    	--l;
    	if (ty == 1) {
    		int x;
    		scanf("%d",&x);
    		int idl = l / BSZ;
    		int idr = (r - 1) / BSZ;
    		bs[idl].push();
    		bs[idr].push();
    		for (;l % BSZ && l < r;l++) bs[l / BSZ].setColor(l % BSZ, x);
    		for (;r % BSZ && l < r;r--) bs[r / BSZ].setColor(r % BSZ - 1, x);
    		bs[idl].recalc();
    		bs[idr].recalc();
    		for (;l < r; l += BSZ)
    			bs[l / BSZ].colorAll(x);
    	} else {
    		ll res = 0;
    		bs[l / BSZ].push();
    		bs[(r-1) / BSZ].push();
    		bs[l / BSZ].recalc();
    		bs[(r-1) / BSZ].recalc();
    		for (;l % BSZ && l < r;l++) res += bs[l / BSZ].getVal(l % BSZ);
    		for (;r % BSZ && l < r;r--) res += bs[r / BSZ].getVal(r % BSZ - 1);
    		for (;l < r; l += BSZ) 
    			res += bs[l / BSZ].tot;
    		printf(LLD"\n", res);
    	}


    }

      
    return 0;
}