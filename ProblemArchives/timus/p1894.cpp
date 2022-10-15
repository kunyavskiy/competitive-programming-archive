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

#define TASKNAME "1894"

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

#ifndef LOCAL
#undef assert
#define assert(x) if (!(x)) { int t = 1/0; printf("%d\n", t);}
#endif

struct point {
   ll x, y;
   ll operator*(const point& b) const{
   	   return x *1LL* b.y - y *1LL* b.x;
   }
   point(){x = y = 0;}
   point (ll x, ll y):x(x), y(y){};
   ld dist(){
   	 return sqrt(x * x + y * y);
   }
};

point operator-(const point& a, const point& b){
	return point(a.x - b.x, a.y - b.y);
}

point operator+(const point& a, const point& b){
	return point(a.x + b.x, a.y + b.y);
}

int hpl(const point& a){
	return a.y > 0 || (a.y == 0 && a.x > 0);
}

bool operator<(const point& a, const point& b){
	if (hpl(a) != hpl(b)) return hpl(a) > hpl(b);
	return a * b > 0;
}

bool operator==(const point& a, const point& b){
	return a.x == b.x && a.y == b.y;
}


bool cmpxy(const point& a, const point& b) {
	if (a.y != b.y) return a.y < b.y;
	return a.x < b.x;
}

vector<point> sum(vector<point> v1, vector<point> v2){
	rotate(v1.begin(), min_element(v1.begin(), v1.end(), cmpxy), v1.end());
	rotate(v2.begin(), min_element(v2.begin(), v2.end(), cmpxy), v2.end());
	point shift;
	for (int it = 0; it < 2; it++, v1.swap(v2)) {
		shift = shift + v1[0];
		v1.pb(v1[0]);
		for (int i = 0; i + 1 < (int)v1.size(); i++)
		   v1[i] = v1[i+1] - v1[i];
		v1.pop_back();
	}

	for (int i = 1; i < (int)v1.size(); i++)
		assert(!(v1[i] < v1[i-1]));
	for (int i = 1; i < (int)v2.size(); i++)
		assert(!(v2[i] < v2[i-1]));
//	eprintf("%d %d\n", shift.x, shift.y);
	vector<point> v(v1.size() + v2.size());
	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v.begin());
	v.insert(v.begin(), shift);

	for (int i = 1; i < (int)v.size(); i++)
		v[i] = v[i-1] + v[i];
	assert(v[0] == v.back());
	v.pop_back();
	return v;
}

vector<point> read(int n){
	vector<point> res(n);
	for (int i = 0; i < n; i++) {
		int x, y;
		scanf("%d %d",&x, &y);
		res[i] = point(x,y);
	}
	return res;
}


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

    int n, m;
    scanf("%d %d",&n,&m);
    vector<point> p1 = read(n);
    vector<point> p2 = read(m);

    for (int i = 0; i < (int)p2.size(); i++)
    	p2[i] = point() - p2[i];


	for (int i = 0; i < (int)p1.size(); i++)
		assert((p1[(i+1)%(int)p1.size()] - p1[i]) * (p1[(i+2)%(int)p1.size()] - p1[i]) >= 0);
	for (int i = 0; i < (int)p2.size(); i++)
		assert((p2[(i+1)%(int)p2.size()] - p2[i]) * (p2[(i+2)%(int)p2.size()] - p2[i]) >= 0);

    vector<point> res = sum(p1, p2);

    res.pb(res[0]);


    ld dist = 1e100;
    for (int i = 0; i + 1 < (int)res.size(); i++) {
       ll temp = (res[i] - res[i+1]) * res[i];
       assert(temp > 0);
       dist = min(dist, temp / (res[i] - res[i+1]).dist());
//       eprintf("%.18lf\n", (double)dist);
    }
    
    dist = dist - 60;
    if (dist < 0) printf("0\n");
    else printf("%.18f\n", (double)dist);
      
    return 0;
}