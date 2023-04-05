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

  ll a, b;
  while (scanf("%lld %lld", &a, &b) == 2) {
    vector<pair<char, char>> op;
    while (a != b) {
      if (a % 2 == 0 && b % 2 == 0) {
        a /= 2; b /= 2;
      } else if (a % 2 == 0) {
        op.emplace_back('B', 'B');
        b *= 2;
      } else if (b % 2 == 0) {
        op.emplace_back('A', 'A');
        a *= 2;
      } else if (a < b) {
        op.emplace_back('B', 'A');
        b += a;
      } else if (a > b) {
        op.emplace_back('A', 'B');
        a += b;
      } else {
        assert(0);
      }
    }

    printf("%d\n", (int)op.size());
    for (auto x : op) {
      printf("%c+=%c\n", x.first, x.second);
    }
  }

  return 0;
}
