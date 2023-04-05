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

const ll INFLL = ll(1e17);

vector<ll> create_empty(int d) {
  vector<ll> res(d, -INFLL);
  res[0] = 0;
  return res;
}

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

  int n, d;
  while (scanf("%d%d", &n, &d) == 2) {
    int off = 1;
    while (off < n) off <<= 1;

    const auto &merge = [&d](const vector<ll> &a, const vector<ll> &b) {
      vector<ll> res(d, -INFLL); // Not EMPTY, we should take one from a and one from b.
      for (int i = 0; i < d; i++) if (a[i] >= 0)
        for (int j = 0; j < d; j++) if (b[j] >= 0) {
          int ij = i + j;
          if (ij >= d) ij -= d;
          res[ij] = max(res[ij], a[i] + b[j]);
        }
      return res;
    };

    vector<vector<ll>> tr(2 * off, vector<ll>(d, -INFLL)); // Not EMPTY, we cannot take anyone.
    for (int i = 0; i < n; i++) {
      vector<ll> cur(d, -INFLL);  // Not EMPTY, we have to take someone.
      for (int i2 = 0; i2 < 3; i2++) {
        int x;
        scanf("%d", &x);
        cur[x % d] = max(cur[x % d], (ll)x);
      }
      tr[off + i] = cur;
    }
    for (int i = off - 1; i >= 1; i--) {
      tr[i] = merge(tr[2 * i], tr[2 * i + 1]);
    }

    for (int i = 1; i < 2 * off; i++) {
      eprintf("i=%d:", i);
      for (int i2 = 0; i2 < d; i2++)
        eprintf(" %lld", tr[i][i2]);
      eprintf("\n");
    }

    const vector<ll> EMPTY = create_empty(d);
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
      int l, r;
      scanf("%d%d", &l, &r), l--, r--;
      eprintf("%d..%d:", l, r);
      l += off; r += off;
      vector<ll> res = EMPTY;
      while (l <= r) {
        if (l & 1) res = merge(tr[l++], res);
        if (!(r & 1)) res = merge(res, tr[r--]);
        l >>= 1; r >>= 1;
      }
      for (int i2 = 0; i2 < d; i2++)
        eprintf(" %lld", res[i2]);
      eprintf("\n");
      ll ans = res[0];
      if (ans < 0) {
        ans = -1;
      }
      printf("%lld\n", ans);
    }
  }
  return 0;
}
