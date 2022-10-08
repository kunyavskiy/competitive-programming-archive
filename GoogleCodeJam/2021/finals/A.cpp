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

typedef long long ll;
typedef long double ld;

void PreCalc() {
}

struct rational {
  __int128 p, q;
  rational(__int128 a, __int128 b) : p(a), q(b) {
    __int128 g = __gcd(abs(a), b);
    p /= g;
    q /= g;
    assert(q);
  }
};

rational operator-(const rational&a) {
  return {-a.p, a.q};
}
rational operator*(const rational&a, __int128 x) {
  return {a.p * x, a.q};
}
rational operator*(const rational&a, const rational &b) {
  return {a.p * b.p, a.q * b.q};
}
rational operator/(const rational&a, const rational &b) {
  __int128 g = __gcd(b.q, a.q);
  return {a.p * (b.q / g), b.p * (a.q / g)};
}
rational operator+(const rational&a, const rational &b) {
  __int128 g = __gcd(a.q, b.q);
  return {a.p * (b.q / g) + b.p * (a.q / g), a.q * (b.q / g)};
}
rational operator-(const rational&a, const rational &b) {
  return a + (-b);
}

bool operator<(const rational& a, const rational&b) {
  return (a - b).p < 0;
}

void solve() {
  int n, w, h;
  scanf("%d%d%d", &n, &w, &h);
  int DX1_, DY1_, DX2_, DY2_;
  scanf("%d%d%d%d", &DX1_, &DY1_, &DX2_, &DY2_);
  if (DX1_ > DX2_) {
    swap(DX1_, DX2_);
    swap(DY1_, DY2_);
  }
  __int128 DX1 = DX1_;
  __int128 DX2 = DX2_;
  vector<__int128> x(n), a(n), b(n);
  vector<__int128> cands;
  for (int i = 0; i < n; i++) {
    int xx, aa, bb;
    scanf("%d%*d%d%d", &xx, &aa, &bb);
    x[i] = xx;
    a[i] = aa;
    b[i] = bb;
    cands.push_back(x[i]);
    cands.push_back(x[i] + DX1);
    cands.push_back(x[i] + DX2);
  }
  struct event {
    __int128 x;
    rational da;
    rational db;
    rational dc;
  };
  vector<event> es;
  rational inita{0, 1};
  rational initb{0, 1};
  rational initc{0, 1};
  for (int i = 0; i < n; i++) {
    initc = initc - rational{b[i], 1};
    if (DX1) {
      es.push_back({x[i], {(a[i] + b[i]), DX1 * DX2}, {-2 * (a[i] + b[i]) * x[i], DX1 * DX2}, {(a[i] + b[i]) * x[i] * x[i], DX1 * DX2}});
      es.push_back({x[i] + DX1, {-(a[i] + b[i]), DX1 * DX2}, {2 * (a[i] + b[i]) * x[i], DX1 * DX2}, {-(a[i] + b[i]) * x[i] * x[i], DX1 * DX2}});
    }
    if (DX1 != DX2) {
      es.push_back({x[i] + DX1, {0, 1}, {0, 1}, {a[i] + b[i], 1}});
      es.push_back({x[i] + DX1, {-(a[i] + b[i]), (DX2 - DX1) * DX2}, {2 * (a[i] + b[i]) * (DX2 + x[i]), (DX2 - DX1) * DX2}, {-(a[i] + b[i]) * (DX2 + x[i]) * (DX2 + x[i]), (DX2 - DX1) * DX2}});
      es.push_back({x[i] + DX2, {(a[i] + b[i]), (DX2 - DX1) * DX2}, {-2 * (a[i] + b[i]) * (DX2 + x[i]), (DX2 - DX1) * DX2}, {(a[i] + b[i]) * (DX2 + x[i]) * (DX2 + x[i]), (DX2 - DX1) * DX2}});
      es.push_back({x[i] + DX2, {0, 1}, {0, 1}, {a[i], 1}});
    }
  }
  sort(es.begin(), es.end(), [](const event& a, const event& b) { return a.x < b.x;});
  vector<rational> v;
  for (int i = 0; i < (int)es.size(); ) {
    int j = i;
    for (;es[i].x == es[j].x; j++) {
      inita = inita + es[j].da;
      initb = initb + es[j].db;
      initc = initc + es[j].dc;
    }
    if (j != (int)es.size()) {
      if (inita.p) {
        rational cand = -initb / (inita * 2);
        if (rational{es[i].x, 1} < cand && cand < rational{es[j].x, 1}) {
          v.push_back(inita * cand * cand + initb * cand + initc);
        }
      }
    }
    v.push_back(inita * es[i].x * es[i].x + initb * es[i].x + initc);
    i = j;
  }
  auto sign = [](__int128 x) {
    if (x < 0) return -1;
    if (x > 0) return 1;
    return 0;
  };
  for (int i = 1; i < (int)v.size(); i++) {
    if (sign(v[i].p) != sign(v[i - 1].p)) {
      printf("0/1\n");
      return;
    }
  }
  for (auto& x : v) if (x.p < 0) x.p = -x.p;
  auto res = *min_element(v.begin(), v.end());
  auto out = [](__int128 a) {
    assert(a >= 0);
    long long hi = a / 1'000'000'000'000'000'000LL;
    long long lo = a % 1'000'000'000'000'000'000LL;
    if (hi == 0) {
      printf("%lld", lo);
    } else {
      printf("%lld%018lld", hi, lo);
    }
  };
  out(res.p);
  printf("/");
  out(res.q);
  printf("\n");
}


int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  PreCalc();
  TIMESTAMP(PreCalc);

  char buf[1000];
  int testNum;
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d", &testNum);

  for (int testId = 1; testId <= testNum; testId++) {
    if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
      TIMESTAMPf("Test %d", testId);
    printf("Case #%d: ", testId);
    solve();
  }

  TIMESTAMP(end);
  return 0;
}
