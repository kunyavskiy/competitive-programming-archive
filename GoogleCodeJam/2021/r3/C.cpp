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

int sgn(ll x) { return x < 0 ? -1 : x > 0; }
struct pt {
  int x, y;
  pt() : x(0), y(0) {}
  pt(int x, int y) : x(x), y(y) {}
  pt operator+(const pt &p2) const { return pt(x + p2.x, y + p2.y); }
  pt operator-(const pt &p2) const { return pt(x - p2.x, y - p2.y); }
  int operator*(const pt &p2) const { return sgn(ll(x) * p2.y - ll(y) * p2.x); }
  int operator^(const pt &p2) const { return sgn(ll(x) * p2.x + ll(y) * p2.y); }
  bool operator==(const pt &p2) const { return x == p2.x && y == p2.y; }
};

struct line {
  long long a, b, c;
  line() : a(0), b(0), c(1) {}
  line(const pt &p1, const pt &p2) {
    a = p1.y - p2.y;
    b = p2.x - p1.x;
    c = -a * p1.x - b * p1.y;
  }
  int side(const pt &p2) const { return sgn(a * p2.x + b * p2.y + c); }
};

bool intersects(const pt& a, const pt& b, const pt&c, const pt&d) {
  line l1{a, b};
  line l2{c, d};
  return l1.side(c) != l1.side(d) && l2.side(a) != l2.side(b);
}


void solve() {
  int n;
  scanf("%d", &n);
  vector<pt> ps(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &ps[i].x, &ps[i].y);
  }
  int a, b, c, d;
  scanf("%d%d%d%d", &a, &b, &c, &d);
  --a, --b, --c, --d;

  vector<int> done = {a, b, c, d};
  vector<pair<int, int>> ans;

  auto try_add = [&](int x, int y) {
    for (auto [a, b] : ans) {
      if (a == x || a == y || b == x || b == y) continue;
      if (intersects(ps[a], ps[b], ps[x], ps[y])) return;
    }
    ans.emplace_back(x, y);
  };

  if (b == d || b == c) swap(a, b);
  if (a == d) swap(c, d);
  try_add(a, b);
  try_add(c, d);

  if (a == c) {
    done = {a, b, d};
    try_add(b, d);
  } else {
    done = {a, b, c, d};
    try_add(a, c);
    try_add(a, d);
    try_add(b, c);
    try_add(b, d);
  }

  for (int i = 0; i < n; i++) {
    if (find(done.begin(), done.end(), i) != done.end()) continue;
    for (int x : done) {
      try_add(i, x);
    }
    done.push_back(i);
  }

  ans.erase(ans.begin());
  ans.erase(ans.begin());
  printf("%d\n", (int)ans.size());
  for (auto [a, b] : ans) {
    printf("%d %d\n", a + 1, b + 1);
  }
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
