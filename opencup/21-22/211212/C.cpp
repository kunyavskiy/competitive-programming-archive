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
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, k;
  while (scanf("%d%d", &n, &k) == 2) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }
    int mn = *min_element(a.begin(), a.end());
    for (int& x : a) x -= mn;
    int mx = *max_element(a.begin(), a.end());
    vector<vector<int>> v(mx + 1);
    for (int i = 0; i < n; i++) {
      v[a[i]].push_back(i);
    }
    int ans = 0;
    for (int i = 0; i <= mx; i++) {
      ans = max(ans, (int)v[i].size());
      int other = i - k;
      if (i != other && 0 <= other && other <= mx) {
        vector<int> ps(v[i].size() + v[other].size());
        merge(v[i].begin(), v[i].end(), v[other].begin(), v[other].end(), ps.begin());
        int mbal = 0;
        int bal = 0;
        for (int pos : ps) {
          if (a[pos] == i) {
            bal--;
          } else {
            bal++;
          }
          mbal = min(mbal, bal);
          ans = max(ans, (int)v[i].size() + bal - mbal);
        }
      }
    }
    printf("%d\n", ans);
  }

  return 0;
}
