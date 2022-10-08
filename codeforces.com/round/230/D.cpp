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

struct three {
	int a, b, c;
	three():a(-1),b(-1),c(-1){}
	bool operator<(const three& r) const{
		return a > r.a;
	}
};


vector<three> read(){
	map<int, three> v;
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int x;
		scanf("%d", &x);
	    if (v[x].a == -1) v[x].a = i + 1;	
	}
	for (int i = 0; i < n; i++) {
		int x;
		scanf("%d", &x);
	    if (v[x].b == -1) v[x].b = i + 1;	
	}
	for (int i = 0; i < n; i++) {
		int x;
		scanf("%d", &x);
	    if (v[x].c == -1) v[x].c = i + 1;	
	}

	vector<three> res;
	res.reserve(v.size());
	for (map<int, three>::iterator iter = v.begin(); iter != v.end(); ++iter)
		res.pb(iter->second);
	for (int i = 0; i < (int)res.size(); i++){
		if (res[i].a == -1) res[i].a = 1e8 + i;
		if (res[i].b == -1) res[i].b = 1e8 + i;
		if (res[i].c == -1) res[i].c = 1e8 + i;
	}
	return res;
}

typedef map<int,int>::iterator myiter;


struct Solver {

	map<int, int> v;
	multiset<int> s;

	Solver(){
		v[0] = 1e9;		
		v[1e9] = 0;
		s.insert(0);
	}

	void erase_one(int x){
		multiset<int>::iterator iter = s.find(x);
		assert(iter != s.end());
		s.erase(iter);
	}


	void insert(int a, int b){
//		eprintf("insert %d %d\n", a, b);
		myiter iter_next = v.lower_bound(a);
		assert(iter_next != v.begin());
		assert(iter_next != v.end());
		assert(a < iter_next->first);
		myiter iter_prev = iter_next;--iter_prev;
		myiter iter = v.insert(mp(a, b)).first;
		s.insert(iter_prev->first + iter->second);
		s.insert(iter->first + iter_next->second);
		erase_one(iter_prev->first + iter_next->second);
	}

	void erase(myiter iter){
//		eprintf("erase %d %d\n", iter->first, iter->second);
		assert(iter != v.begin());
		assert(iter != --v.end());

		myiter iter_prev = iter; --iter_prev;
		myiter iter_next = iter; ++iter_next;

		erase_one(iter_prev->first + iter->second);
		erase_one(iter->first + iter_next->second);
		v.erase(iter);
		s.insert(iter_prev->first + iter_next->second);			
	}


	void add(int a, int b) {
		myiter iter = v.lower_bound(a);
		if (iter->second >= b) return;
		myiter iter_old = iter;
		while (iter_old != v.begin()){
			iter = iter_old;
			--iter;
			if (iter->second <= b) 
				erase(iter);
			else 
				break;
		}
		insert(a, b);
	}
	int get(){
		assert(!s.empty());
		return *s.begin();
	}
};






int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

    vector<three> v = read();
    sort(v.begin(), v.end());

    int ans = 1e9;

    Solver s;

    for (int i = 0; i < (int)v.size(); i++){
    	ans = min(ans, v[i].a + s.get());
    	s.add(v[i].b, v[i].c);
    }

    ans = min(ans, s.get());
    printf("%d\n", ans);      
    return 0;
}