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

// diff b + c + 5d; 4a + 2b + c + d = n, a <= 2b
ll solve3(int n) {
}


// diff a + b + 2c + 10d; 5a + b + c + d = n
// diff b + 2c + 10d; 4a + b + c + d = n, a <= b
ll solve2(int n) {
  ll ans = 0;
  for (int i = 0; i <= 1 && i <= n; i++) {
    ans += solve3(n - i);
  }
  return ans;
}


// diff a + 5b + 10c + 50d; a + b + c + d = n
ll solve(int n) {
  ll ans = 0;
  for (int i = 0; i <= 4 && i <= n; i++) {
    ans += solve2(n - i);
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    printf("%lld\n", solve(n));
  }

  return 0;
}
