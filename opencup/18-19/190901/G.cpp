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

const double eps = 1e-9;

double sqr(double x) {
  return x * x;
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
//  freopen("g.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  for (int test_id = 0; test_id < t; test_id++) {
    int n;
    scanf("%d", &n);
    vector<vector<double>> v(n + 1, vector<double>(4));
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j < 4; j++) {
        scanf("%lf", &v[i][j]);
      }
    }
    double ans = 0;

    for (int i = 0; i < n; i++) {
      double r1 = v[i][3];
      double r2 = v[n][3];
      double d2 = (v[i][0] - v[n][0]) * (v[i][0] - v[n][0]) +
                      (v[i][1] - v[n][1]) * (v[i][1] - v[n][1]) +
                      (v[i][2] - v[n][2]) * (v[i][2] - v[n][2]);
      double d = sqrt(d2);

      if (r1 + r2 < d + eps) {
        continue;
      }
      double r = r1;
      double R = r2;
      if (r > R) swap(r, R);
      if (d + r < R + eps) {
        ans += M_PI * r * r * r * 4 / 3;
        continue;
      }
//      double x = (d2 - r1 * r1 + r2 * r2) / (2 * d);
//      double x = (d * d - r * r + R * R) / (2 * d);
//      double d1 = x;
//      double d2 = d - x;
//      double h1 = R - d1;
//      double h2 = r - d2;

      double V = M_PI * sqr(R + r - d) * (sqr(d) + 2 * d * r - 3 * sqr(r) + 2 * d * R + 6 * r * R - 3 * sqr(R)) / (12 * d);
      ans += V;
    }
    printf("Case #%d: %.17f\n", test_id + 1, ans);

  }

  return 0;
}
