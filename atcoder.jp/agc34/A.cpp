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

char s[300000];

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    --a, --b, --c, --d;
    scanf("%s", s);
    auto check = [](int a, int b) {
      for (int i = a; i < b - 1; i++) {
        if (s[i] == '#' && s[i + 1] == '#') {
          return false;
        }
      }
      return true;
    };
    bool result = check(a, c) && check(b, d);
    if (result && c > d) {
      bool change = false;
      for (int i = b; i <= d; i++) {
        if (s[i - 1] == '.' && s[i] == '.' && s[i + 1] == '.') {
          change = true;
        }
      }
      result &= change;
    }
    printf("%s\n", result ? "Yes" : "No");
  }

  return 0;
}
