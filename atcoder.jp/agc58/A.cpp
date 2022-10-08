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

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> p(2 * n);
    for (int i = 0; i < 2 * n; i++) {
      scanf("%d", &p[i]);
    }

    auto check = [&](int pos) {
      assert(pos % 2 != 0);
      if (pos >= 0 && p[pos] < p[pos + 1]) return false;
      if (p[pos + 1] > p[pos + 2]) return false;
      return true;
    };
    vector<int> ans;
    for (int i = 0; i < 2 * n; i += 2) {
      if (check(i - 1)) continue;
      swap(p[i], p[i + 1]);
      if (check(i - 1)) {
        ans.push_back(i);
        continue;
      }
      swap(p[i], p[i + 1]);
      assert(i != 0);
      swap(p[i - 1], p[i]);
      ans.push_back(i - 1);
      assert(check(i - 1));
    }
    printf("%d\n", (int) ans.size());
    for (int x: ans) printf("%d ", x + 1);
    printf("\n");
  }

  return 0;
}
