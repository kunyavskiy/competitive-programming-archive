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

struct plane {
  ld a, b, c;

  ld eval(ld x, ld y) const {
    return a * x + b * y + c;
  }
};

plane p1, p2;

ld int1(ld x) {
  return 0.5 * (x * sqrt(1.0 - x * x) + asin(x));
}

ld int2(ld x) {
  return -1.0 / 3.0 * pow(1.0 - x * x, 1.5);
}

ld area(const plane &p1, ld ang, ld a, ld b) {
  ld ax = cos(ang) * 0;
  ld ay = sin(ang) * 0;
  ld bx = cos(ang) * 1;
  ld by = sin(ang) * 1;
  ld ah = p1.eval(ax, ay);
  ld bh = p1.eval(bx, by);
  return ah * (int1(b) - int1(a)) + (bh - ah) * (int2(b) - int2(a));
}

ld get_balance(const plane &p1, ld ang, ld x) {
  return area(p1, ang, x, 1) - area(p1, ang, -1, x);
}

pair<ld, ld> balance(ld ang) {
  ld l = -1;
  ld r = 1;
  for (int i = 0; i < 100; i++) {
    ld m = (l + r) / 2.0;
    ld val = get_balance(p1, ang, m);
    if (val > 0) {
      l = m;
    } else {
      r = m;
    }
  }
  return {get_balance(p2, ang, (l + r) / 2), (l + r) / 2};
}

ld read() {
  double x;
  scanf("%lf", &x);
  return x;
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  p1.a = read();
  p1.b = read();
  p1.c = read();
  p2.a = read();
  p2.b = read();
  p2.c = read();

  ld l = 0.0;
  ld r = M_PI;

  ld ball = balance(0).first;

  if (ball == 0) {
    l = r = 0;
  } else {
    for (int i = 0; i < 100; i++) {
      ld m = (l + r) / 2.0;
      ld f = balance(m).first;
      if (ball * f < 0) {
        r = m;
      } else {
        l = m;
      }
    }
  }

  ld ang = (l + r) / 2;
  auto bb = balance(ang);
  eprintf("b.first = %f\n",(double) bb.first);
  ld x = bb.second;

  ld a = cos(ang);
  ld b = sin(ang);

  ld px = cos(ang) * x;
  ld py = sin(ang) * x;

  ld c = a * px + b * py;
  
  printf("%.10f %.10f %.10f", (double)a, (double)b, (double)c);

  return 0;
}
