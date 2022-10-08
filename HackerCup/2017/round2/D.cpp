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

#define TASKNAME "D"

typedef long long ll;
typedef long double ld;

const int MOD = 1000000007;
const int INV2 = (MOD + 1) / 2;
const int INV3 = (MOD + 2) / 3;

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

void add(int& a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int& a, int b) {
  if ((a -= b) < 0) a += MOD;
}



int cnt;
int blue, white;

int c2(int h) {
  return mul(h, mul(h+1, INV2));
}

int c3(int h) {
  return mul(h, mul(h+1, mul(h + 2, mul(INV2, INV3))));
}

vector<int> rh;


void solve_one(int l, int m, int r, int h, int n) {
  if (h == n) return;
  int cntl = m - l;
  int cntr = r - m;

  int H = n - h;
  add(cnt, mul(cntl, mul(cntr, c2(H))));
  add(white, mul(cntl, mul(cntr, mul(cntl + cntr, mul(INV2, c3(H))))));
  add(blue, mul(cntl, mul(cntr, mul(cntl + cntr, mul(INV2, c3(H - 1))))));

  int psum = 0;

  int psuml = 0, psumr = 0;
  int csuml = 0, csumr = 0;

  for (int i = m; i > l; i--) {
    psuml += csuml;
    csuml += h - rh[i];
  }
  for (int i = m; i < r; i++) {
    psumr += csumr;
    csumr += h - rh[i];
  }

  psum = mul(psuml, psumr);

  add(blue, mul(psum, c2(H)));
}

void solve() {
  cnt = blue = white = 0;
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  rh.resize(m);
  vector<pair<int, int>> h(m);
  int ptr = 0;
  int sum = 0;
  for (int i = 0; i < k; i++) {
    int l, s, a, b;
    scanf("%d%d%d%d", &l, &s, &a, &b);

    for (int j = 0; j < l; j++) {
      h[ptr].first = rh[ptr] = s;
      add(sum, s);
      h[ptr].second = ptr;
      ptr++;
      s = (int) ((s * 1LL * a + b) % (n - 1) + 1);
    }
  }
  sort(h.begin(), h.end());

  set<int> s;
  for (int i = 0; i < m; i++) {
    s.insert(i);
  }

  for (auto x : h) {
    s.erase(x.second);
    auto it = s.lower_bound(x.second);
    int l, r;
    if (it == s.end()) {
      r = m;
    } else {
      r = *it;
    }
    if (it == s.begin()) {
      l = -1;
    } else {
      l = *(--it);
    }
    solve_one(l, x.second, r, x.first, n);
  }

  int gray = mul(cnt, sum);
  int black = mul(cnt, mul(n, m));
  sub(black, white);
  sub(black, blue);
  sub(black, gray);

  printf("%d %d %d %d\n", (MOD - black) % MOD, (MOD - white) % MOD, (MOD - gray) % MOD, (MOD - blue) % MOD);
}

int main() {
  assert(mul(INV2, 2) == 1);
  freopen(TASKNAME".in", "r", stdin);
  freopen(TASKNAME".out", "w", stdout);

  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    printf("Case #%d: ", i);
    solve();
  }

  return 0;
}
