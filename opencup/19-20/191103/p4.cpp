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
typedef __int128_t i128;

int f(i128 a, i128 b, i128 c, i128 d, i128 x) {
  i128 val = 0;
  val += a;
  val *= x;
  val += b;
  val *= x;
  val += c;
  val *= x;
  val += d;
  if (val > 0) {
    return 1;
  } else if (val < 0) {
    return -1;
  } else {
    return 0;
  }
}

void add_root(i128 a, i128 b, i128 c, i128 d, i128 x, vector<int> &roots) {
  bool any = false;
  while ((a || b || c) && f(a, b, c, d, x) == 0) {
    any = true;
    roots.push_back((int)x);
    eprintf("add_root %d (%d %d %d %d)\n", (int)x, (int)a, (int)b, (int)c, (int)d);
    d = c;
    c = 2 * b;
    b = 3 * a;
    a = 0;
  }
  assert(any);
}

void solve(i128 a, i128 b, i128 c, i128 d, vector<int> &roots) {
  i128 A = 3 * a;
  i128 B = 2 * b;
  i128 C = c;
  i128 D = B * B - 4 * A * C;
  vector<i128> xs;
  xs.push_back(i128(-1e9));
  xs.push_back(i128(1e9));
  if (D > 0) {
    i128 sqrtD = sqrt(D + 0.0);
    i128 x1 = i128((-B - sqrtD) / (2 * A));
    i128 x2 = i128((-B + sqrtD) / (2 * A));
    for (int dt = -2; dt <= 2; ++dt) {
      xs.push_back(x1 + dt);
      xs.push_back(x2 + dt);
    }
  }
  sort(xs.begin(), xs.end());
  xs.erase(unique(xs.begin(), xs.end()), xs.end());
  for (int i = 0; i < int(xs.size()); ++i) {
    if (f(a, b, c, d, xs[i]) == 0) {
      add_root(a, b, c, d, xs[i], roots);
    }
    if (i > 0) {
      i128 L = xs[i - 1] + 1;
      i128 R = xs[i];
      if (L >= R) { continue; }
      int sgn = f(0, A, B, C, L);
      assert(sgn != 0);
      while (L + 1 < R) {
        i128 M = (L + R) / 2;
        if (sgn * f(a, b, c, d, M) <= 0) {
          L = M;
        } else {
          R = M;
        }
      }
      if (f(a, b, c, d, L) == 0) {
        add_root(a, b, c, d, L, roots);
      }
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("p4.in", "r", stdin);
  freopen("p4.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  vector<int> roots;
  for (int i = 0; i < n; i++) {
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    eprintf("%d %d %d %d\n", a, b, c, d);
    solve(a, b, c, d, roots);
  }

  sort(roots.begin(), roots.end());
  int bestCnt = 0, bestX = -1;
  int curCnt = 0;
  for (int i = 0; i < int(roots.size()); ++i) {
    if (i == 0 || roots[i] != roots[i - 1]) {
      curCnt = 0;
    }
    curCnt++;
    if (bestCnt < curCnt) {
      bestCnt = curCnt;
      bestX = roots[i];
    }
  }
  if (bestCnt == 0) {
    printf("NO\n");
  } else {
    printf("YES\n%d %d\n", bestX, bestCnt);
  }

  return 0;
}
