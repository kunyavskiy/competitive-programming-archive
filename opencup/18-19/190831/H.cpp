#include <iostream>
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
#include <random>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


using namespace std;

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
typedef double dbl;

const dbl EPS = 1e-9;
bool eq(dbl a, dbl b) {
  return fabs(a - b) < EPS;
}

bool ls(dbl a, dbl b) {
  return a < b && !eq(a, b);
}

//#undef assert
//#define assert(x) void(x)

struct pt {
  dbl x, y, z;

  pt() {}
  pt(dbl _x, dbl _y, dbl _z) : x(_x), y(_y), z(_z) {}

  pt operator+ (const pt &p) const {
    return pt(x + p.x, y + p.y, z + p.z);
  }

  pt operator- (const pt &p) const {
    return pt(x - p.x, y - p.y, z - p.z);
  }

  pt operator* (dbl d) const {
    return pt(x * d, y * d, z * d);
  }

  dbl operator% (const pt &p) const {
    return x * p.x + y * p.y + z * p.z;
  }

  dbl d2() const {
    return (*this) % (*this);
  }

  dbl d() const {
    return sqrt(d2());
  }

  pt norm() const {
    return (*this) * (1.0 / d());
  }

  pt operator* (const pt &p) const {
    return pt(
      y * p.z - z * p.y,
      -x * p.z + z * p.x,
      x * p.y - y * p.x
      );
  }

  bool read() {
    return !!(cin >> x >> y >> z);
  }

  bool operator== (const pt &p) const {
    return eq(x, p.x) && eq(y, p.y) && eq(z, p.z);
  }
};

const int SEG = 1;
const int CIR = 2;
struct event {
  int type;
  pt F;
  pt O;

  void print() {
    cout.precision(17);
    cout << fixed;

    cout << type;
    cout << " " << F.x << " " << F.y << " " << F.z;
    if (type == CIR) cout << " " << O.x << " " << O.y << " " << O.z;
    cout << endl;
  }
};

vector<event> solve(pt p1, pt v1, pt p2, pt v2, dbl rad) {
  pt cp = p1, cv = v1;
  (void)cv;


  v1 = v1.norm();
  v2 = v2.norm();

  vector<event> ans;
  if (!(v1 == v2)) {
    pt x = v2;
    pt v = v1;
    pt P = p1;

    pt n = (v * x);
    if (eq(n.d(), 0)) {
      n = pt(2213245, 3452345, 1634532).norm();
    } else {
      n = n.norm();
    }
    pt y = (n * x).norm();
    pt O = P + (n * v).norm() * rad;
    pt F = O - y * rad; // TODO: -y*rad?
    ans.push_back({CIR, F, O});

    p1 = F;
    v1 = x;
  }
  assert(v1 == v2);

  {
    pt d = p2 - p1;

    if (!eq((d * v1).d(), 0)) {
      pt x = v1;
      pt n = (d * x).norm();
      pt u = (n * x).norm();

      if (ls(u % d, 0)) {
        u = u * -1;
      }
      dbl need = u % d;

      double R = max(5 * rad, 5 * need);
      ans.push_back({CIR, p1 + u * 2 * R, p1 + u * R});
      p1 = p1 + u * 2 * R; v1 = v1 * -1;
      R -= need / 2;
      ans.push_back({CIR, p1 - u * 2 * R, p1 - u * R});
      p1 = p1 - u * 2 * R; v1 = v1 * -1;
    }
  }
//  pt diff = p1 - p2;
//  db2(diff.x, diff.y);
//  db2(v2.x, v2.y);
  assert(eq(((p1 - p2) * v2).d(), 0));

  if (!(p1 == p2)) {
    pt u(12934, 59678, 90912);
    u = u.norm();
    pt n = (v2 * u).norm();

    dbl need = (p2 - p1) % v2;
    ans.push_back({CIR, p1 + n * rad * 2, p1 + n * rad});
    p1 = p1 + n * rad * 2; v1 = v1 * -1;

    ans.push_back({SEG, p1 + v1 * 300, pt()});
    p1 = p1 + v1 * 300;

    ans.push_back({CIR, p1 - n * rad * 2, p1 - n * rad});
    p1 = p1 - n * rad * 2; v1 = v1 * -1;

    ans.push_back({SEG, p1 + v1 * (300 + need), pt()});
    p1 = p1 + v1 * (300 + need);
  }
  assert(p1 == p2);

  for (auto ev : ans) {
    if (ev.type == CIR) {
      assert(eq((ev.O - cp).d(), (ev.O - ev.F).d()));
      cp = ev.F;
    }
    if (ev.type == SEG) {
      cp = ev.F;
    }
  }

  return ans;
}

void print(vector<event> ans) {
  cout << ans.size() << endl;
  for (auto ev : ans) ev.print();
}

void stress() {
  for (int it = 0;; it++) {
    db(it);
    mt19937 rnd(it);

    const int C = 1;
    auto randp = [&]() {
      pt p;
      int x = rnd() % (C + C + 1) - C;
      int y = rnd() % (C + C + 1) - C;
      int z = rnd() % (C + C + 1) - C;
      p.x = x; p.y = y; p.z = z;
      return p;
    };

    pt p1, v1, p2, v2;
    dbl r;
    p1 = randp();
    db3(p1.x, p1.y, p1.z);
    p2 = randp();
    r = rnd() % C + 1;
    while (eq(v1.d(), 0)) v1 = randp();
    while (eq(v2.d(), 0)) v2 = randp();

    solve(p1, v1, p2, v2, r);
  }
}

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
//  freopen("h.out", "w", stdout);
#endif
//  stress();

  pt p1, v1, p2, v2;
  dbl r;
  while (p1.read()) {
    v1.read();
    p2.read();
    v2.read();
    cin >> r;

    print(solve(p1, v1, p2, v2, r));
  }

  return 0;
}
