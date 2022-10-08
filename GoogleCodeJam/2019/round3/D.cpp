#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>

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

int sgn(ll x) { return x < 0 ? -1 : x > 0; }
struct point {
  int x, y;
  point() : x(0), y(0) {}
  point(int x, int y) : x(x), y(y) {}
  point operator+(const point &p2) const { return point(x + p2.x, y + p2.y); }
  point operator-(const point &p2) const { return point(x - p2.x, y - p2.y); }
  bool operator==(const point &p2) const { return x == p2.x && y == p2.y; }
};

struct line {
  ll a, b, c;

  line() : a(0), b(0), c(1) {}

  line(const point &p1, const point &p2) {
    a = p1.y - p2.y;
    b = p2.x - p1.x;
    c = -a * p1.x - b * p1.y;
  }

  line(int a, int b, int c) : a(a), b(b), c(c) {}

  ll dist(const point &p2) const { return a * p2.x + b * p2.y + c; }

  bool are_sym(const point &p1, const point &p2) {
    ll d1 = dist(p1);
    ll d2 = dist(p2);
    if (d1 != -d2) return false;
    if (d1 == 0) return p1 == p2;
    point d = p1 - p2;
    return d.x * 1LL * b - d.y * 1LL * a == 0;
  }
};



void solve() {
  int n;
  scanf("%d%*d", &n);

  vector<point> p(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &p[i].x, &p[i].y);
    p[i].x *= 2;
    p[i].y *= 2;
  }

  line result(0, 0, 0);

  auto good_split = [&](line l) {
    int isects = 0;
    for (int i = 0; i < n; i++) {
      if (l.dist(p[i]) == 0) {
        isects++;
      }
    }
    for (int i = 0; i < n; i++) {
      if (sgn(l.dist(p[i])) * sgn(l.dist(p[(i + 1) % n])) < 0) {
        isects++;
      }
      if (!l.dist(p[i]) && !l.dist(p[(i + 1) % n])) {
        return false;
      }
    }
    return isects == 2;
  };

  for (int i = 0; i < n; i++) {
    for (int j = 1; j < n; j++) {
      line l(p[0], p[j]);
      if (!good_split(l)) continue;
      bool ok = true;
      for (int k = 1; k < n; k++) {
        ok = ok && l.are_sym(p[k], p[n - k]);
      }
      if (ok) {
        result = l;
      }
    }
    rotate(p.begin(), p.begin() + 1, p.end());
  }

  for (int i = 0; i < n; i++) {
    for (int j = 1; j < n; j++) {
      point v = p[j] - p[i];
      line l(v.x, v.y, 0);
      l.c = -(l.dist(p[i]) + l.dist(p[j])) / 2;
      assert(l.are_sym(p[i], p[j]));
      if (!good_split(l)) continue;
      bool ok = true;
      for (int k = 0; k < n; k++) {
        ok = ok && l.are_sym(p[k], p[(j + i - k +  3 * n) % n]);
      }
      if (ok) {
        result = l;
      }
    }
  }

  if (!result.a && !result.b) {
    printf("IMPOSSIBLE\n");
    return;
  }
  eprintf("%lld %lld %lld\n", result.a, result.b, result.c);
  printf("POSSIBLE\n");

  vector<ll> answer;
  for (int i = 0; i < n; i++) {
    if (result.dist(p[i]) == 0) {
      answer.push_back(p[i].x);
      answer.push_back(2);
      answer.push_back(p[i].y);
      answer.push_back(2);
    }
  }

  for (int i = 0; i < n; i++) {
    point p1 = p[i];
    point p2 = p[(i + 1) % n];
    if (sgn(result.dist(p1) * sgn(result.dist(p2)) < 0)) {
      line l1 = result;
      line l2(p1, p2);
      ll d = l1.a * l2.b - l1.b * l2.a;
      ll x = (l1.b * l2.c - l1.c * l2.b);
      ll y = -(l1.a * l2.c - l1.c * l2.a);
      answer.push_back(x);
      answer.push_back(2 * d);
      answer.push_back(y);
      answer.push_back(2 * d);
    }
  }
  assert(answer.size() == 8);

  for (int i = 0; i < 8; i += 2) {
    ll n = answer[i];
    ll d = answer[i + 1];
    if (d < 0) {
      n = -n;
      d = -d;
    }
    ll g = __gcd(abs(n), abs(d));
    n /= g;
    d /= g;
    printf("%lld/%lld%c", n, d, " \n"[i == 6]);
  }
}


int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
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
