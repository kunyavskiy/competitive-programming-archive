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

#ifdef LOCAL
int n;
int xx0, yy0, zz0;
int xx1, yy1, zz1;

void swapXZ() {
  swap(xx0, zz0);
  swap(xx1, zz1);
}

void swapXY() {
  swap(xx0, yy0);
  swap(xx1, yy1);
}

void symZ() {
  zz0 = 2 * n - zz0;
  zz1 = 2 * n - zz1;
}

void symY() {
  yy0 = 2 * n - yy0;
  yy1 = 2 * n - yy1;
}

static inline int sqr(int x) {
  return x * x;
}

int getDist() {
  return sqr(xx0 - xx1) + sqr(yy0 - yy1) + sqr(zz0 - zz1);
}

int sign(int x) {
  if (x > 0) {
    return 1;
  } else if (x < 0) {
    return -1;
  } else {
    return 0;
  }
}
#endif

int go_forward() {
  printf("forward\n");
  fflush(stdout);
#ifdef LOCAL
  int d1 = getDist();
  assert(zz1 == 0);
  assert(xx1 % 2 == 1 && yy1 % 2 == 1);
  if (xx1 == 2 * n - 1) {
    xx1 += 1;
    zz1 += 1;
    swapXZ();
    symZ();
  } else {
    xx1 += 2;
  }
  int d2 = getDist();
  eprintf("forward (%d %d %d) => (%d %d %d)\n", xx1, yy1, zz1, xx0, yy0, zz0);
  return sign(d2 - d1);
#else
  static char s[20];
  scanf("%s", s);
  if (!strcmp(s, "farther")) {
    return 1;
  } else if (!strcmp(s, "closer")) {
    return -1;
  } else if (!strcmp(s, "same")) {
    return 0;
  } else {
    assert(0);
  }
#endif
}

void turn_left() {
  printf("left\n");
  fflush(stdout);
#ifdef LOCAL
  swapXY();
  symY();
  eprintf("left (%d %d %d) => (%d %d %d)\n", xx1, yy1, zz1, xx0, yy0, zz0);
#endif
}

void go_backward() {
  turn_left();
  turn_left();
  go_forward();
  turn_left();
  turn_left();
}

void dig() {
  printf("dig\n");
  fflush(stdout);
#ifdef LOCAL
  assert(xx0 == xx1 && yy0 == yy1 && zz0 == zz1);
#endif
}

int main() {
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
//  freopen("output.txt", "w", stdout);

  scanf("%d%d%d%d%d%d%d", &n, &xx0, &yy0, &zz0, &xx1, &yy1, &zz1);
#endif


  bool is_decr = false;
  while (1) {
    int x = go_forward();
    eprintf("x = %d\n", x);
    if (x <= 0 && !is_decr) { is_decr = true; continue; }
    if (x >= 0 && is_decr) { break; }
  }
  go_backward();
  turn_left();
  int cnt[3] = {0, 0, 0};
  int cur = 0;
  int prev_x = 1;
  while (1) {
    int x = go_forward();
    if (x < 0 && prev_x >= 0) {
      cur++;
      if (cur > 2) { break; }
    }
    if (x != 0) {
      cnt[cur]++;
    }
    prev_x = x;
  }
  eprintf("cnt[0] %d cnt[1] %d cnt[2] %d\n", cnt[0], cnt[1], cnt[2]);
  while (go_forward() <= 0) {
  }
  go_backward();
  if (cnt[2] >= cnt[1]) {
    bool is_decr = false;
    while (1) {
      int x = go_forward();
      if (x < 0 && !is_decr) { is_decr = true; continue; }
      if (x > 0 && is_decr) { break; }
    }
    go_backward();
  }

  dig();

  return 0;
}
