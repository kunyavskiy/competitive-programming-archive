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
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    vector<pair<int, int>> ans(n + 1, {-1, -1});

    vector<int> next(n);
    vector<int> dir(n);
    next[n - 1] = n;
    dir[n - 1] = 1;
    for (int i = n - 2; i >= 0; i--) {
      dir[i] = 1;
      if (a[i] > a[i + 1]) {
        dir[i] = -1;
      }
      if (dir[i] == dir[i + 1]) {
        next[i] = next[i + 1];
      } else {
        next[i] = i + 2;
      }
    }

    int q;
    scanf("%d", &q);
    for (int _ = 0; _ < q; _++) {
      int x;
      scanf("%d", &x);
      auto& res = ans[x];
      if (res.first == -1) {
        res.first = res.second = 0;
        for (int i = 0; i < n; ) {
          res.first++;
          int nxt = next[i];
          if (nxt - i < x) {
            int rnxt = min(n, i + x);
            res.second += rnxt - nxt;
            nxt = rnxt;
          }
          i = nxt;
        }
      }
      printf("%d %d\n", res.first, res.second);
    }
  }

  return 0;
}
