#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <list>
#include <set>
#include <map>
//#include <iostream>

#define pb push_back
#define mp make_pair
#define TASKNAME "cutting"

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("[" #x "] Time = %.3lfs\n",clock()*1.0/CLOCKS_PER_SEC)

#ifdef _WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

#define sz(x) ((int)(x).size())

using namespace std;

typedef long double ld;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;
typedef pair <ll, ll> pll;
typedef vector<pii> vpii;

const int inf = 1e9;
const double eps = 1e-9;
const int INF = inf;
const double EPS = eps;

#ifdef LOCAL
struct __timestamper {
	~__timestamper(){
		TIMESTAMP(end);
	}
} __Timestamper;
#else
struct __timestamper {};
#endif

/*Template end*/

enum Sides { FRONT, REAR, BOTTOM, TOP, LEFT, RIGHT };
struct Cube {
  int x, y, z;
  int id;
  char cols[7];
  char sides[7];
  
  Cube() {
    x = y = z = 0;
    memset(cols, 0, sizeof cols);
    memset(sides, 0, sizeof sides);
  }
  
  void doit(const int *cyc) {
    for (int i = 0; i < 3; i++) {
      swap(cols[cyc[i]], cols[cyc[i + 1]]);
      swap(sides[cyc[i]], sides[cyc[i + 1]]);
    }
  }
    
  void rot(int ty) {
    if (ty == 0) {
      swap(x, z);
      const int cyc[] = { RIGHT, TOP, LEFT, BOTTOM };
      doit(cyc);
    } else {
      assert(ty == 1);
      swap(y, z);
      const int cyc[] = { TOP, REAR, BOTTOM, FRONT };
      doit(cyc);
    }
  }
  
  bool read() {
    if (scanf("%d%d%d%s", &y, &z, &x, cols) != 4) return false;
    strcpy(sides, "FBDULR");
    return true;
  }
  
  char& operator[](int v) { return cols[v]; }
  bool operator<(const Cube &c2) {
    #define cmp(a) if (a != c2.a) return a < c2.a;
    cmp(x)
    cmp(y)
    cmp(z)
    for (int i = 0; i < 6; i++) cmp(cols[i])
    return false;
    #undef cmp
  }
  bool operator==(const Cube &c2) {
    #define cmp(a) if (a != c2.a) return false;
    cmp(x)
    cmp(y)
    cmp(z)
    return strcmp(cols, c2.cols) == 0;
    #undef cmp
  }
  bool hascol(char c) {
    return !!strchr(cols, c);
  }
};

const int MAXN = 1010;
char out[MAXN][200];

int main()
{
  #ifdef LOCAL
  freopen(TASKNAME".in","r",stdin);
  freopen(TASKNAME".out","w",stdout);
  #endif

  Cube base;
  while (base.read()) {
    int n;
    scanf("%d", &n);
    vector<Cube> all(n);
    for (int i = 0; i < n; i++) {
      assert(all[i].read());
      all[i].id = i;
    }
    
    vi lenx, leny, lenz;
    int firx = -1, firy = -1, firz = -1;
    int lasx = -1, lasy = -1, lasz = -1;
    
    for (Cube cu : all) {
      bool okx = false;
      bool oky = false;
      bool okz = false;
      for (int r1 = 0; r1 < 4; r1++, cu.rot(0))
      for (int r2 = 0; r2 < 4; r2++, cu.rot(1))
      for (int r3 = 0; r3 < 4; r3++, cu.rot(0)) {
        #define doit(a, b, c, d, ty) \
          if (!ok##ty && cu[a] == base[a] && cu[b] == base[b]) { \
            ok##ty = true; \
            len##ty.pb(cu.ty); \
            if (cu[c] == base[c]) fir##ty = sz(len##ty) - 1; \
            if (cu[d] == base[d]) las##ty = sz(len##ty) - 1; \
          }
        doit(FRONT, BOTTOM, LEFT, RIGHT, x)
        doit(LEFT, BOTTOM, FRONT, REAR, y)
        doit(FRONT, LEFT, BOTTOM, TOP, z)
        #undef doit
      }
    }
    #define doit(ty) \
      assert(fir##ty >= 0 && las##ty >= 0); \
      { \
        int len1 = len##ty[fir##ty], len2 = len##ty[las##ty]; \
        int ptr = 0; \
        for (int i = 0; i < sz(len##ty); i++) \
          if (i != fir##ty && i != las##ty) len##ty[ptr++] = len##ty[i]; \
        len##ty.resize(ptr); \
        len##ty.insert(len##ty.begin(), len1); \
        if (fir##ty != las##ty) { \
          len##ty.pb(len2); \
        } else { \
          assert(sz(len##ty) == 1); \
        } \
      }
    doit(x)
    doit(y)
    doit(z)
    #undef doit

    for (int x = 0, cx = 0; x < sz(lenx); cx += lenx[x++])
    for (int y = 0, cy = 0; y < sz(leny); cy += leny[y++])
    for (int z = 0, cz = 0; z < sz(lenz); cz += lenz[z++]) {
      Cube wanted;
      wanted.x = lenx[x];
      wanted.y = leny[y];
      wanted.z = lenz[z];
      strcpy(wanted.cols, base.cols);
      if (x > 0) wanted[LEFT] = '.';
      if (x + 1 < sz(lenx)) wanted[RIGHT] = '.';
      if (y > 0) wanted[FRONT] = '.';
      if (y + 1 < sz(leny)) wanted[REAR] = '.';
      if (z > 0) wanted[BOTTOM] = '.';
      if (z + 1 < sz(lenz)) wanted[TOP] = '.';
      
      bool ok = false;
      for (int i = 0; i < sz(all); i++) {
        Cube cu = all[i];
        for (int r1 = 0; r1 < 4; r1++, cu.rot(0))
        for (int r2 = 0; r2 < 4; r2++, cu.rot(1))
        for (int r3 = 0; r3 < 4; r3++, cu.rot(0)) {
          if (cu == wanted) {
            ok = true;
            snprintf(out[cu.id], sizeof out[cu.id], "%c %c %d %d %d", cu.sides[FRONT], cu.sides[BOTTOM], cy, cz, cx);
            all.erase(all.begin() + i);
            goto end;
          }
        }
      }
      end:;
      assert(ok);
    }
    for (int i = 0; i < n; i++)
      puts(out[i]);
  }

  return 0;
}
