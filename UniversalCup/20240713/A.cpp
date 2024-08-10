#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x)                                                           \
  eprintf("[" #x "] Time : %.3lf s.\n",                                        \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...)                                                     \
  eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__,                            \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() { TIMESTAMPf("%s", what.data()); }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;


int solve2(string s) {

  int ans = 10;

  {
    bool hasU = false;
    bool hasC = false;
    bool hasT = false;

    for (int i = 0; i < (int)s.size(); i++) {
      if (s[i] == 'U') {
        hasU = true;
      } else if (s[i] == 'C') {
        hasC = true;
      } else if (s[i] == 'T') {
        assert(i != 0);
        hasU = hasC = false;
        hasT = true;
      } else if (s[i] == 'P') {
        if (hasT) {
          int res = 0;
          if (hasC) {
            res += 2;
          } else {
            res += 1;
          }
          if (hasU) {
            res += 2;
          } else {
            res += s[i + 1] != 'C';
          }
          ans = min(ans, res);
          hasC = true;
        }
      } else {
        assert(false);
      }
    }
  }
  bool hasUT = false;
  bool hasU = false;
  for (int i = 0; i < (int)s.size(); i++) {
    if (s[i] == 'U') {
      hasU = true;
    } else if (s[i] == 'C') {
      hasUT = false;
    } else if (s[i] == 'T') {
      if (s[i - 1] == 'U') {
        hasUT = true;
        hasU = false;
      } else {
        hasU = true;
      }
    } else if (s[i] == 'P') {
      if (hasUT) {
        int res = 0;
        if (hasU) {
          res += 2;
        } else {
          res += s[i + 1] != 'C';
        }
        ans = min(ans, res);
        hasUT = false;
      }
    } else {
      assert(false);
    }
  }
  if (ans == 10) ans = -1;
  return ans;
}

int solve() {
  int n;
  static char s[2100000];
  scanf("%d%s", &n, s);

  int lptr = 0;
  while (lptr < n && s[lptr] != 'U') lptr++;
  int rptr = n - 1;
  while (rptr >= lptr && s[rptr] != 'C') rptr--;
  if (lptr >= rptr) {
    return - 1;
  }

  return solve2(string(s + lptr, s + rptr + 1));
}

int main() {
  #ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
  #endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    printf("%d\n", solve());
  }

  return 0;
}
