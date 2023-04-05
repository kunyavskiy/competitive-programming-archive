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

const int MOD1 = 1000000007;
int MOD2;

struct HV {
  int f, s;

  bool operator<(const HV &rhs) const {
    if (f != rhs.f)
      return f < rhs.f;
    return s < rhs.s;
  }

  bool operator==(const HV &x) const {
    return f == x.f && s == x.s;
  }
};

int addm(int a, int b, int MOD) {
  if ((a += b) >= MOD) a -= MOD;
  return a;
}


HV operator+(const HV &a, const HV &b) {
  return {addm(a.f, b.f, MOD1), addm(a.s, b.s, MOD2)};
}

HV operator-(const HV &a, const HV &b) {
  return {addm(a.f, MOD1 - b.f, MOD1), addm(a.s, MOD2 - b.s, MOD2)};
}

HV operator*(const HV &a, const HV &b) {
  return {(int) ((a.f * 1LL * b.f) % MOD1), (int) ((a.s * 1LL * b.s) % MOD2)};
}


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

const int BITS = 20;
const int ALL = ((1 << BITS) - 1);

void transform(HV *a) {
  for (int i = 0; i < BITS; i++) {
    for (int j = 0; j < (1 << BITS); j++) {
      if (j & (1 << i)) {
        a[j] = a[j] + a[j ^ (1 << i)];
      }
    }
  }
}

HV v[1 << BITS];
HV t[1 << BITS];
int sign[1 << BITS];

HV evallast(HV *a) {
  HV res = {0, 0};
  for (int i = 0; i < (1 << BITS); i++) {
    if (sign[i ^ ALL] == 1) {
      res = res + a[i];
    } else {
      res = res - a[i];
    }
  }
  return res;
}

int cnk[50][50];

int ways(int k) {
  cnk[0][0] = 1;
  for (int i = 0; i < 50; i++) {
    for (int j = 0; j < 50; j++) {
      if (i) add(cnk[i][j], cnk[i - 1][j]);
      if (i && j) add(cnk[i][j], cnk[i - 1][j - 1]);
    }
  }


  vector<int> dp(k + 1);
  dp[0] = 0;
  dp[1] = 1;
  for (int i = 2; i <= k; i++) {
    for (int j = 1; j < i; j++) {
      add(dp[i], mul(cnk[i - 2][j - 1], mul(dp[j], dp[i - j])));
    }
  }

  eprintf("dp[%d] = %d\n", k, dp[k]);
  return dp[k];
}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  MOD2 = 1e9 + rand() % 1000000;
  while (true) {
    bool ok = true;
    for (int i = 2; i * i <= MOD2; i++) {
      if (MOD2 % i == 0) {
        ok = false;
        break;
      }
    }
    if (ok) break;
    MOD2++;
  }


  sign[0] = 1;
  for (int i = 1; i < (1 << BITS); i++) {
    sign[i] = - sign[i & (i - 1)];
  }

  int n;
  scanf("%d", &n);

  int all = 0;

  for (int i = 0; i < n; i++) {
    int a;
    scanf("%d", &a);
    all |= a ^ ALL;
    v[a ^ ALL] = v[a ^ ALL] + HV{1, 1};
  }

  if (all != ALL) {
    printf("-1\n");
    return 0;
  }

  transform(v);
  memcpy(t, v, sizeof(v));

  for (int k = 1;; k++) {
    HV lst = evallast(t);
    if (lst.f || lst.s) {
      printf("%d %d\n", k - 1, mul(ways(k), lst.f));
      return 0;
    }
    for (int i = 0; i < (1 << BITS); i++) {
      t[i] = t[i] * v[i];
    }
  }
}
