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

const int MOD = 1000000009;

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

int norm(int x) {
  return (x + MOD) % MOD;
}

void solve(int n) {
  vector<int> x(n), y(n);
  for (int i = 0;  i < n; i++) {
    scanf("%d%d", &x[i], &y[i]);
  }

  vector<int> a;
  vector<int> c;

  for (int i = 1; i + 1 < n; i++) {
    a.push_back(x[i]);
    int c1 = mul(norm(y[i] - y[i - 1]), minv(x[i] - x[i - 1]));
    int c2 = mul(norm(y[i + 1] - y[i]), minv(x[i + 1] - x[i]));
    sub(c2, c1);
    c.push_back(mul(c2, minv(2)));
  }

  for (int i = 0; i < 10 && i < n; i++) {
    int value = 0;
    for (int j = 0; j < (int)a.size(); j++) {
      add(value, mul(c[j], abs(x[i] - a[j])));
    }
    if (value != norm(y[i])) {
//      eprintf("at %d: f(%d) = %d != %d\n", i, x[i], value, y[i]);
      printf("No\n");
      return;
    }
  }
  printf("Yes\n");
  return;
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    solve(n + 1);
  }

}
