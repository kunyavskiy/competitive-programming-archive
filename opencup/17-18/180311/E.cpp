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

typedef vector<vector<int>> Matrix;

Matrix mul(const Matrix& a, const Matrix &b) {
  int n = a.size();
  int inner = a[0].size();
  assert(a[0].size() == b.size());
  int m = b.size();
  Matrix res = vector<vector<int>>(n, vector<int>(m));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      for (int k = 0; k < inner; k++) {
        add(res[i][j], mul(a[i][k], b[k][j]));
      }
    }
  }
  return res;
}

bool is_null(const Matrix& a) {
  for (const auto & x : a) {
    for (const auto &y : x) {
      if (y != 0) {
        return 0;
      }
    }
  }
  return 1;
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  Matrix a;
  a = vector<vector<int>>(n, vector<int>(n));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &a[i][j]);
    }
  }

  Matrix b = vector<vector<int>>(1, vector<int>(n));

  for (int i = 0; i < n; i++) {
    b[0][i] = abs(rand()) % MOD;
  }

  for (int i = 1; i <= n + 5; i++) {
    Matrix r = mul(b, a);
    if (is_null(r)) {
      printf("%d\n", i);
      return 0;
    }
    b = r;
  }

  printf("Infinity\n");
  return 0;
}
