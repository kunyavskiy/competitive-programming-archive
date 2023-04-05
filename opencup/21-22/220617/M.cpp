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

long long sums(vector<int> v) {
  sort(v.begin(), v.end());
  long long ans = 0;
  int n = (int)v.size();
  for (int i = 0; i < n; i++) {
    ans += v[i] * 1LL * (i - (n - i - 1));
  }
  eprintf("sums(%d,%d,%d) = %lld\n", v[0], v[1], v[2], ans);
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("m.in", "r", stdin);
  freopen("m.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> p(n), q(n);
    for (int &x: p) scanf("%d", &x);
    for (int &x: q) scanf("%d", &x);
    vector<int> s(n), m(n);
    for (int i = 0; i < n; i++) {
      s[i] = p[i] + q[i];
      m[i] = p[i] - q[i];
    }

    long long ans =
      sums(p) * 2 +
      sums(q) * 2 -
      (sums(s) + sums(m));
    printf("%lld\n", ans);
  }

  return 0;
}
