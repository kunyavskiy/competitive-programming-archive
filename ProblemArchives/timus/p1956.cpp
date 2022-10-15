#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <deque>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#ifdef DEBUG
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define timestamp(str) eprintf("[ "str" ] time=%.4lf\n", clock() / double(CLOCKS_PER_SEC))
#else
#define eprintf(...)
#define timestamp(str)
#endif
#define sz(x) (int)((x).size())

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;

#define TASKNAME ""

const long long linf = 1e18;
const int inf = 1e9;
const double eps = 1e-9;
#define INF inf
#define EPS eps

const int MAXN = 1000;

#define sqr(x) (ll(x) * (x))

int sgn(ll x) { return x < 0 ? -1 : !!x; }
struct pt {
  int x, y;
  pt() : x(0), y(0) {}
  pt(int x, int y) : x(x), y(y) {}
  pt operator-(const pt &p2) const { return pt(x - p2.x, y - p2.y); }
  int operator*(const pt &p2) const { return sgn(ll(x) * p2.y - ll(y) * p2.x); }
  bool operator!=(const pt &p2) const { return x != p2.x || y != p2.y; }
};

int getd(int L, int R, int n) {
  if (L < R) return R - L;
  return n - L + R;
}

int norm(int x, int n) { return x >= n ? x - n : x; }

pt pts[MAXN];
bool acmp(const pt &a, const pt &b) {
  return a * b > 0;
}

bool isHpl(const pt &a) {
  return a.y > 0 || (a.y == 0 && a.x >= 0);
}

double calc(int n) {
  if (n <= 1) return 0;

  int mid = partition(pts, pts + n, isHpl) - pts;
  sort(pts, pts + mid, acmp);
  sort(pts + mid, pts + n, acmp);

  vector<ll> sumsx(n + 1), sumsy(n + 1);
  for (int i = 0; i < n; i++) {
    sumsx[i + 1] = sumsx[i] + pts[norm(i, n)].x;
    sumsy[i + 1] = sumsy[i] + pts[norm(i, n)].y;
  }
  ll sumxall = sumsx[n], sumyall = sumsy[n];

/*  eprintf("\n");
  for (int i = 0; i < n;i++)
    eprintf("%d %d\n", pts[i].x, pts[i].y);*/

  int laseq = 0;

  double ans = 1e100;
  for (int i = 0; i < n; i++) {
//    eprintf("\ni=%d\n", i);
    if (pts[i] * pts[laseq] != 0)
      laseq = i;

    int mid = laseq;
    {
      int pr = (laseq - 1 + n) % n;
//      eprintf("pr=%d\n", pr);
      if (pts[i] * pts[pr] < 0) {
        int L = i, R = pr;
        for (int step = 17; step >= 0; step--)
          while (getd(L, R, n) > (1 << step)) {
            int M = norm(L + (1 << step), n);
//            eprintf("%d %d %d; %d, %d\n", L, M, R, step, getd(L, R, n));
            if (pts[i] * pts[M] < 0) R = M;
            else L = M;
          }
        mid = R;
      }
    }

    ll sumx1 = 0, sumy1 = 0;
    if (i < mid) {
      sumx1 = sumsx[mid] - sumsx[i];
      sumy1 = sumsy[mid] - sumsy[i];
    } else {
      sumx1 = sumxall - sumsx[i] + sumsx[mid];
      sumy1 = sumyall - sumsy[i] + sumsy[mid];
    }

//    eprintf("mid=%d\n", mid);
    ll sumx2 = sumxall - sumx1;
    ll sumy2 = sumyall - sumy1;

//    eprintf("%I64d %I64d; %I64d %I64d\n", sumx1, sumy1, sumx2, sumy2);
    ll cans = 0;
    cans += sumx1 * -pts[i].y;
    cans += sumy1 * pts[i].x;
    cans -= sumx2 * -pts[i].y;
    cans -= sumy2 * pts[i].x;
    assert(cans >= 0);
    ans = min(ans, cans / sqrt(sqr(pts[i].x) + sqr(pts[i].y)));

    sumx1 -= pts[i].x;
    sumy1 -= pts[i].y;
  }
  return ans;
}

pt src[MAXN];

int main() {
/*  #ifdef DEBUG
  freopen(TASKNAME ".in", "r", stdin);
  freopen(TASKNAME ".out", "w", stdout);
  #else
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  #endif*/

  int n;
  while (scanf("%d", &n) >= 1) {
    for (int i = 0; i < n; i++)
      scanf("%d%d", &src[i].x, &src[i].y);

    if (n <= 2) {
      printf("0\n");
      continue;
    }

    double ans = 1e100;
    for (int st = 0; st < n; st++) {
      int ptr = 0;
      for (int i = 0; i < n; i++)
        if (i != st && src[i] != src[st])
          pts[ptr++] = src[i] - src[st];

      ans = min(ans, calc(ptr));
    }
    printf("%.18lf\n", fabs(ans));
  }

  timestamp("end");
  return 0;
}

