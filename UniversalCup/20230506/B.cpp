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
#include <valarray>

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

struct expression {
  string s;
  valarray<double> values;
};

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  vector<vector<expression>> e(10);
  valarray<double> x(n);
  valarray<double> ans(n);
  valarray<double> ansm1(n);
  for (int i = 0; i < n; i++) {
    scanf("%lf%lf", &x[i], &ans[i]);
    ansm1[i] = max(abs(ans[i]), 1.0);
  }
  e[0].push_back({"x", x});
  for (int d1 = 0; d1 <= 9; d1++) {
    for (const auto& [s1, v1] : e[d1]) {
      if ((abs(v1 - ans) / ansm1).max() < 0.001) {
        printf("%s\n", s1.c_str());
        return 0;
      }
      if (d1 != 9) {
        e[d1 + 1].push_back({"cos(" + s1 + ")", cos(v1)});
        e[d1 + 1].push_back({"sin(" + s1 + ")", sin(v1)});
      }
      for (int d2 = 0; d2 <= d1; d2++) {
        if (d1 + d2 + 2 <= 9) {
          for (const auto &[s2, v2] : e[d2]) {
            if (d1 != d2 || s1 <= s2) {
              e[d1 + d2 + 2].push_back({"(" + s1 + ")+(" + s2 + ")", v1 + v2});
              e[d1 + d2 + 2].push_back({"(" + s1 + ")*(" + s2 + ")", v1 * v2});
            }
            e[d1 + d2 + 2].push_back({"(" + s1 + ")-(" + s2 + ")", v1 - v2});
            e[d1 + d2 + 2].push_back({"(" + s2 + ")-(" + s1 + ")", v2 - v1});
            if (abs(v2).min() >= 0.01) {
              e[d1 + d2 + 2].push_back({"(" + s1 + ")/(" + s2 + ")", v1 / v2});
            }
            if (abs(v1).min() >= 0.01) {
              e[d1 + d2 + 2].push_back({"(" + s2 + ")/(" + s1 + ")", v2 / v1});
            }
          }
        }
      }
    }
  }

  assert(false);

  return 0;
}
