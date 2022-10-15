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

void solve(int n) {
  vector<ll> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &a[i]);
  }
  ll tot = 0;
  int last = 0;
  for (int i = 1; i < n; i++) {
    if (a[i - 1] == 0) continue;
    if (a[i] == 0) {
      printf("-1\n");
      return;
    }
    ll x = a[i];
    while (x < a[i - 1]) {
      x *= 2;
      last++;
    }
    ll y = a[i - 1];
    while (last && y * 2 <= a[i]) {
      y *= 2;
      last--;
    }
    tot += last;
  }
  printf("%lld\n", tot);
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    solve(n);
  }

  return 0;
}
