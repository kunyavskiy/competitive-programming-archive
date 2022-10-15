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

#define TASKNAME "QRECT"

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
typedef unsigned long long ull;

const int MAXN = 310000;

enum EvTy { OPENR, OPENQ, CLOSEQ, CLOSER };

struct Event {
	EvTy ty;
	int id;
	int x;
	bool operator<(const Event& r) const {
		if (x != r.x) return x < r.x;
		return ty < r.ty;
	}
};


void solve(Event* evs1, int size1, Event* evs2, int size2, ull* mask) {
	Event* evs2end = evs2 + size2;
	Event* evs1end = evs1 + size1;
	ull curopen = 0, curclose = -1;
	for (; evs1 != evs1end; evs1++) {
		for (;evs2 != evs2end && evs2->x < evs1->x;evs2++)
			if (evs2->ty == OPENR)
			 	curopen |= (1ull << evs2->id); 
			else
				curclose &= ~(1ull << evs2->id);
			
		if (evs1->ty == OPENQ) {
			mask[evs1->id] = curclose; 
		} else {
			for (;evs2 != evs2end && evs2->x == evs1->x;evs2++)
				if (evs2->ty == OPENR)
				 	curopen |= (1ull << evs2->id); 
				else
					curclose &= ~(1ull << evs2->id);
			mask[evs1->id] &= curopen; 
		}
	}
}

struct Rect {
	int x1, y1, x2, y2;
	Rect(){};
	Rect (int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
};

Rect qs[MAXN];
int qt[MAXN];
Rect rs[MAXN];
int it[MAXN], dt[MAXN];
int rid[MAXN];
int qn, rn;

ull ansx[MAXN];
ull ansy[MAXN];

int res[MAXN];



int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif
    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; i++) {
    	char c;
    	int x1, y1, x2, y2;
    	scanf(" %c", &c);
    	if (c == 'Q') {
    		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
    		if (x1 > x2) swap(x1, x2);
    		if (y1 > y2) swap(y1, y2);
    		qs[qn] = Rect(x1, y1, x2, y2);
    		qt[qn] = i;
    		qn++;
    	} else if (c == 'I') {
    		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
    		if (x1 > x2) swap(x1, x2);
    		if (y1 > y2) swap(y1, y2);
    		rs[rn] = Rect(x1, y1, x2, y2);
    		it[rn] = i;
    		dt[rn] = n;
    		rid[i] = rn;
    		rn++;
    	} else if (c == 'D') {
    		scanf("%d",&x1);
    		assert(dt[x1-1] == n);
    		dt[x1-1] = i;
    	}
    }

    vector<Event> xevs(2*qn), yevs(2*qn);
    for (int i = 0; i < qn; i++){
    	xevs[2*i].x = qs[i].x1;
    	xevs[2*i].id = i;
    	xevs[2*i].ty = OPENQ;

    	xevs[2*i+1].x = qs[i].x2;
    	xevs[2*i+1].id = i;
    	xevs[2*i+1].ty = CLOSEQ;

    	yevs[2*i].x = qs[i].y1;
    	yevs[2*i].id = i;
    	yevs[2*i].ty = OPENQ;

    	yevs[2*i+1].x = qs[i].y2;
    	yevs[2*i+1].id = i;
    	yevs[2*i+1].ty = CLOSEQ;
    }

    sort(xevs.begin(), xevs.end());
    sort(yevs.begin(), yevs.end());


    for (int i = 0; i < rn; i += 64) {
    	int last = min(i + 64, rn);
    	static Event nx[200];
    	static Event ny[200];
    	vector<pair<int, int> > ts;
    	for (int j = i; j < last; j++){
        	nx[2*(j-i)].x = rs[j].x1;
        	nx[2*(j-i)].id = j-i;
        	nx[2*(j-i)].ty = OPENR;

        	nx[2*(j-i)+1].x = rs[j].x2;
        	nx[2*(j-i)+1].id = j-i;
        	nx[2*(j-i)+1].ty = CLOSER;

        	ny[2*(j-i)].x = rs[j].y1;
        	ny[2*(j-i)].id = j-i;
        	ny[2*(j-i)].ty = OPENR;

        	ny[2*(j-i)+1].x = rs[j].y2;
        	ny[2*(j-i)+1].id = j-i;
        	ny[2*(j-i)+1].ty = CLOSER;

	      	ts.pb(mp(it[j], j-i+1));
        	ts.pb(mp(dt[j], -(j-i+1)));
    	}    		
    	sort(nx, nx+2*(last-i));
    	sort(ny, ny+2*(last-i));
    	solve(&xevs[0], xevs.size(), &nx[0], 2*(last-i), ansx);
    	solve(&yevs[0], yevs.size(), &ny[0], 2*(last-i), ansy);
    	sort(ts.begin(), ts.end());
    	ull opened, closed;
    	opened = closed = 0;
    	int ptr = 0;
    	for (int i = 0; i < qn; i++) {
    		while (ptr < (int)ts.size() && ts[ptr].first < qt[i]) {
    			if (ts[ptr].second > 0)
    				opened |= (1ull << (+ts[ptr].second - 1));
    			else
    				closed |= (1ull << (-ts[ptr].second - 1));
    			ptr++;
    		}
    		ull mask = ansx[i] & ansy[i] & opened & ~closed;
//    		eprintf("i = %d ansx=%I64u ansy=%I64u opened=%I64u closed=%I64u\n", i, ansx[i], ansy[i], opened, closed);
    		res[i] += __builtin_popcountll(mask);
    	}
    }

    for (int i = 0; i < qn; i++)
    	printf("%d\n", res[i]);
    return 0;
}