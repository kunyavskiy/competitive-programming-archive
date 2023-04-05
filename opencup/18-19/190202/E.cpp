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

vector<double> rnd_perm(int n) {
  vector<double> v(n);
  for (int i = 0; i < n; i++) {
    v[i] = i - (n + 1) / 2.0;
  }
  random_shuffle(v.begin(), v.end());
  return v;
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    int total = 0;
    vector<double> v(n);
    for (int i = 0; i < n; i++) {
      int x;
      scanf("%d", &x);
      total += x;
      v[i] = x;
    }
    if (total != n * (n + 1) / 2) {
      printf("-1\n");
      continue;
    }
    for (double& x : v) {
      x -= (n + 1) / 2.0;
    }

    vector<vector<double>> a;
    vector<vector<int>> ra;
    vector<vector<double>> coef;

    for (int i = 0; i < n - 1; i++) {
      vector<double> r(n);
      vector<int> rr(n);
      for (int j = 0; j < n; j++) {
        rr[j] = j + 1;
      }
      random_shuffle(rr.begin(), rr.end());
      for (int j = 0; j < n; j++) {
        r[j] = rr[j] - (n + 1) / 2.0;
      }
      vector<double> c(n);
      c[i] = 1;
      for (int j = 0; j < i; j++) {
        double x = -r[j] / a[j][j];
        for (int k = 0; k < n; k++) {
          r[k] += x * a[j][k];
          c[k] += x * coef[j][k];
        }
      }
      if (abs(r[i]) < 1e-9) {
        i--;
        continue;
      }
      a.push_back(r);
      ra.push_back(rr);
      coef.push_back(c);
    }


    vector<double> cfs(n);
    for (int i = 0; i < n - 1; i++) {
      double x = v[i] / a[i][i];
      for (int j = 0; j < n; j++) {
        cfs[j] += coef[i][j] * x;
        v[j] -= a[i][j] * x;
      }
    }

    auto debug = [&]() {
      vector<double> check(n);

      for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n; j++) {
          check[j] += cfs[i] * (ra[i][j] - (n + 1) / 2.0);
        }
      }

      for (int i = 0; i < n; i++) {
        eprintf("%lf ", check[i]);
      }
      eprintf("\n");
    };

    debug();

    for (int i = n - 1; i >= 0; i--) {
      if (cfs[i] < 0) {
        for (int j = 0; j < i; j++) {
          cfs[j] -= cfs[i] * coef[i][j];
        }
        cfs[i] *= -1;
        for (int j = 0; j < n; j++) {
          a[i][j] = -a[i][j];
          ra[i][j] = n + 1 - ra[i][j];
          coef[i][j] *= -1;
        }
        for (int j = 0; j < i; j++) {
          cfs[j] += cfs[i] * coef[i][j];
        }
      }
      debug();
    }

    double norm = 0;
    for (int i = 0; i < n; i++) {
      norm += cfs[i];
    }

    for (int i = 0; i < n; i++) {
      cfs[i] /= norm;
    }
    debug();

    vector<double> check(n);


    printf("%d\n", n - 1);
    for (int i = 0; i < n - 1; i++) {
      printf("%.18lf", cfs[i]);
      for (int j = 0; j < n; j++) {
        printf(" %d", ra[i][j]);
        check[j] += cfs[i] * ra[i][j];
      }
      printf("\n");
    }

#ifdef LOCAL
    for (int i = 0; i < n; i++) {
      eprintf("%lf ", check[i]);
    }
    eprintf("\n");
#endif

  }

  return 0;
}
