#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x)                                                           \
  eprintf("[" #x "] Time : %.3lf s.\n",                                        \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...)                                                     \
  eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__,                            \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() { TIMESTAMPf("%s", what.data()); }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

#ifdef LOCAL
#define TEST
#endif

#ifdef TEST
int answer;
int balance;
#endif

int query(int x) {
  printf("? %d\n", x + 1);
  fflush(stdout);
#ifdef TEST
  if (x < answer) balance--;
  if (x > answer) balance++;
  return abs(balance);
#else
  int a;
  scanf("%d", &a);
  return a;
#endif
}

void result(int x) {
#ifdef TEST
  assert(x == answer);
#endif
  printf("! %d\n", x + 1);
  fflush(stdout);
}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
  scanf("%d", &answer);
  --answer;
#endif
  int n;
  scanf("%d", &n);
  int prev = 0;
  for (int i = 0; i < 20; i++) {
    int v = query(i);
    if (prev == v) {
      result(i);
      return 0;
    }
    prev = v;
  }

  int l = 20;
  int r = n;
  while (r - l > 1) {
    int m = (l + r) / 2;
    int v = query(m);
    if (v == prev) {
      result(m);
      return 0;
    }
    if (v > prev) {
      l = m + 1;
    } else {
      r = m;
    }
    prev = v;
  }

  result(l);
  return 0;
}
