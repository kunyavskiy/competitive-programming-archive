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
typedef double dbl;

const dbl PHI = (sqrt(5.0) - 1) / 2;

dbl tern(dbl L, dbl R, function<dbl(dbl)> f) {
  dbl fL = f(R - (R - L) * PHI);
  dbl fR = f(L + (R - L) * PHI);
  for (int it = 0; it < 60; it++ ){
    if (fL > fR) {
      fR = fL;
      R = L + (R - L) * PHI;
      fL = f(R - (R - L) * PHI);
    } else {
      fL = fR;
      L = R - (R - L) * PHI;
      fR = f(L + (R - L) * PHI);
    }
  }
  return min(fL, fR);
}

dbl solve(vector<int> a, vector<int> b, vector<int> c) {
  int n = a.size();
  return tern(0, 1, [&](dbl pa) {
    return tern(0, 1 - pa, [&](dbl pb) {
      dbl pc = 1 - pa - pb;
      dbl sum = 0;
      for (int i = 0; i < n; i++) {
        sum += min({a[i] * pa, b[i] * pb, c[i] * pc});
      }
      return sum;
    });
  });
}

void test() {
  int n = 5e4;
  vector<int> a(n), b(n), c(n);
  for (int i = 0; i < n; i++) {
    a[i] = rand() % 100 + 1;
    b[i] = rand() % 100 + 1;
    c[i] = rand() % 100 + 1;
  }
  printf("%.17f\n", solve(a, b, c));
  exit(0);
}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
//  freopen("a.out", "w", stdout);
#endif
//  test();

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> a(n), b(n), c(n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int i = 0; i < n; i++) scanf("%d", &b[i]);
    for (int i = 0; i < n; i++) scanf("%d", &c[i]);

    printf("%.17f\n", solve(a, b, c));
  }

  return 0;
}
