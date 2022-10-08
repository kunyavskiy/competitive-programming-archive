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

struct point{
  ll x, y;
  explicit point(ll x = 0, ll y = 0):x(x), y(y){}
};

point operator+(const point& a, const point& b) {
  return point(a.x + b.x, a.y + b.y);
}
point operator-(const point& a, const point& b) {
  return point(a.x - b.x, a.y - b.y);
}
point operator*(const point& a, long long b) {
  return point(a.x * b, a.y * b);
}
point operator-(const point& a){
  return point(-a.x, -a.y);
}

bool check(point p, point px, point py) {
  if (px.x == 0 && p.x != 0) return false;
  if (px.x != 0) {
    if (p.x % px.x != 0) return false;
    p = p - px * (p.x /px.x);
  }
  assert(py.x == 0);
  if (py.y == 0 && p.y != 0) return false;
  return p.y == 0 || p.y % py.y == 0;
}

void normx(point& a, point &b) {
  if (a.x < 0) a = -a;
  if (b.x < 0) b = -b;
  while (a.x && b.x) {
    if (a.x < b.x) swap(a, b);
    a = a - b * (a.x / b.x);
  }
}

void normy(point& a, point &b) {
  if (a.y < 0) a = -a;
  if (b.y < 0) b = -b;
  while (a.y && b.y) {
    if (a.y < b.y) swap(a, b);
    a = a - b * (a.y / b.y);
  }
}


void solve(){
  int n;
  scanf("%d",&n);
  vector<point> p(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld%lld",&p[i].x, &p[i].y);
  }
  point a, b;
  scanf("%lld%lld%lld%lld",&a.x, &a.y, &b.x, &b.y);
  if (((a.x - b.x) & 1) || ((a.y - b.y) & 1)) {
    printf("NO\n");
    return;
  }
  while (p.size() < 2)
    p.pb(point(0, 0));
  point a2 = p.back() * 2 - a;
  a = b - a;
  a2 = b - a2;
  assert(a.x % 2 == 0 && a.y % 2 == 0);
  assert(a2.x % 2 == 0 && a2.y % 2 == 0);
  a.x /= 2, a.y /= 2;
  a2.x /= 2, a2.y /= 2;
  if (a.x < 0) a = -a;
  if (a2.x < 0) a2 = -a2;
  for (int i = 0; i < (int)p.size(); i++)
    p[i] = p.back() - p[i];
  p.pop_back();
  for (int i = 0; i < (int)p.size(); i++)
    if (p[i].x < 0)
      p[i] = -p[i];
  for (int i = 1; i < (int)p.size(); i++) {
    normx(p[i], p[0]);
    if (p[i].x != 0)
      swap(p[i], p[0]);
    if (i != 1) {
      normy(p[i], p[1]);
      if (p[i].y != 0)
        swap(p[i], p[1]);
    }
  }
  if (p[0].x == 0) {
    normy(p[0], p[1]);
    if (p[0].y)
      swap(p[0], p[1]);
  }
  if (check(a, p[0], p[1]) || check(a2, p[0], p[1])) {
    printf("YES\n");
  } else {
    printf("NO\n");
  }
}

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  int t;
  scanf("%d",&t);
  while (t-->0)
    solve();
      
  return 0;
}
