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

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  auto read = [] () -> pair<int, int> {
    char s[100];
    scanf("%s", s);
    int p2, p5;
    p2 = p5 = 0;
    long long x = 0;
    bool have_dot = false;
    for (int i = 0; s[i]; i++) {
      if (s[i] == '.') {
        have_dot = true;
      } else {
        x = 10 * x + s[i] - '0';
        if (have_dot) {
          p2--, p5--;
        }
      }
    }

    while (x % 2 == 0) {
      p2++;
      x /= 2;
    }
    while (x % 5 == 0) {
      p5++;
      x /= 5;
    }

    return {p2, p5};
  };

  int n;
  while (scanf("%d", &n) == 1) {
    map<pair<int, int>, int> cnt;
    for (int i = 0; i < n; i++) {
      cnt[read()]++;
    }

    ll ans = 0;

    for (auto [a, c1] : cnt) {
      for (auto [b, c2] : cnt) {
        if (a.first + b.first >= 0 && a.second + b.second >= 0) {
          if (a == b) {
            ans += c1 * 1LL * (c1 - 1);
          } else {
            ans += c1 * 1LL * c2;
          }
        }
      }
    }
    ans /= 2;
    printf("%lld\n", ans);
  }

  return 0;
}
