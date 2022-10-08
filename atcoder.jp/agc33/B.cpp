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

char s[210000];
char t[210000];

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int r, c, n;
  while (scanf("%d%d%d", &r, &c, &n) == 3) {
    int x, y;
    scanf("%d%d", &x, &y);
    scanf("%s%s", s, t);
    --x, --y;

    int xl = 0, xr = r;
    int yl = 0, yr = c;

    bool fail = false;

    auto norm = [&]() {
      xl = max(xl, 0);
      xr = min(xr, r);
      yl = max(yl, 0);
      yr = min(yr, c);
      fail |= xl >= xr;
      fail |= yl >= yr;
    };

    for (int i = n - 1; i >= 0; i--) {
      switch (t[i]) {
        case 'L': yr++; break;
        case 'R': yl--; break;
        case 'U': xr++; break;
        case 'D': xl--; break;
      }
      norm();
      switch (s[i]) {
        case 'L': yl++; break;
        case 'R': yr--; break;
        case 'U': xl++; break;
        case 'D': xr--; break;
      }
      norm();
    }

    fail |= !(xl <= x && x < xr && yl <= y && y < yr);

    printf("%s\n", fail ? "NO" : "YES");
  }

  return 0;
}
