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
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n, k;
  while (scanf("%d%d", &n, &k) == 2) {
    vector<int> v(n);
    for (int& x : v) scanf("%d", &x);
    set<int> s;
    int ans = n - k + 1;
    for (int i = 0; i < k; i++) {
      s.insert(v[i]);
    }
    int sorted = 0;
    vector<bool> sorted_seg(n);
    if (k == 1) sorted_seg[0] = true;
    for (int i = 1; i < n; i++) {
      if (v[i] > v[i-1]) {
        sorted++;
      }
      if (i >= k && v[i - k + 1] > v[i - k]) {
        sorted--;
      }
      if (sorted == k - 1) sorted_seg[i] = true;
    }

    bool have_sorted = sorted_seg[k - 1];

    for (int i = k; i < n; i++) {
      s.insert(v[i]);
      if ((v[i] == *--s.end() && v[i - k] == *s.begin()) || (sorted_seg[i] && have_sorted)) ans--;
      have_sorted |= have_sorted || sorted_seg[i];
      s.erase(v[i - k]);
    }


#ifdef LOCAL
    set<vector<int>> ss;
    for (int i = k; i <= n; i++) {
      vector<int> u = v;
      sort(u.begin() + i - k, u.begin() + i);
//      for (int j = 0; j < n; j++) eprintf("%d ", u[j]);
      if (!ss.insert(u).second) {
//        eprintf("!!!!");
      }
//      eprintf("\n");
    }
//    eprintf("%d %d\n", n, k);
//    assert((int)ss.size() == ans);
#endif
    printf("%d\n", ans);
  }

  return 0;
}
