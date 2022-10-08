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


struct point {
  int x, y;
  int id;
};

bool operator<(const point& a, const point& b) {
  if (a.x != b.x) {
    return a.x < b.x;
  }
  return a.y < b.y;
}

const int MAXN = 210000;

int tree[MAXN];

int get(int v, int L, int R, int l, int r) {
  if (r < L || R < l) return 1.1e9;
  if (L <= l && r <= R)
    return tree[v];
  int a = get(2*v, L, R, l, (l + r) / 2);
  int b = get(2*v, L, R, (l + r) / 2 + 1, r);
  return max(a, b);
}

int upd(int v, int pos, int l, int r, int val) {
  if (r < pos || pos < l) return tree[v];
  if (l == pos && pos == r) {
    tree[v] = val;
    return tree[v];
  }
  int a = upd(2*v, pos, l, (l + r) / 2, val);
  int b = upd(2*v, pos, (l + r) / 2 + 1, r, val);
  return tree[v] = max(a, b);
}


int main() {
  #ifdef LOCAL
  assert(freopen (TASKNAME
           ".in", "r", stdin));
  assert(freopen (TASKNAME
           ".out", "w", stdout));
  #endif

  int n;
  scanf ("%d", &n);
  vector<point> v (n);
  vector<int> ys, xs;

  for (int i = 0; i < n; i++) {
    v[i].id = i + 1;
    scanf ("%d%d", &v[i].x, &v[i].y);
    ys.push_back (v[i].y);
    xs.push_back (v[i].x);
  }
  sort(ys.begin(), ys.end());
  ys.erase(unique(ys.begin(), ys.end()), ys.end());
  sort(xs.begin(), xs.end());
  xs.erase(unique(xs.begin(), xs.end()), xs.end());

  for (int i = 0; i < n; i++) {
    v[i].y = lower_bound (ys.begin (), ys.end (), v[i].y) - ys.begin () + 1;
    v[i].x = lower_bound (xs.begin (), xs.end (), v[i].x) - xs.begin () + 1;
  }


  int lst = 2;
  while (lst <= (int)ys.size()) lst *= 2;

  sort (v.begin (), v.end ());

  map<int, int> s;

  for (int i = 0; i < n; i++) {
    eprintf("%d %d\n", v[i].x, v[i].y);
    int xlimit = -1 << 30;
    if (s.find (v[i].y) != s.end ()) {
      xlimit = s[v[i].y];
    }

    int yl = 0;
    int yr = ys.size();
    if (i && v[i-1].x == v[i].x)
      yl = v[i-1].y + 1;
    if (i < n - 1 && v[i+1].x == v[i].x)
      yr = v[i+1].y - 1;

    if (get(0, yl, yr, 0, lst - 1) > xlimit) {
      printf("NO\n");
      return 0;
    }

    s[v[i].y] = v[i].x;
  }
  for (int i = 0; i < n; i++)
    swap (v[i].x, v[i].y);
  printf ("YES\n");


  return 0;
}
