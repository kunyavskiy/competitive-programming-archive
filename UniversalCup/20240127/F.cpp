#undef NDEBUG
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

struct item {
  ll a, b;
  bool small;
};

bool operator<(item a, item b) {
  return std::tie(a.a, a.b, a.small) < std::tie(b.a, b.b, b.small);
}

char s[110000];
int ptr;
item get_expr();

int get_pow() {
  if (s[ptr] != '^') return 1;
  ptr++;
  int d = 0;
  while ('0' <= s[ptr] && s[ptr] <= '9') {
    d = d * 10 + s[ptr] - '0';
    ptr++;
  }
  return d;
}

item get_factor() {
  if (s[ptr] == 'N') {
    ptr++;
    return item{get_pow(), 0, 0};
  }
  if (s[ptr] == 'l') {
    ptr++;
    assert(s[ptr++] == 'o');
    assert(s[ptr++] == 'g');
    assert(s[ptr++] == '(');
    auto r = get_expr();
    assert(s[ptr++] == ')');
    int p = get_pow();
    if (r.a == 0) {
      return item {0, 0, r.b > 0 || r.small};
    } else {
      return item{0, p, false};
    }
  }
  if (s[ptr] == '(') {
    ptr++;
    auto r = get_expr();
    assert(s[ptr++] == ')');
    return r;
  }
  assert(false);
}

item get_term() {
  auto res = get_factor();
  while (s[ptr] == '*') {
    ptr++;
    auto other = get_factor();
    res = item{res.a + other.a, res.b + other.b, res.small || other.small};
  }
  return res;

}

item get_expr() {
  auto res = get_term();
  while (s[ptr] == '+') {
    ptr++;
    auto other = get_term();
    res = max(res, other);
  }
  return res;
}

int main() {
  #ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
  #endif

  while (scanf("%s", s) == 1) {
    ptr = 0;
    auto [a, b, small] = get_expr();
    assert(s[ptr] == 0);
    if (small)
      b++;
    printf("%lld %lld\n", a, b);
  }

  return 0;
}
