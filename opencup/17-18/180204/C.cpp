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

struct Path {
  double p, b, g;

};

double f(const Path & p1, const Path & p2) {
  return p1.b + p1.p * p1.g + (1 - p1.p) * (p2.p * p2.g + p2.b);
}

bool operator < (const Path & p1, const Path & p2) {
  double a1 = f(p1, p2);
  double a2 = f(p2, p1);
  eprintf("a1 %.10lf a2 %.10lf\n", a1, a2);
  return a1 < a2 - 1e-9;
}

double calc_res(const vector <Path> & ps) {
  int n = int(ps.size());
  double res = 0.0;
  for (int i = n - 1; i >= 0; --i) {
    const auto & path = ps[i];
    eprintf("p=%.4lf, b=%.4lf, g=%.4lf\n", path.p, path.b, path.g);
    res = path.p * path.g + path.b + (1 - path.p) * res;
    eprintf("res %.4lf\n", res);
  }
  return res;
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int tt = 0;
  int n;
  while (scanf("%d", &n) == 1) {
    eprintf("Test#%d\n", tt++);
    vector<Path> ps(n);
    for (Path &path : ps) {
      int k;
      scanf("%d", &k);
      vector<double> prob(k);
      for (double &x : prob) {
        scanf("%lf", &x);
        x /= 1000.0;
      }
      sort(prob.begin(), prob.end());
//      reverse(prob.begin(), prob.end());

      path.p = 1.0;
      path.g = k;
      path.b = 0;
      for (int i = 0; i < k; ++i) {
        path.b += path.p * (1 - prob[i]) * (i + 1);
        path.p *= prob[i];
      }
//      eprintf("p=%.4lf, b=%.4lf, g=%.4lf\n", path.p, path.b, path.g);
    }

//    eprintf("sort\n");
    sort(ps.begin(), ps.end());



    double res = calc_res(ps);
    printf("%.10lf\n", res);

#ifdef LOCAL
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        eprintf("i %d p=%.4lf, b=%.4lf, g=%.4lf\n", i, ps[i].p, ps[i].b, ps[i].g);
        eprintf("j %d p=%.4lf, b=%.4lf, g=%.4lf\n", j, ps[j].p, ps[j].b, ps[j].g);
        assert(!(ps[j] < ps[i]));
      }
    }
    if (n <= 10) {
      vector <int> perm(n);
      for (int i = 0; i < n; ++i) {
        perm[i] = i;
      }
      double res2 = 1e100;
      do {
        vector <Path> new_ps(n);
        for (int i = 0; i < n; ++i) {
          new_ps[i] = ps[perm[i]];
        }
        double cur = calc_res(new_ps);
        res2 = min(res2, cur);
      } while (next_permutation(perm.begin(), perm.end()));
      eprintf("res = %.10lf res2 %.10lf\n", res, res2);
      assert(fabs(res - res2) < 1e-9);
    }
#endif

    #ifdef LOCAL
    eprintf("=====\n");
    #endif
  }
  return 0;
}
