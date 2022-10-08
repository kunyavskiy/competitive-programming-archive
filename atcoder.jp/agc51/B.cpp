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

  int n = 1000;
  int M = 100000;
  vector<int> x(n);
  vector<int> y(n);
  for (int i = 0; i < n; i++) {
    x[i] = rand() % M;
    y[i] = rand() % M;
  }

  map<int, set<int>> m;
  for (int i : x) {
    for (int j : y) {
      m[i - j].insert(i + j);
    }
  }
  vector<pair<int, int>> v(m.size());
  for (auto &[a, b] : m) {
    v.emplace_back(b.size(), a);
  }
  sort(v.rbegin(), v.rend());

  vector<pair<int, int>> res;
  set<int> as, bs, cs, ds;
  for (auto [_,x] : v) {
    for (int s : m[x]) {
      if (ds.size() && ds.size() >= 10 * max({as.size(), bs.size(), cs.size()})) {
        eprintf("%zd %zd %zd %zd\n", as.size(), bs.size(), cs.size(), ds.size());
        printf("%d\n", (int) res.size());
        for (auto [a, b] : res) {
          printf("%d %d\n", a, b);
        }
        return 0;
      }
      assert(res.size() < 100'000);
      int xx = (x + s) / 2;
      int yy = (s - x) / 2;
      assert(x == xx - yy);
      assert(s == xx + yy);
      as.insert(xx);
      bs.insert(yy);
      cs.insert(xx - yy);
      ds.insert(xx + yy);
      res.emplace_back(xx, yy);
    }
  }



  return 0;
}
