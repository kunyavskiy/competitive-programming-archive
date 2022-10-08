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

  int n;
  while (scanf("%d", &n) == 1) {
    vector<ll> a(n), b(n);
    for (ll &x : a) scanf("%lld", &x);
    for (ll &x : b) scanf("%lld", &x);
    vector<ll> v[2];
    v[0].resize(n/2);
    v[1].resize(n/2);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
      ans += a[i];
      v[i % 2][i / 2] = b[i] - a[i];
    }
    sort(v[0].rbegin(), v[0].rend());
    sort(v[1].rbegin(), v[1].rend());
    for (int i = 0; i < n / 2; i++) {
      if (v[0][i] + v[1][i] > 0) {
        ans += v[0][i] + v[1][i];
      }
    }
    printf("%lld\n", ans);
  }

  return 0;
}
