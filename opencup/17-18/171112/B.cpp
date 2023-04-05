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
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {

    map<int, int> cnt;

    for (int i = 0; i < m; i++) {
      int a;
      scanf("%d", &a);
      cnt[a]++;
    }

    int mx_cnt, mx_val;
    mx_cnt = mx_val = 0;

    for (auto x : cnt) {
      mx_cnt = max(mx_cnt, x.second);
      mx_val = max(mx_val, x.first);
    }

    int min_k = mx_cnt;
    int max_k = n / mx_val;

    int good = 0;

    for (int i = 1; i * i <= n; i++) {
      if (n % i == 0) {
        if (min_k <= i && i <= max_k) {
          good++;
        }
        if (i != n / i) {
          if (min_k <= n / i && n / i <= max_k) {
            good++;
          }
        }
      }
    }

    printf("%s\n", good == 1 ? "YES" : "NO");
  }

  return 0;
}
