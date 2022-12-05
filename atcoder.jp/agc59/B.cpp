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

  int t;
  scanf("%d", &t);
  while (t-->0) {
      int n;
      scanf("%d", &n);
      map<int, int> cnt;
      for (int i = 0; i < n; i++) {
          int x;
          scanf("%d", &x);
          cnt[x]++;
      }
      vector<pair<int, int>> v(cnt.begin(), cnt.end());
      sort(v.begin(), v.end(),[](auto x, auto y) { return x.second > y.second; });

      list<int> l;
      vector<list<int>::iterator> good;
      for (auto [x, c]: v) {
          auto it = l.end();
          if (!good.empty()) {
              it = good.back();
              good.pop_back();
          }
          for (int i = 0; i < c; i++) {
              auto nit = l.insert(it, x);
              if (i != 0 || (int)l.size() == 1) {
                  good.push_back(nit);
              }
          }
      }
      for (int x: l) {
          printf("%d ", x);
      }
      printf("\n");
  }

  return 0;
}
