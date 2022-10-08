#include <iostream>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

  ~__timestamper() {
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

int dp[510][510];

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  static char A[10010], B[10010];

  while (scanf("%s%s", A, B) == 2) {
    int a, b;
    a = b = 0;
    for (int i = 0; A[i]; i++) {
      if (A[i] == '1' && B[i] == '1') {
        a++;
      } else if (A[i] == '1') {
        b++;
      }
    }

    dp[0][0] = 1;

    for (int j = 0; j <= b; j++) {
      for (int i = 0; i <= a; i++) {
        for (int k = 0; k <= a; k++) {
          if (i == 0 && j == 0 && k == 0) continue;
          int &res = dp[i][k];
          if (j) {
            res = mul(res, j * j); // b->b
            // b->a, b-> c is fail
          } else {
            res = 0;
          }
          if (i) {
            add(res, mul(dp[i - 1][k], i * (1 + j + k + k)));     // a->self, a -> b, a-> c, c-> a
            if (i >= 2) {
              add(res, mul(dp[i - 2][k + 1], i * (i - 1))); // a->other a
            }
          }
          if (k) {
            add(res, mul(dp[i][k - 1], k * k)); // c->c
            // c->b is fail
          }

        }
      }
    }

    printf("%d\n", dp[a][0]);
  }

  return 0;
}
