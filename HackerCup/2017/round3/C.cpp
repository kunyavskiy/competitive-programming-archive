//#include <iostream>
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
#include <stdarg.h>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if (_WIN32 || __WIN32__)
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "C"

typedef long long ll;
typedef long double ld;

const int MOD = 1000000007;

void add(int& x, ll y) {
  x = (x + y) % MOD;
  if (x < 0) x += MOD;
}

vector<ll> read_lcg(int n) {
  vector<ll> res(n);
  scanf("%lld", &res[0]);
  int a, b, c, d;
  scanf("%d%d%d%d", &a, &b, &c, &d);
  for (int i = 1; i < n; i++) {
    res[i] = (res[i - 1] * 1LL * a + b) % c + d;
  }
  return res;
}

vector<ll> rs;
vector<ll> cs;

ll get_rsum(int a, int b) {
  return rs[b] - rs[a];
}

ll get_csum(int a, int b) {
  return cs[b] - cs[a];
}


void solve() {
  int n;
  scanf("%d", &n);
  vector<ll> c = read_lcg(n);
  vector<ll> r = read_lcg(n);

  for (int i = 0; i < 2*n; i++) {
    if (r[(i + 1) % n] > r[i % n] + c[i % n]) {
      r[(i + 1) % n] = r[i % n] + c[i % n];
    }
  }
  for (int i = 2 * n; i >= 0; i--) {
    if (r[(i + n - 1) % n] > r[i % n] + c[(i + n - 1) % n]) {
      r[(i + n - 1) % n] = r[i % n] + c[(i + n - 1) % n];
    }
  }

  for (int i = 0; i < 2*n; i++) {
    r.push_back(r[i]);
  }
  for (int i = 0; i < 2*n; i++) {
    c.push_back(c[i]);
  }
  rs = vector<ll> (r.size() + 1);
  for (int i = 0; i < (int)r.size(); i++) {
    rs[i + 1] = rs[i] + r[i];
  }
  cs = vector<ll> (c.size() + 1);
  for (int i = 0; i < (int)c.size(); i++) {
    cs[i + 1] = cs[i] + c[i];
  }
  vector<ll> cs2 = vector<ll> (cs.size() + 1);
  for (int i = 0; i < (int)c.size(); i++) {
    cs2[i + 1] = cs2[i] + cs[i];
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    add(ans, 2 * r[i]);
  }

  for (int i = n; i < 2*n; i++) {
    ll tot = get_csum(i, i + n);
    int lf = 0;
    int rg = n;
    while (rg - lf > 1) {
      int m = (lf + rg) / 2;
      ll s = get_csum(i, i + m);
      if (s <= tot - s) {
        lf = m;
      } else {
        rg = m;
      }
    }

//    for (int j = 0; j <= lf; j++) {
//      assert(get_csum(i, i + j) <= get_csum(i + j - n, i));
//      add(ans, min(get_csum(i, i + j), r[i] + r[i + j]));
//    }


    int llf = -1, lrg = lf + 1;
    while (lrg - llf > 1) {
      int m = (llf + lrg) / 2;
      if (get_csum(i, i + m) <= r[i] + r[i+m]) {
        llf = m;
      } else {
        lrg = m;
      }
    }
    add(ans, get_rsum(i + llf + 1, i + lf + 1));
    add(ans, r[i] * (lf - llf));
    add(ans, cs2[i + llf + 1] - cs2[i]);
    add(ans, -cs[i] * (llf + 1));


    int rlf = lf - n, rrg = 0;
    while (rrg - rlf > 1) {
      int m = (rlf + rrg) / 2;
      if (get_csum(i + m, i) >= r[i] + r[i+m]) {
        rlf = m;
      } else {
        rrg = m;
      }
    }
    add(ans, get_rsum(i + (lf - n + 1), i + rlf + 1));
    add(ans, r[i] * (rlf - (lf - n + 1) + 1));
    add(ans, -(cs2[i] - cs2[i + rlf + 1]));
    add(ans, cs[i] * (-rlf - 1));


//    for (int j = lf - n + 1; j < 0; j++) {
//      assert(get_csum(i + j, i) <= get_csum(i, i + j + n));
//      if (get_csum(i + j, i) <= r[i] + r[i+j]) {
//        assert(j > rlf);
//        add(ans, /*cs[i]*/ - cs[(i + j)]);
//      } else {
//        assert(j <= rlf);
//        add(ans, r[i] + r[i + j]);
//      }
//    }
  }

  printf("%d\n", (int) ((ans * 1LL * (MOD + 1) / 2) % MOD));
}

int main() {
  freopen(TASKNAME".in", "r", stdin);
  freopen(TASKNAME".out", "w", stdout);

  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    printf("Case #%d: ", i);
    fprintf(stderr, "Case #%d of %d\n", i, t);
    solve();
  }

  return 0;
}
