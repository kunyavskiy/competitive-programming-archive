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
  freopen("d.in", "r", stdin);
  //freopen("d.out", "w", stdout);
#endif

  int n, m, k;
  while (scanf("%d%d%d", &n, &m, &k) == 3) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
      a[i]--;
    }
    vector<vector<int>> e(n);
    for (int i = 0; i < m; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      u--; v--;
      e[u].push_back(v);
      e[v].push_back(u);
    }

    int ok = 0;
    for (int it = 0; it < 2; it++) {
      vector<vector<int>> b(k);
      for (int i = 0; i < n; i++) {
        b[a[i]].push_back(i);
      }

      vector<int> last(k, 0);
      int tmr = 1;

      for (int c = 1; c < k; c++) {
        for (int v : b[c]) {
          tmr++;
          for (int to : e[v]) {
            last[a[to]] = tmr;
          }
          for (int i = 0; i < c; i++) {
            if (last[i] != tmr) {
              ok = 1;
              if (ok) break;
            }
          }
          if (ok) break;
        }
        if (ok) break;
      }
      if (ok) break;

      for (int &c : a) {
        c = k - 1 - c;
      }
    }
    cout << ok << endl;
  }

  return 0;
}
