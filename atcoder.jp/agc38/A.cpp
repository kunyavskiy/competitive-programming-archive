#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <numeric>
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

  int w, h, a, b;
  while (scanf("%d%d%d%d", &h, &w, &a, &b) == 4) {
    vector<int> rs, cs;
    for (int i = 0; i <= h && rs.empty(); i++) {
      for (int j = 0; j <= w; j++) {
        if (i * a + (h - i) * (w - a) == j * b + (w - j) * (h - b)) {
          rs.resize(h);
          for (int k = 0; k < h; k++) {
            rs[k] = (k < i) ? a : w - a;
          }
          cs.resize(w);
          for (int k = 0; k < w; k++) {
            cs[k] = (k < j) ? b : h - b;
          }
          assert(accumulate(cs.begin(), cs.end(), 0) == accumulate(rs.begin(), rs.end(), 0));
          break;
        }
      }
    }
    if (rs.empty()) {
      printf("-1\n");
      continue;
    }
    vector<int> v(w);
    for (int i = 0; i < w; i++) {
      v[i] = i;
    }
    for (int i = 0; i < h; i++) {
      sort(v.begin(), v.end(), [&](int a, int b) { return cs[a] > cs[b];});
      string s(w, '0');
      for (int j = 0; j < rs[i]; j++) {
        s[v[j]] = '1';
        cs[v[j]]--;
      }
      printf("%s\n", s.data());
    }
  }

  return 0;
}
