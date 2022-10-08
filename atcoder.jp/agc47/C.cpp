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

#define TIMESTAMP(x) eprintf("[" #x "] Time : %.3lf s.\n", (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

const int P = 200003;
const int MINDEEP = 4;


void add(ll *a, ll *b, int deep, int coef) {
  for (int i = 0; i < (1 << deep); i++)
    a[i] += b[i] * coef;
}

void mul(ll *a, ll *b, ll *res, int deep) {
  if (deep == MINDEEP) {
    for (int i = 0; i < (1 << deep); i++)
      for (int j = 0; j < (1 << deep); j++)
        res[i + j] += a[i] * b[j];
    return;
  }
  mul(a, b, res, deep - 1);
  mul(a + (1 << (deep - 1)), b + (1 << (deep - 1)), res + (1 << deep), deep - 1);
  vector<ll> temp(1 << deep);
  add(a, a + (1 << (deep - 1)), deep - 1, 1);
  add(b, b + (1 << (deep - 1)), deep - 1, 1);
  mul(a, b, &temp[0], deep - 1);
  add(a, a + (1 << (deep - 1)), deep - 1, -1);
  add(b, b + (1 << (deep - 1)), deep - 1, -1);
  add(&temp[0], res, deep, -1);
  add(&temp[0], res + (1 << (deep)), deep, -1);
  add(res + (1 << (deep - 1)), &temp[0], deep, 1);
}


int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  vector<int> id(P, -1);
  vector<int> rid(P - 1, -1);
  int cur = 1;
  for (int i = 0; i < P - 1; i++) {
    assert(i == 0 || cur != 1);
    id[cur] = i;
    rid[i] = cur;
    cur = (2 * cur) % P;
  }

  constexpr int PSIZE_LOG = 18;
  constexpr int PSIZE = 1 << PSIZE_LOG;

  int n;
  while (scanf("%d", &n) == 1) {
    vector<ll> a(PSIZE);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
      int x;
      scanf("%d", &x);
      if (x == 0) {
        continue;
      }
      a[id[x]]++;
      ans -= (x * 1LL * x) % P;
    }
    vector<ll> b = a;
    vector<ll> res(PSIZE * 2);
    mul(&a[0], &b[0], &res[0], PSIZE_LOG);
    for (int i = 0; i < (int)res.size(); i++) {
      ans += res[i] * 1LL * rid[i % (P - 1)];
    }
    ans /= 2;
    printf("%lld\n", ans);
  }

  return 0;
}
