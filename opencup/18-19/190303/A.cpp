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

struct point {
  double x, y;
};

point operator-(const point& a, const point&b) {
  return {a.x - b.x, a.y - b.y};
}

double operator*(const point& a, const point& b) {
  return a.x * b.y - a.y * b.x;
}

const int MAXN = 2510;

double f[MAXN];

double cnk2(int n, int k, int n1, int k1) {
  if (k > n || n < 0) return 0;
  return exp(f[n] - f[k] - f[n - k] - (f[n1] - f[k1] - f[n1 - k1]));
}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  f[0] = 0;
  for (int i = 1; i < MAXN; i++) {
    f[i] = f[i - 1] + log(i);
  }

  int n, k;
  while (scanf("%d%d", &n, &k) == 2) {
    vector<point> p(n);
    for (int i = 0; i < n; i++) {
      scanf("%lf%lf", &p[i].x, &p[i].y);
    }
    reverse(p.begin() + 1, p.end());

    double ans = 0;

    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        double a = p[i] * p[j] / 2;
//        eprintf("%lf %lf(%d, %d) %lf\n", a, cnk2(n - (j - i) - 1, k - 2, n, k), n - (j - 1) - 1, k - 2, cnk2(j - i - 1, k - 2, n, k));
        ans += a * cnk2(n - (j - i) - 1, k - 2, n, k);
        ans -= a * cnk2(j - i - 1, k - 2, n, k);
      }
    }

    printf("%lf\n", ans);
//    break;
  }

  return 0;
}
