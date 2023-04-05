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

const int MAXN = 10 * 1000 * 1000 + 100;

int invv[MAXN];

int mul(int a, int b, int p) {
  return (a * 1LL * b) % p;
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int p, r;
  ll _n;
  scanf("%lld%d%d", &_n, &p, &r);

  if (_n >= 2 * p) {
    if (r == 0) {
      printf("%d %d\n", 2, 1);
    } else {
      printf("-1 -1\n");
    }
    return 0;
  }

  int n = (int)_n;


  invv[1] = 1;
  for (int i = 2; i < p; i++) {
    invv[i] = mul(p - invv[p % i], p / i, p);
    assert(mul(i, invv[i], p) == 1);
  }
  int val = 1;
  for (int i = 1; i <= n; i++) {
    if (i != p) {
      val = mul(val, i, p);
    }
  }

  if (r == 0) {
    if (n > p) {
      printf("%d %d\n", n, n - 1);
    } else if (p > 2 && n >= p) {
      printf("%d %d\n", 2, 1);
    } else {
      printf("-1 -1\n");
    }
    return 0;
  }

  if (n >= p) {
    int need = mul(r, invv[val], p);
    printf("%d %d\n", p, need);
    return 0;
  }

  for (int i = 1; i <= n; i++) {
    int nval = mul(val, invv[i % p], p);
    nval = mul(r, invv[nval], p);
    if (nval < i) {
      printf("%d %d\n", i, nval);
      return 0;
    }
  }
  printf("-1 -1\n");
  return 0;
}
