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

struct bit {
  vector<int> x;
  int n;
  explicit bit(int n) : x(n), n(n) {}
  void add(int pos) {
    while (pos < n) {
      x[pos]++;
      pos = pos | (pos + 1);
    }
  }
  int get(int pos) {
    int res = 0;
    while (pos != -1) {
      res += x[pos];
      pos = (pos & (pos + 1)) - 1;
    }
    return res;
  }
};

bool solve() {
  int n;
  scanf("%d", &n);
  vector<int> p(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &p[i]);
    p[i]--;
  }
  bit t(n);
  long long tot = 0;
  for (int i = n - 1; i >= 0; i--) {
    tot += t.get(p[i]);
    t.add(p[i]);
  }
  tot--;
  int x = 0;
  while (tot > 0) {
    if (tot < n - x - 1) break;
    if (p[x] != x) return false;
    tot -= (n - x - 1);
    x++;
  }
  for (int y = x; y <= x + tot; y++) {
    if (p[y] < p[x]) {
      return std::is_sorted(p.begin() + x, p.begin() + y) && *min_element(p.begin() + y + 1, p.begin() + x + tot + 2) > p[y - 1];
    }
  }
  return true;
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    bool r = solve();
    if (r) printf("Yes\n"); else printf("No\n");
  }

  return 0;
}
