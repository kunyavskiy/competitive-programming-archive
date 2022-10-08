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

struct variable {
  int pos;
  ll value;
};

int var_id;

vector<string> output;
char buf[1000];

variable operator+(variable a, variable b) {
  sprintf(buf, "+ %d %d %d", a.pos, b.pos, var_id);
  output.push_back(buf);
  return {var_id++, a.value + b.value};
}

variable& operator+=(variable &a, variable b) {
  sprintf(buf, "+ %d %d %d", a.pos, b.pos, a.pos);
  output.push_back(buf);
  a.value += b.value;
  return a;
}


variable operator<(variable a, variable b) {
  sprintf(buf, "< %d %d %d", a.pos, b.pos, var_id);
  output.push_back(buf);
  return {var_id++, (a.value < b.value) ? 1 : 0};
}

variable get_zero() {
  return {var_id++, 0};
}

variable zero, one;

variable mul_bits(variable a, variable b) {
#ifdef LOCAL
  assert(a.value == 1 || a.value == 0);
  assert(b.value == 1 || b.value == 0);
#endif
  variable s = a + b;
  variable res = one < s;
#ifdef LOCAL
  assert(res.value == a.value * b.value);
#endif
  return res;
}

variable mul_bool(variable a, variable b) {
#ifdef LOCAL
  assert(b.value == 1 || b.value == 0);
#endif
  variable cur = get_zero();
  variable res = get_zero();
  for (int i = 30; i >= 0; i--) {
    variable p2 = one;
    for (int j = 0; j < i; j++) {
      p2 = p2 + p2;
    }
    p2 = cur + p2;
    p2 = p2 < a;
    variable add = mul_bits(p2, b);
    // p2 = p2 & check
    for (int j = 0; j < i; j++) {
      p2 = p2 + p2;
    }
    for (int j = 0; j < i; j++) {
      add = add + add;
    }
    cur += p2;
    res += add;
  }
  variable agz = zero < a;
  res += mul_bits(agz, b);
#ifdef LOCAL
  assert(cur.value == a.value - 1 || a.value == 0);
  assert(res.value == a.value * b.value);
#endif
  return res;
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  variable a{0, 0};
  variable b{1, 0};
#ifdef LOCAL
  scanf("%lld %lld", &a.value, &b.value);
#endif

  var_id = 2;
  variable res = get_zero();
  zero = get_zero();
  one = a < (a + a + b + b);
  variable cur = get_zero();

  for (int i = 29; i >= 0; i--) {
    variable nxt = one;
    for (int j = 0; j < i; j++) {
      nxt = nxt + nxt;
    }
    nxt = cur + nxt;
    nxt = nxt < b;
    variable add_val = mul_bool(a, nxt);
    for (int j = 0; j < i; j++) {
      nxt = nxt + nxt;
    }
    for (int j = 0; j < i; j++) {
      add_val = add_val + add_val;
    }
    cur += nxt;
    res += add_val;
  }
  res += mul_bool(a, zero < b);

  eprintf("ops = %d, vars = %d\n", (int)output.size(), var_id);
#ifdef LOCAL
  eprintf("res.value = %lld, a.value = %lld, b.value = %lld\n", res.value,a.value, b.value);
  assert(res.value == a.value * b.value);
#endif
  printf("%d\n", (int)output.size());
  for (const auto& x : output) {
    printf("%s\n", x.c_str());
  }

  return 0;
}
