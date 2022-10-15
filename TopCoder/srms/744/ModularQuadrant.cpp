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

class ModularQuadrant {

  ll sum3(ll r) {
    return (r + 1) / 3 + 2LL * (r / 3);
  }

  ll sum3(int l, int r) {
    return sum3(r) - sum3(l);
  }

  ll sum_sq(ll r) {
    ll ans = sum3(r);
    ll lim1 = (r + 1) / 3;
    ll lim2 = r / 3;
    ans += 2 * lim1;
    ans += 8 * lim2;
    ans += 3 * lim1 * (lim1 - 1);
    ans += 6 * lim2 * (lim2 - 1);

#ifdef LOCAL
    ll ans2 = 0;
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < r; j++) {
        ans2 += max(i, j) % 3;
      }
    }
    assert(ans == ans2);
#endif
    return ans;
  }

  ll get(int rx, int ry) {
    if (rx < ry) swap(rx, ry);
    ll ans = ry * 1LL * sum3(ry, rx);
    ans += sum_sq(ry);

#ifdef LOCAL
    ll ans2 = 0;
    for (int i = 0; i < rx; i++) {
      for (int j = 0; j < ry; j++) {
        ans2 += max(i, j) % 3;
      }
    }
    assert(ans == ans2);
#endif
    return ans;
  }

public:
  ll sum(int lx, int rx, int ly, int ry) {
    rx++, ry++;
    return get(rx, ry) - get(rx, ly) - get(lx, ry) + get(lx, ly);
  }
};










