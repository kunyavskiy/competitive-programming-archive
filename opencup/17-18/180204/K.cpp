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

const int M = 53;

struct MatrixWithColumnSum {
  int m[M+1][M];

  MatrixWithColumnSum() {
    memset(m, 0, sizeof(m));
  }

  int get(int i, int j) {
    return m[i][j];
  }
  void set(int i, int j, int v) {
    sub(m[M][j], m[i][j]);
    m[i][j] = v;
    add(m[M][j], m[i][j]);
  }
  int get_sum(int j) {
    return m[M][j];
  }
};

struct MatrixWithColumnAdd {
  int m[M][M + 1];

  MatrixWithColumnAdd() {
    memset(m, 0, sizeof(m));
  }

  int get(int i, int j) {
    int val = m[i][j];
    add(val, m[i][M]);
    return val;
  }
  void set(int i, int j, int v) {
    m[i][j] = v;
    sub(m[i][j], m[i][M]);
  }
  void sub_row(int j, int v) {
    sub(m[j][M], v);
  }
};


const int MAXN = 1000100;

int prodLf[MAXN][M];
int prodRg[MAXN][M];

char s[MAXN];

int get_val(char c) {
  if ('a' <= c && c <= 'z') {
    return c - 'a' + 1;
  }
  return c - 'A' + 26 + 1;
}

const ll MOD2 = MOD * 1LL * MOD;

int solve(int x, int y) {
  //int z = 0;
  ll ans = 0;
  for (int j = 0; j < M; j++) {
    ans += prodLf[x][j] * 1LL * prodRg[y][j];
    if (ans >= MOD2) {
      ans -= MOD2;
    }
  }
  return ans % MOD;
}


int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

  scanf("%s", s);
  int n = strlen(s);
  {
    MatrixWithColumnSum lf;
    for (int i = 0; i < M; i++) {
      lf.set(i, i, 1);
    }

    for (int i = 0; i < M; i++) {
      prodLf[n][i] = lf.get_sum(i);
    }

    for (int i = n - 1; i >= 0; i--) {
      int val = get_val(s[i]);
      for (int j = 0; j < M; j++) {
        lf.set(val, j, lf.get_sum(j));
      }
      for (int j = 0; j < M; j++) {
        prodLf[i][j] = lf.get_sum(j);
      }
    }
  }

  TIMESTAMP(a);

  {
    MatrixWithColumnAdd rg;
    for (int i = 0; i < M; i++) {
      rg.set(i, i, 1);
    }

    for (int i = 0; i < M; i++) {
      prodRg[n][i] = rg.get(i, 0);
    }

    for (int i = n - 1; i >= 0; i--) {
      int val = get_val(s[i]);
      for (int j = 0; j < M; j++) {
        int t = rg.get(j, val);
        rg.sub_row(j, t);
        rg.set(j, val, t);
      }
      for (int j = 0; j < M; j++) {
        prodRg[i][j] = rg.get(j, 0);
      }
    }
  }

  TIMESTAMP(b);

  int Q, a, b, p, q, r;
  scanf("%d%d%d%d%d%d", &Q, &a, &b, &p, &q, &r);
  int z = 0;

  for (int i = 0; i < Q; i++) {
    int na = mul(p, a);
    add(na, mul(q, b));
    add(na, z);
    add(na, r);

    int nb = mul(p, b);
    add(nb, mul(q, a));
    add(nb, z);
    add(nb, r);

    a = na;
    b = nb;

    int x = min(a % n, b % n);
    int y = max(a % n, b % n) + 1;

    z = solve(x, y);
    assert(0 <= z && z < MOD);
  }

  printf("%d\n", z);
  return 0;
}
