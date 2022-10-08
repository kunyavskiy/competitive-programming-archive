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

const int MOD = 998244353;

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

void adamar(vector<int> &x) {
  size_t n = x.size();
  for (size_t i = 1; i < n; i *= 2) {
    for (size_t j = 0; j < n; j++) {
      if (!(j & i)) {
        int a = x[j];
        int b = x[j ^ i];
//        eprintf("%d %d -> ", x[j], x[j ^ i]);
        x[j] = a;
        add(x[j], b);
        x[j ^ i] = a;
        sub(x[j ^ i], b);
//        eprintf("%d %d\n", x[j], x[j ^ i]);
      }
    }
  }
}

void out(int n) {
  for (int i = 1; i < 100; i++) {
    int x = mul(n, i);
    if (x < 100) {
      eprintf("%d/%d\n", x, i);
      return;
    } else if (x > MOD - 100) {
      eprintf("-%d/%d\n", MOD - x, i);
      return;
    }
  }
  eprintf("??[%d]", n);
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    n = (1 << n);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }
    int s = 0;
    for (int i = 0; i < n; i++) {
      add(s, a[i]);
    }
    adamar(a);

    vector<int> result(n);
    int n2 = mul(s, n);
    result[0] = n2;
    for (int i = 1; i < n; i++) {
      int t = a[i];
      sub(t, a[0]);
      result[i] = mul(s, minv(t));
      sub(result[0], mul(a[i], result[i]));
    }
    result[0] = mul(result[0], minv(a[0]));

    int temp = 0;
    for (int i = 0; i < n; i++) {
      add(temp, mul(result[i], a[i]));
    }
    assert(temp == n2);

    adamar(result);
    for (int i = 0; i < n; i++) {
      sub(result[i], 1);
      printf("%d\n", result[i]);
    }
  }

  return 0;
}
