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

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif
  while(true) {
    int n;
    int m;
    if (scanf("%d%d", &n, &m) != 2) {
      return 0;
    }
    vector<bool> fixed(n);
    vector<int> fixVal(n);
    int fn = 0;
    for (int i = 0; i < n; i++) {
      int x;
      if (scanf("%d", &x) == 1) {
        fixed[i] = true;
        fixVal[i] = x;
        fn++;
      } else {
        char s[10];
        scanf("%s", s);
      }
    }
    int mm = m;
    vector<int> a(m + n + 2 * fn);
    vector<int> b(m + n + 2 * fn);
    vector<int> d(m + n + 2 * fn);
    for (int i = 0; i < m; i++) {
      scanf("%d%d%d", &a[i], &b[i], &d[i]);
    }
    for (int i = 0; i < n; i++) {
      a[m] = 0;
      b[m] = i + 1;
      d[m] = -100000000;
      m++;
    }
    for (int i = 0; i < n; i++) {
      if (fixed[i]) {
        a[m] = 0;
        b[m] = i + 1;
        d[m] = fixVal[i];
        m++;
        a[m] = i + 1;
        b[m] = 0;
        d[m] = -fixVal[i];
        m++;
      }
    }
    double l = 0;
    double r = 1e10;
    vector<double> ans;
    while (r > l + 1e-5) {
      double t = (l + r) / 2;
      vector<double> x(n + 1, -1e100);
      x[0] = 0;
      bool ok2 = true;
      for (int i = 0; i < n + 2; i++) {
        bool ok = true;
        for (int j = 0; j < m; j++) {
          int aa = a[j];
          int bb = b[j];
          double dd = d[j];
//          cout << aa << " " << bb << " " << dd << endl;
          if (j < mm) dd -= t;
          if (x[aa] + dd > x[bb]) {
            ok = false;
            x[bb] = x[aa] + dd;
          }
        }
//        cout << endl;
        if (ok) {
          ok2 = true;
          break;
        }
        if (i == n + 1) {
          ok2 = false;
          break;
        }
      }
      if (ok2) {
        r = t;
        ans = x;
      } else {
        l = t;
      }
    }
    cout << setprecision(20) << std::fixed;
    cout << l << endl;
    for (int i = 1; i <= n; i++) {
      cout << ans[i] << " ";
    }
    cout << endl;
  }
}
