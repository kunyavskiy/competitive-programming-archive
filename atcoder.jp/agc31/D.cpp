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
#include <numeric>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


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

using perm = vector<int>;

perm one(int n) {
  perm p = perm(n);
  for (int i = 0; i < n; i++) {
    p[i] = i;
  }
  return p;
}

perm operator*(const perm& a, const perm& b) {
  perm res(a.size());
  for (int i = 0; i < (int)a.size(); i++) {
    res[i] = b[a[i]];
  }
  return res;
}

perm operator^(perm a, int k) {
  perm res = one(a.size());
  while (k) {
    if (k & 1) res = res * a;
    a = a * a;
    k /= 2;
  }
  return res;
}

perm operator~(const perm& a) {
  perm res(a.size());
  for (int i = 0; i < (int)a.size(); i++) {
    assert(0 <= a[i] && a[i] < (int)a.size());
    res[a[i]] = i;
  }
  return res;
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n, k;
  while (scanf("%d%d", &n, &k) == 2) {
    perm p(n), q(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &p[i]);
      --p[i];
    }
    for (int i = 0; i < n; i++) {
      scanf("%d", &q[i]);
      --q[i];
    }

    perm lm, rm;

    int deg = (k - 12) / 6;
    if (deg > 0) {
      perm ip = ~p;
      perm iq = ~q;
      lm = (iq * p * q * ip);
      rm = (p * iq * ip * q);
      lm = lm ^ deg;
      rm = rm ^ deg;
      k -= deg * 6;
    } else {
      lm = rm = one(n);
    }

    for (int i = 2; i < k; i++) {
      perm t = (~p) * q;
      p = q;
      q = t;
    }

    perm ans;
    if (k == 1) {
      ans = p;
    } else {
      ans = q;
    }

    ans = lm * ans * rm;

    for (int i : ans) {
      printf("%d ", i + 1);
    }
    printf("\n");
  }

  return 0;
}
