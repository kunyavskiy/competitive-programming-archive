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
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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

double d[55][110 * 50];

int f[55], s[55];
double p[55];
int n, r;

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  scanf("%d%d", &n, &r);
  for (int i = 0; i < n; i++) {
    int _p;
    scanf("%d%d%d", &f[i], &s[i], &_p);
    p[i] = _p / 100.0;
    r -= f[i];
  }

  d[0][0] = 1e100;

  for (int it = 0; it <= 100; it++) {
    for (int i = n - 1; i >= 0; i--) {
      for (int j = 0; j <= r; j++) {
        if (i == 0 && j == 0) {
          if (s[0] - f[0] <= r) {
            d[0][0] = min(d[0][0], (d[1][0] + f[0]) * p[0] + (d[1][s[0] - f[0]] + s[0]) * (1.0 - p[0]));
          }
          double ss = 0;
          for (int k = 0; k < n; k++) {
            ss = ss + f[k] + (ss + s[k]) * (1.0 - p[k]) / p[k];
            d[0][0] = min(d[0][0], d[k+1][0] + ss);
          }

        } else {
          double val1 = (d[i + 1][j] + f[i]) * p[i];
          double val2 = d[0][0] + s[i];
          if (j + s[i] - f[i] <= r) {
            val2 = d[i + 1][j + s[i] - f[i]] + s[i];
          }
          val2 *= (1.0 - p[i]);
          d[i][j] = val1 + val2;
          if (d[i][j] > d[0][0]) {
            d[i][j] = d[0][0];
          }
        }
      }
    }
  }

  printf("%.18f\n", d[0][0]);


  return 0;
}
