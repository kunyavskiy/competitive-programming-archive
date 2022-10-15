#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <functional>
#include <bitset>
#include <ctime>
#include <cassert>
#define pb push_back
#define mp make_pair      
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
 
typedef long long ll;
typedef long double ld;


class ArmorUp {

  struct lin {
    double a, b;
  };

  lin compose(lin x, lin y) {
    return {x.a * y.a, x.a * y.b + x.b};
  }

  bool check(double d, double m, double x, int k) {
    lin a = {1 - d / (2.0 * m), -d / 2.0};
    lin res = {1, 0};
    while (k) {
      if (k & 1) res = compose(res, a);
      a = compose(a, a);
      k >>= 1;
    }
    double value = res.a * x + res.b;
    return value <= 0;
  }

public:
  double minimalDamage(int m, int x, int k) {
    double l = 0.0;
    double r = 2 * x;
    for (int i = 0; i < 100; i++) {
      double d = (l + r) / 2;
      if (check(d, m, x, k)) {
        r = d;
      } else {
        l = d;
      }
    }
    return (l + r) / 2;
  }
};










