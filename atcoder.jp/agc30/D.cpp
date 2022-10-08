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

const int MOD = 1000000007;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) {
  return mpow(x, MOD - 2);
}

struct data {
  int m;
  int im;
  vector<vector<int>> vals;

  int get(int x, int y) {
    return mul(vals[x][y], m);
  }

  void set(int x, int y, int v) {
    vals[x][y] = mul(v, im);
  }

  void mult_all(int x) {
    m = mul(m, x);
    im = mul(im, minv(x));
  }

  data(int n): m(1), im(1), vals(n, vector<int>(n, 0)) {}
};

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n, q;
  int i2 = minv(2);
  while (scanf("%d%d", &n, &q) == 2) {
    data d(n);
    vector<int> v(n);
    for (int i = 0; i < n; i++){
      scanf("%d", &v[i]);
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        d.set(i, j, v[i] > v[j]);
      }
    }

    for (int i = 0; i < q; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      --x, --y;
      if (x > y) swap(x, y);
      d.mult_all(2);
      for (int z = 0; z < n; z++) {
        if (z == x || z == y) continue;
        {
          int a = d.get(x, z);
          int b = d.get(y, z);
          add(a, b);
          a = mul(a, i2);
          d.set(x, z, a);
          d.set(y, z, a);
        }
        {
          int a = d.get(z, x);
          int b = d.get(z, y);
          add(a, b);
          a = mul(a, i2);
          d.set(z, x, a);
          d.set(z, y, a);
        }
      }

      int a = d.get(x, y);
      int b = d.get(y, x);
      add(a, b);
      a = mul(a, i2);
      d.set(x, y, a);
      d.set(y, x, a);

//      eprintf("===\n");
//      for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//          eprintf("%d ", d.get(i, j));
//        }
//        eprintf("\n");
//      }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        add(ans, d.get(i, j));
      }
    }
    printf("%d\n", ans);
  }

  return 0;
}
