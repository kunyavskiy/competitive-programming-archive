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

ll s[64];

ll MOD = 1000000007;

ll calc(int k, ll n) {
//  cerr << k << " " << n << "\n";
  assert(k >= 0);
  assert(n >= 1 && n <= (1LL << k));

  if (n == 1) return 1;
  if (n == (1LL << k)) return s[k];

  if (n <= (1LL << (k - 1))) {
    return calc(k - 1, n);
  } else {
    ll res = s[k - 1];
    res = (res + calc(k - 1, n - (1LL << (k - 1)) + 1) + MOD - 1) % MOD;
    res = (res + ((1LL << (k - 2)) % MOD) * ((n - (1LL << (k - 1))) % MOD)) % MOD;
    return res;
  }
}

void solve_test() {
  ll n;
  scanf("%lld", &n);
  cout << calc(62, n) << "\n";
}
int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  s[0] = 1;
  s[1] = 2;
  for (int i = 2; i < 64; i++) {
    s[i] = (s[i - 1] + s[i - 1] + MOD - 1) % MOD;
    s[i] = s[i] + ((1LL << (i - 2)) % MOD) * (((1LL << (i - 1)) - 1) % MOD) + (1LL << (i - 1));
    s[i] %= MOD;
//    cout << i << " " << s[i] << "\n";
  }


  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    solve_test();
  }

  return 0;
}
