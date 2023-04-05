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

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &v[i]);
    }
    vector<double> dp((1 << n));
    for (int mask = 1; mask < (1 << n); mask++) {
      vector<double> as, bs;
      double ans = 0;
      for (int j = 0; j < n; j++) {
        if (mask & (1 << j)) {
/*          if (dp[mask ^ (1 << j)] >= v[j]) {
            ans = max<double>(ans, v[j]);
            continue;
          }*/
          as.push_back(v[j]);
          bs.push_back(dp[mask ^ (1 << j)] - v[j]);
        }
      }
      while (!as.empty()) {
        double aa = 0, bb = 1;
        for (int i = 1; i < (int)as.size(); i++) {
          aa += (as[0] - as[i]) / bs[i];
          bb += bs[0] / bs[i];
        }
        double p0 = (1 - aa) / bb;
        int ptr = 0;
        for (int i = 0; i < (int)as.size(); i++) {
          double p = (as[0] - as[i] + bs[0] * p0) / bs[i];
          if (p >= 0) {
            as[ptr] = as[i];
            bs[ptr] = bs[i];
            ptr++;
          } else {
            ans = max(ans, as[i]);
          }
        }
        if (ptr == (int)as.size()) {
          ans = max(ans, as[0] + bs[0] * p0);
          break;
        }
        as.resize(ptr);
        bs.resize(ptr);
      }
      dp[mask] = ans;
    }
    printf("%.18lf\n", dp.back());
  }

  return 0;
}
