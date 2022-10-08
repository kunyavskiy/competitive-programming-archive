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

//"AAABAAABAAABAAABAA"

void solve() {
  ll a, b;
  int l, r;
  scanf("%lld%lld%d%d", &a, &b, &l, &r);
  ll k = (a + b) / (min(a, b) + 1);

  // AAB

  ll lf = 0;
  ll rg = a + 1;
  while (rg - lf > 1) {
    ll m = (lf + rg) / 2;
    ll totb_min = m * 1LL * k + (a - m + 1) / k;
    if (totb_min > b) {
      rg = m;
    } else {
      lf = m;
    }
  }

  ll AKB = (a - lf) / k;
  ll BKA = lf;
  ll midA = a - AKB * k - BKA;
  ll midB = b - AKB - BKA * k;
  assert(midA <= k);
  assert(midB <= k);

  int cnt[2];
  cnt[0] = cnt[1] = 0;

  int last = 'A';
  int last_cnt = 0;

  for (ll i = l - 1; i < r; i++) {
    char c;
    if (i < AKB * (k + 1)) {
      c = (i % (k + 1) == k) ? 'B' : 'A';
    } else if (i < AKB * (k + 1) + midA) {
      c = 'A';
    } else if (i < AKB * (k + 1) + midA + midB) {
      c = 'B';
    } else {
      c = ((i - AKB * (k + 1) - midB - midA) % (k + 1) == 0) ? 'A' : 'B';
    }
    printf("%c", c);
    if (c == last) {
      last_cnt++;
      assert(last_cnt <= k);
    } else {
      last_cnt = 1;
      last = c;
    }
    cnt[c - 'A']++;
  }
  printf("\n");
  if (l == 1 && r == a + b) {
    assert(cnt[0] == a);
    assert(cnt[1] == b);
  }
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0)
    solve();
  return 0;
}
