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
#include <iomanip>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl

using namespace std;

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");

#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

void print(vector<vector<double>> &a) {
  cerr << a.size();
//  for (auto &q : a) {
//    for (auto x : q) {
//      cout << x << " ";
//    }
//    cout << "\n";
//  }
//  cout << "\n";
}

int main() {
#ifdef LOCAL
  freopen("p6.in", "r", stdin);
  freopen("p6.out", "w", stdout);
#endif

  int n, v;
  scanf("%d%d", &n, &v);

  vector<int> x(n);
  vector<int> y(n);
  vector<int> p(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d%d", &x[i], &y[i], &p[i]);
  }
  vector<vector<double>> a(n, vector<double>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      ll dx = x[i] - x[j];
      ll dy = y[i] - y[j];
      if (dx * dx + dy * dy <= (ll) v * v) {
        a[i][j] = sqrt(dx * dx + dy * dy);
      } else {
        a[i][j] = 1e100;
      }
    }
  }

  print(a);

  vector<vector<double>> d1(n, vector<double>(n, 1e100));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        d1[i][j] = min(d1[i][j], max(0.0, a[i][k] + a[k][j] - v) * p[k]);
      }
    }
  }

  print(d1);

  vector<vector<double>> d2(n, vector<double>(n, 1e100));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      d2[i][j] = a[i][j] * p[j];
    }
  }

  print(d2);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        d2[j][k] = min(d2[j][k], d2[j][i] + d2[i][k]);
      }
    }
  }

  print(d2);

  vector<vector<double>> d3(n, vector<double>(n, 1e100));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      d3[i][j] = p[i] * a[i][j];
      for (int k = 0; k < n; k++) {
        d3[i][j] = min(d3[i][j], v * p[i] + d2[i][k] + d1[k][j]);
      }
    }
  }

  print(d3);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        d3[j][k] = min(d3[j][k], d3[j][i] + d3[i][k]);
      }
    }
  }

  print(d3);

  double s = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      s += d3[i][j];
    }
  }
  s /= n * (n - 1);

  cout << setprecision(20);
  cout << s;

  return 0;
}
