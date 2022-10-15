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
#define sz(x) ((int)(x).size())


#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "1185"

typedef long long ll;
typedef long double ld;

int sgn(ll x) { return x < 0 ? -1 : x > 0; }
struct point {
  int x, y;
  point() : x(0), y(0) {}
  point(int x, int y) : x(x), y(y) {}
  point operator+(const point &p2) const { return point(x + p2.x, y + p2.y); }
  point operator-(const point &p2) const { return point(x - p2.x, y - p2.y); }
  int operator*(const point &p2) const { return sgn(ll(x) * p2.y - ll(y) * p2.x); }
  int operator^(const point &p2) const { return sgn(ll(x) * p2.x + ll(y) * p2.y); }
  bool operator==(const point &p2) const { return x == p2.x && y == p2.y; }
};

bool operator<(const point &a, const point &b) {
  if (a.y != b.y) return a.y < b.y;
  return a.x < b.x;
}


bool cmp(const point& a,const point& b){
	ll tmp=a.x*1LL*b.y - a.y*1LL*b.x;
	if (tmp!=0)
		return tmp > 0;
	return a.x*1LL*a.x + a.y*1LL*a.y < a.x*1LL*a.x + a.y*1LL*a.y;
}

bool cmpxy(const point& a,const point& b){
	if (a.y!=b.y)
		return a.y<b.y;
	return a.x<b.x;
}

bool good(const point& a,const point& b,const point& c){
	int x1=b.x-a.x;
	int y1=b.y-a.y;
	int x2=c.x-a.x;
	int y2=c.y-a.y;
	return x1*1LL*y2-x2*1LL*y1 > 0;
}

void normalize(vector<point> &gon) {
  gon.erase(unique(gon.begin(), gon.end()),
            gon.end());
  while (sz(gon) > 1 && gon[0] == gon.back())
    gon.pop_back();
  rotate(gon.begin(),
         min_element(gon.begin(), gon.end()),
         gon.end());
  
  int ptr = 1;
  for (int i = 1; i < sz(gon); i++) {
    int pr = ptr - 1;
    int ne = (i + 1 == sz(gon) ? 0 : i + 1);
    
    point a = gon[pr], b = gon[i], c = gon[ne];
    if (((b - a) * (c - b)) != 0 || 
        ((b - a) ^ (c - b)) < 0) {
      gon[ptr++] = gon[i];
      continue;
    }
  }
  gon.resize(ptr);
}




void convex(vector<point>& a){
	int n=a.size();
	sort(a.begin(),a.end(),cmpxy);
	a.erase(unique(a.begin(),a.end()),a.end());
	n=a.size();
	for (int i=n-1;i>=0;--i){
		a[i].x-=a[0].x;
		a[i].y-=a[0].y;
	}	
	sort(a.begin()+1,a.end(),cmp);	
	vector<point> v;
	v.pb(a[0]);
	v.pb(a[1]);
	for (int i=2;i<n;i++){
		for (;v.size()>2 && !good(v[v.size()-2],v[v.size()-1],a[i]);v.pop_back());
		v.pb(a[i]);
	}
	a=v;
	return;
}


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif


    int n,Len;
    scanf("%d %d",&n,&Len);
    vector<point> v(n);

    for (int i = 0; i < n; i++)
    	scanf("%d %d",&v[i].x,&v[i].y);

    normalize(v);
    convex(v);

    v.pb(v[0]);

    double len = 2*M_PI * Len;
    for (int i = 1; i < (int)v.size(); i++)
    	len += sqrt((v[i].x - v[i-1].x) * (v[i].x - v[i-1].x) + (v[i].y - v[i-1].y) * (v[i].y - v[i-1].y));

    printf("%d\n",(int)round(len));
      
    TIMESTAMP(end);
    return 0;
}