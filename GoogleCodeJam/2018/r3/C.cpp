#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <assert.h>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

using namespace std;

typedef long long ll;
typedef long double ld;

void PreCalc() {
}

struct point {
  ll x, y, z;

  point(ll x, ll y, ll z) : x(x), y(y), z(z) {}

  point() { x = y = z = 0; }

  bool operator==(const point &a) const {
    return x == a.x && y == a.y && z == a.z;
  }
};

inline point operator+(const point &a, const point &b) {
  return point(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline point operator-(const point &a, const point &b) {
  return point(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline point operator*(const point &a, ll t) {
  return point(a.x * t, a.y * t, a.z * t);
}

inline ll det(ll a, ll b, ll c, ll d) {
  return a * d - b * c;
}

inline ll det(ll a11, ll a12, ll a13, ll a21, ll a22, ll a23, ll a31, ll a32, ll a33) {
  return a11 * det(a22, a23, a32, a33) - a12 * det(a21, a23, a31, a33) + a13 * det(a21, a22, a31, a32);
}

int sgn(ll x) {
  return (x > 0) - (x < 0);
}

inline ll det(const point &a, const point &b, const point &c) {
  return det(a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z);
}

point vp(const point &a, const point &b) {
  return point(det(a.y, a.z, b.y, b.z), -det(a.x, a.z, b.x, b.z), det(a.x, a.y, b.x, b.y));
}

ll sp(const point &a, const point &b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}


void solve() {
  int n;
  scanf("%d", &n);
  vector<point> pt(n);
  vector<int> order(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld%lld%lld", &pt[i].x, &pt[i].y, &pt[i].z);
    order[i] = i;
  }
  do {
    bool fail = false;
    for (int i = 2; i < n; i++) {
      point v = vp(pt[order[i]] - pt[order[i - 2]], pt[order[i - 1]] - pt[order[i - 2]]);
      if (v.z == 0) {
        fail = true;
        break;
      }
      if (v.z < 0) {
        v = v * -1;
      }
      for (int j = 0; j < i - 2; j++) {
        if (sp(v, pt[order[j]] - pt[order[i - 2]]) > 0) {
          fail = true;
        }
      }
    }
    if (!fail) {
      for (int i : order) {
        printf("%d ", i + 1);
      }
      printf("\n");
      return;
    }
  } while (next_permutation(order.begin(), order.end()));
  assert(false);
}


int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
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
