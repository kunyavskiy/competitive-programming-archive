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

const int K = 4;

struct Matrix {
  int a[K][K];

  int* operator[](int id) {
    return a[id];
  }
  const int* operator[](int id) const {
    return a[id];
  }

  Matrix(int v) {
    memset(a, 0, sizeof(a));
    for (int i = 0; i < K; i++) {
      a[i][i] = v;
    }
  }
};

Matrix operator*(const Matrix& a, const Matrix & b) {
  Matrix res(0);
  for (int i = 0; i < K; i++)
    for (int j = 0; j < K; j++)
      for (int k = 0; k < K; k++) {
        res[i][j] = (int) ((res[i][j] + a[i][k] * 1LL * b[k][j]) % MOD);
      }
  return res;
}

Matrix operator^(Matrix a, int b) {
  Matrix r(1);
  while (b) {
    if (b & 1) r = r * a;
    a = a * a;
    b >>= 1;
  }
  return r;
}

struct Vector {
  int a[K];

  Vector() { memset(a, 0, sizeof(a));}

  int& operator[](int id) {
    return a[id];
  }
  const int& operator[](int id) const {
    return a[id];
  }
};

Vector operator*(const Matrix& a, const Vector& b) {
  Vector res;
  for (int i = 0; i < K; i++) {
    for (int j = 0; j < K; j++) {
      res[i] = (res[i] + a[i][j] * 1LL * b[j]) % MOD;
    }
  }
  return res;
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  Matrix F(0);



  F[1][0] = 1;
  F[1][1] = 1;

  F[2][0] = 1;
  F[2][1] = 1;
  F[2][2] = 1;

  F[3][0] = 1;
  F[3][2] = 2;
  F[3][1] = 1;
  F[3][3] = 1;


  F[0][0] = 1;
  F[0][2] = 2;
  F[0][1] = 1;
  F[0][3] = 1;

  int n;
  scanf("%d", &n);

  Vector cur;
  cur[0] = 1;
  cur[1] = 0;
  cur[2] = 0;
  cur[3] = 0;

  int m;
  scanf("%d", &m);

  int last = 0;

  for (int i = 0; i < m; i++) {
    int x;
    scanf("%d", &x);
    cur = (F ^ (x - last)) * cur;
    cur[0] = 0;
    last = x;
  }

  cur = (F ^ (n - last)) * cur;

  printf("%d\n", cur[0]);
  return 0;
}