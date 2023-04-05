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

vector<vector<int>> teams;

struct Req {
  int l, r;  // [l, r].
  int id;
  ll ans;
};

int d;

vector<ll> init(const vector<int> &team) {
  vector<ll> res(d, -INFLL);
  for (int x : team)
    res[x % d] = max(res[x % d], (ll)x);
  return res;
}

vector<ll> append(const vector<ll> &prev, const vector<int> &team) {
  vector<ll> res(d, -INFLL);
  for (int x : team) {
    int xd = x % d;
    for (int i = 0; i < d; i++) {
      int ix = i + xd;
      if (ix >= d) ix -= d;
      res[ix] = max(res[ix], prev[i] + x);
    }
  }
  return res;
}

template<typename It>
void solve(int l, int r, It rbegin, It rend) {
  // [l, r] and [rbegin, rend).
  assert(l <= r);
  assert(rbegin <= rend);
  if (rbegin == rend) {
    return;
  }
  for (It i = rbegin; i != rend; i++) {
    assert(l <= i->l && i->l <= i->r && i->r <= r);
  }
  if (l == r) {
    ll cans = init(teams[l])[0];
    for (It i = rbegin; i != rend; i++) {
      i->ans = cans;
    }
    return;
  }

  int m = (l + r) / 2;  // [l, m] and [m+1,r].
  It lend = partition(rbegin, rend, [m](const Req &a) {
    return a.r <= m;
  });
  It mend = partition(lend, rend, [m](const Req &a) {
    return a.l <= m;
  });
  assert(rbegin <= lend);
  assert(lend <= mend);
  assert(mend <= rend);
  /*
  eprintf("split: [%d,%d] and [%d,%d]; offs=%td %td %td\n", l, m, m + 1, r, lend - rbegin, mend - rbegin, rend - rbegin);
  for (It i = rbegin; i != lend; i++)
    eprintf("  L: %d..%d\n", i->l, i->r);
  for (It i = lend; i != mend; i++)
    eprintf("  M: %d..%d\n", i->l, i->r);
  for (It i = mend; i != rend; i++)
    eprintf("  R: %d..%d\n", i->l, i->r);
    */
  solve(l, m, rbegin, lend);
  solve(m + 1, r, mend, rend);

  vector<vector<ll>> bords_(r - l + 1, vector<ll>(d, -INFLL));
  auto bords = [&bords_, &l](int x) -> vector<ll>& { return bords_[x - l]; };
  bords(m + 1) = init(teams[m + 1]);
  for (int i = m + 1; i < r; i++)
    bords(i + 1) = append(bords(i), teams[i + 1]);
  bords(m) = init(teams[m]);
  for (int i = m; i > l; i--)
    bords(i - 1) = append(bords(i), teams[i - 1]);
  for (It i = lend; i != mend; i++) {
    assert(i->l <= m);
    assert(i->r > m);
    ll &cans = i->ans = -INFLL;
    for (int lx = 0; lx < d; lx++) {
      int rx = lx ? d - lx : 0;
      cans = max(cans, bords(i->l)[lx] + bords(i->r)[rx]);
    }
  }
}


int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

  int n;
  while (scanf("%d%d", &n, &d) == 2) {
    teams.assign(n, vector<int>(3));
    for (int i = 0; i < n; i++) {
      for (int i2 = 0; i2 < 3; i2++)
        scanf("%d", &teams[i][i2]);
    }

    int m;
    scanf("%d", &m);
    vector<Req> rqs(m);
    for (int i = 0; i < m; i++) {
      scanf("%d%d", &rqs[i].l, &rqs[i].r);
      rqs[i].l--, rqs[i].r--;
      rqs[i].id = i;
      rqs[i].ans = -INFLL;
    }

    solve(0, n - 1, rqs.begin(), rqs.end());

    vector<ll> output(m);
    for (Req &r : rqs)
      output[r.id] = r.ans;
    for (int i = 0; i < m; i++)
      printf("%lld\n", max(-1LL, output[i]));
  }
  return 0;
}
