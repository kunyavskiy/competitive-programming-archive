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

#define TASKNAME "G"

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

struct Point {
  int x, y;
  int num;
  Point() : x(0), y(0), num(-1) {}
  Point(int x, int y, int num = -1) : x(x), y(y), num(num) {}

  void read(int num) {
    this->num = num;
    scanf("%d%d", &x, &y);
  }

  Point operator - (const Point & p) const {
    return Point(x - p.x, y - p.y);
  }

  int operator * (const Point & p) const {
    return x * p.y - y * p.x;
  }

  int operator % (const Point & p) const {
    return x * p.x + y * p.y;
  }

  int sqrAbs() const {
    return x * x + y * y;
  }

  void print() const {
    eprintf("%d %d\n", x, y);
  }

};

int sign(int x) {
  if (x > 0) { return 1; }
  if (x < 0) { return -1; }
  return 0;
}

bool intersectWithRay(const Point & p0, const Point & v0, const Point & p1, const Point & p2) {
  if (sign((p1 - p0) * v0) * sign((p2 - p0) * v0) == -1) {
    if (sign((p2 - p1) * (p0 - p1)) * sign((p2 - p1) * v0) == -1) {
      return true;
    }
  }
  return false;
}

struct PolarAngleComparator {
  Point p0, v0;
  PolarAngleComparator(const Point & p0, const Point & v0) : p0(p0), v0(v0) {
  }

  bool operator() (const Point & p1, const Point & p2) {
    //return p1 < p2;
//    eprintf("compare ");
//    p1.print();
//    p2.print();
    int vm1 = v0 * (p1 - p0);
    int vm2 = v0 * (p2 - p0);
//    eprintf("vm1 %d vm2 %d\n", vm1, vm2);
    if (sign(vm1) != sign(vm2)) {
      return vm1 > vm2;
    }
    int vm = (p1 - p0) * (p2 - p0);
//    eprintf("vm %d\n", vm);
    if (vm != 0) {
      return vm > 0;
    }
    return (p1 - p0).sqrAbs() > (p2 - p0).sqrAbs();
  }
};

void preprocess(vector<Point> & p, int offset, const Point & p0) {
  int i = offset;
  while (i < int(p.size()) && (p[i] - p0) * (p[offset] - p0) == 0 && (p[i] - p0) % (p[offset] - p0) > 0) {
    ++i;
  }
  reverse(p.begin() + offset, p.begin() + i);
}


int main() {
#ifdef LOCAL
    assert(freopen(TASKNAME".in", "r", stdin));
    assert(freopen(TASKNAME".out", "w", stdout));
#endif
  int n;
  scanf("%d", &n);
  Point p0, v0;
  p0.read(-1);
  v0.read(-1);
  vector <Point> p(n);
  for (int i = 0; i < n; ++i) {
    p[i].read(i);
  }

  int z = 0;
  for (int i = 1; i < n; ++i) {
    if (p[i].y < p[z].y || (p[i].y == p[z].y && p[i].x > p[z].x)) {
      z = i;
    }
  }
  swap(p[0], p[z]);

//  auto cmp = PolarAngleComparator(p[0], Point(1, 0));
//  cmp(p[10 - 1], p[2 - 1]);
//  return 0;

  sort(p.begin() + 1, p.end(), PolarAngleComparator(p[0], Point(1, 0)));
  preprocess(p, 1, p[0]);

  eprintf("p: ");
  for (int i = 0; i < int(p.size()); ++i) {
    eprintf("%d ", p[i].num + 1);
  }
  eprintf("\n");

  vector <Point> st;
  vector <Point> p2;
  st.push_back(p[0]);
  for (int i = 1; i < n; ++i) {
    while (st.size() >= 2 && (p[i] - st[st.size() - 2]) * (st.back() - st[st.size() - 2]) > 0) {
      p2.push_back(st.back());
      st.pop_back();
    }
    st.push_back(p[i]);
  }

  int k = int(st.size());
  st.push_back(st[0]);
  z = 0;
  for (int i = 0; i < k; ++i) {
    if (intersectWithRay(p0, v0, st[i], st[i + 1])) {
      z = i;
    }
  }
  st.pop_back();
  if (z != k - 1) {
    rotate(st.begin(), st.begin() + z + 1, st.end());
  }
//  st[0].print();
//  st.back().print();
  assert(intersectWithRay(p0, v0, st[0], st.back()));

  eprintf("convex: ");
  for (int i = 0; i < int(st.size()); ++i) {
    eprintf("%d ", st[i].num + 1);
  }
  eprintf("\n");


//  p2.push_back(st[0]);
//  p2.push_back(st.back());

  sort(p2.begin(), p2.end(), PolarAngleComparator(p0, v0));
  preprocess(p2, 0, p0);

  p2.insert(p2.begin(), st[0]);
  p2.push_back(st.back());


  for (int i = 1; i < int(p2.size()); ++i) {
    if (intersectWithRay(p0, v0, p2[i - 1], p2[i])) {
      eprintf("i %d\n", i);
      p2[i - 1].print();
      p2[i].print();
      printf("-1\n");
      return 0;
    }
  }

  assert(p2[0].num == st[0].num);
  assert(p2.back().num == st.back().num);
  for (int i = 0; i < int(p2.size()); ++i) {
    printf("%d ", p2[i].num + 1);
    eprintf("%d ", p2[i].num + 1);
  }
  eprintf("| ");
  for (int i = k - 2; i >= 1; --i) {
    printf("%d ", st[i].num + 1);
    eprintf("%d ", st[i].num + 1);
  }
  printf("%d\n", p2[0].num + 1);

  return 0;
}
