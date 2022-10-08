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

struct Item {
	ll sum2;
	int cnt;
	ll sum1;
	ll best0;
	int bpos;
	Item(ll val = 0, int pos = -1) {
		sum2 = val;
		cnt = 1;
		sum1 = best0 = 0;
		bpos = pos;
	}
	Item(ll sum2, int cnt, ll sum1, ll best0, ll bpos):sum2(sum2), cnt(cnt), sum1(sum1), best0(best0), bpos(bpos){}
	void eprint() {
		eprintf("sum2 = %I64d, cnt = %d, sum1 = %I64d, best0 = %I64d, bpos = %d\n", sum2, cnt, sum1, best0, bpos);
	}
};

Item operator+(const Item& a, const Item& b){
	return Item(
		a.sum2 + b.sum2,
		a.cnt + b.cnt,
		a.sum1 + b.sum1 + b.cnt * a.sum2,
		max(a.best0, b.best0 + a.sum1),
		a.best0 > b.best0 + a.sum1 ? a.bpos : b.bpos
	);
}

const int lst = 1<<3;
Item tree[2*lst+10];
int cur[lst];


void setval(int pos, int val){
	pos += lst;
	tree[pos] = Item(val, pos - lst);
	while (pos /= 2) {
		tree[pos] = tree[2*pos] + tree[2*pos+1];
	}
}

ll getSlow(){
	ll cur0 = 0, cur1 = 0;
	ll curbest = 0;
	for (int i = 0; i < lst; i++){
		cur0 += cur1;
		eprintf(LLD"%c", cur0, " \n"[i == lst-1]);
		cur1 += cur[i];
		curbest = max(curbest, cur0);
	}
	return curbest;
}

void addval(int pos, int val){
	cur[pos] += val;
	setval(pos, cur[pos]);
}

void adda(int a) {
	eprintf("Adda %d\n", a);
	if (!a) return;
	addval(0, 1);
	addval(a, -1-a);
	addval(a+1, a);
	tree[1].eprint();
	tree[2].eprint();
	tree[4].eprint();
	tree[5].eprint();

}

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

    for (int i = 0; i < lst; i++)
    	setval(i, 0);
  	int n, w;
  	scanf("%d%d",&n,&w);
  	vector<pair<int, int> > v(n);
  	for (int i = 0; i < n; i++)      
  		scanf("%d%d",&v[i].second, &v[i].first);


  	Item res = Item(1, 0);res.eprint();
    res = res + Item(0, 1);res.eprint();
    res = res + Item(-3, 2);res.eprint();
    res = res + Item(2, 3);res.eprint();
    eprintf("\n");

  	sort(v.begin(), v.end());

  	int ptr = 0;
  	for (int i = 0; i <= v.back().first + 1; i++) {
  		while (ptr < (int)v.size() && v[ptr].first == i-1)
  			adda(v[ptr].second), ptr++;
  		printf(LLD" %d\n", tree[1].best0 /*+ w * 1LL * (v.size()-ptr) * 1LL * i*/, tree[1].bpos-1);
  	}
  		
    
    return 0;
}