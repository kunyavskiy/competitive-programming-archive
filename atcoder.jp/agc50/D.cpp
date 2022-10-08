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

const int N = 41;
int dp[N][N][N][N][N];
string out(int x) {
  for (int i = 1; i <= 200; i++) {
    if (mul(i, x) <= 200) {
      return to_string(mul(i, x)) + "/" + to_string(i);
    }
  }
  return "???[" + to_string(x) + "]";
}

int calc(int left, int right, int done, int unknown, int remaining) {
  int &ans = dp[left][right][done][unknown][remaining];
  if (ans != -1) return ans;
  if (remaining == 0) return 0;
  if (done == left + right + 1) {
    return ans = calc(left, right, 0, unknown - 1, remaining);
  }
  ans = 0;
  assert(remaining <= unknown);
  int prob = mul(remaining, minv(unknown));
  int prob_not = 1; sub(prob_not, prob);
  if (left == 0) {
    add(ans, prob);
    if (prob_not) {
      add(ans, mul(prob_not, calc(right, 0, done + 1, unknown, remaining)));
    }
  } else {
    add(ans, mul(prob, calc(left - 1, right, done, unknown, remaining - 1)));
    if (prob_not) {
      add(ans, mul(prob_not, calc(left - 1, right + 1, done + 1, unknown, remaining)));
    }
  }
//  eprintf("calc(%d, %d, %d, %d, %d) = %s\n", left, right, done, unknown, remaining, out(ans).c_str());
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  eprintf("%ld\n", sizeof(dp) / 1024 / 1024);

  int n, k;
  while (scanf("%d%d", &n, &k) == 2) {
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < n; i++) {
//      eprintf("%s\n", out(calc(i, n - i - 1, 0, k, k)).c_str());
      printf("%d\n", calc(i, n - i - 1, 0, k, k));
    }
  }

  return 0;
}
