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

int solve(vector<ll> a, string s) {
  int n = a.size();
  for (int i = n - 1; i >= 0; i--) {
    if (a[i] == 0) continue;
    if (s[i] == '1') {
      return 1;
    }
    ll bit = a[i] & ~(a[i] - 1);
    for (int j = 0; j < i; j++) {
      if (a[j] & bit) {
        a[j] ^= a[i];
      }
    }
  }
  return 0;
}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  scanf("%*d");
  int n;
  while (scanf("%d", &n) == 1) {
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
      scanf("%lld", &a[i]);
    }
    char s[300];
    scanf("%s", s);
    printf("%d\n", solve(a, s));

  }

  return 0;
}
