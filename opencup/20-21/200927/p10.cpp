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

int main() {
#ifdef LOCAL
  freopen("p10.in", "r", stdin);
  freopen("p10.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &x[i]);
    }
    for (int i = 0; i < n; i++) {
      scanf("%d", &y[i]);
    }
//    sort(x.begin(), x.end());
//    sort(y.begin(), y.end());

    double best = 1e100;
    double bestk = 0;
    double bestb = 0;

    auto try_solve = [&](int a1, int b1, int a2, int b2) {
      // k * a1 + b = b1
      // k * a2 + b = b2
      // k * (a1 - a2) = b1 - b2
      double k = (b1 - b2) * 1.0 / (a1 - a2);
      double b = b1 - k * a1;
      double ans = 0;
      for (int i = 0; i < n; i++) {
        ans += abs(x[i] - (k * y[i] + b));
      }
      if (ans < best) {
        best = ans;
        bestk = k;
        bestb = b;
      }
    };

//    for (int it = 0; it < 2; it++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if (i != j) {
            try_solve(y[i], x[i], y[j], x[j]);
          }
        }
      }
//      for (int i = 0; i < n; i++) {
//        y[i] = -y[i];
//      }
//      reverse(y.begin(), y.end());
//      bestk = -bestk;
//      bestb = -bestb;
//    }
    printf("%.18lf %.18lf %.18lf\n", best, bestk, bestb);
  }

  return 0;
}
