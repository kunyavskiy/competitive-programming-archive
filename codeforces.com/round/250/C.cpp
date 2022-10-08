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



int sgn(ll a){
    return (a > 0) - (a < 0);
}

struct point {
  int x, y;
  point() : x(0), y(0) {}
  point(int x, int y) : x(x), y(y) {}
  point operator+(const point &p2) const { return point(x + p2.x, y + p2.y); }
  point operator-(const point &p2) const { return point(x - p2.x, y - p2.y); }
  point operator/(int b) const { return point(x / b, y / b); }
  int operator*(const point &p2) const { return ll(x) * p2.y - ll(y) * p2.x; }
  bool operator==(const point &p2) const { return x == p2.x && y == p2.y; }
  bool operator!=(const point &p2) const { return x != p2.x || y != p2.y; }
};

bool is_in(int l, int r, int x) {
  if (l > r) swap(l, r);
  return l <= x && x <= r;
}

bool contains(const point &a, const point &b, 
              const point &p) {
  if ((p - a) * (p - b) != 0) return false;
  return is_in(a.x, b.x, p.x) && 
         is_in(a.y, b.y, p.y);
}

int inside(const vector<point> &gon, const point &p) {
  int cnt = 0;
  for (int i = 0; i < (int)gon.size(); i++) {
    point a = gon[i];
    point b = gon[i + 1 >= (int)gon.size() ? 0 : i + 1];
    if (contains(a, b, p)) return 1;
    
    if (a.y > b.y) swap(a, b);
    if (a.y == b.y || p.y <= a.y || b.y < p.y) 
       continue;
    
    if (ll(b.x - a.x) * ll(p.y - a.y) -
        ll(b.y - a.y) * ll(p.x - a.x) >= 0)
      cnt++;
  }
  return (cnt & 1) ? 2 : 0;
}

bool cross(const point& a, const point& b, const point& c, const point& d){
    if (a != c && b != c && contains(a, b, c)) return true;
    if (a != d && b != d && contains(a, b, d)) return true;
    if (c != a && d != a && contains(c, d, a)) return true;
    if (c != b && d != b && contains(c, d, b)) return true;
    
    if (sgn((b - a) * (c - a)) * sgn((b - a) * (d - a)) >= 0) return false;
    if (sgn((d - c) * (a - c)) * sgn((d - c) * (b - c)) >= 0) return false;
    return true;
}



const int MAXN = 210;
bool good[MAXN][MAXN];
int dp[MAXN][MAXN];
const int MOD = 1000000007;

void madd(int& a, int b){
	if ((a += b) >= MOD) a -= MOD;
}

int calc(int l, int r){
	int& res = dp[l][r];
	if (dp[l][r] >= 0) return res;
	if (r - l == 1) return res = 1;
	res = 0;
	for (int i = l + 1; i < r; i++){
		if (good[l][i] && good[i][r])
			madd(res, (calc(l, i) * 1LL * calc(i, r)) % MOD);
	}
	return res;
}

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif


    int n;
    while (scanf("%d",&n) == 1){
        vector<point> gon(n);
        for (int i = 0; i < n; i++){
            scanf("%d %d",&gon[i].x, &gon[i].y);
            gon[i].x *= 2;
            gon[i].y *= 2;
        }

        for (int i = 0; i < n; i++)                                                                          
            for (int j = i+1; j < n; j++){
                bool res = true;

                for (int k = 0; k < n; k++)
                    if (cross(gon[i], gon[j], gon[k], gon[(k+1)%n])) {
                        res = false;
                    }
                if (inside(gon, (gon[i] + gon[j]) / 2) != 2) 
                    res = false;

                if (i+1 == j) res = true;
                good[i][j] = good[j][i] = res;
            }

        memset(dp, -1, sizeof(dp));

        printf("%d\n",calc(0, n-1));
    }
      
  return 0;
}