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

vector<vector<int>> dp1, dp2h, dp2v, dp;
int a, b;

int solve(int c, int d);

int solve2v(int c, int d) {
  int &ans = dp2v[c][d];
  if (ans != -1) return ans;
  if (c == a || d == b) return 0;
  ans = mul(solve2v(c - 1, d), d - 1);
  add(ans, solve(c - 1, d));
  return ans;
}

int solve2h(int c, int d) {
  int &ans = dp2h[c][d];
  if (ans != -1) return ans;
  if (c == a || d == b) return 0;
  ans = mul(solve2h(c, d - 1), c - 1);
  add(ans, solve(c, d - 1));
  return ans;
}


int solve1(int c, int d) {
  int &ans = dp1[c][d];
  if (ans != -1) return ans;
  if (c == a || d == b) return 0;
  ans = solve(c - 1, d - 1);
  ans = mul(ans, c - 1);
  ans = mul(ans, d - 1);
  return ans;
}

int solve(int c, int d) {
  int &ans = dp[c][d];
  if (ans != -1) return ans;
  if (c == a && d == b) return 1;
  if (c == a) return ans = mul(solve(c, d - 1), c);
  if (d == b) return ans = mul(solve(c - 1, d), d);
  ans = solve1(c, d);
  add(ans, solve2h(c, d));
  add(ans, solve2v(c, d));
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int c, d;
  while (scanf("%d%d%d%d", &a, &b, &c, &d) == 4) {
    dp = vector<vector<int>>(c + 1, vector<int>(d + 1, -1));
    dp1 = vector<vector<int>>(c + 1, vector<int>(d + 1, -1));
    dp2h = vector<vector<int>>(c + 1, vector<int>(d + 1, -1));
    dp2v = vector<vector<int>>(c + 1, vector<int>(d + 1, -1));

    printf("%d\n", solve(c, d));
  }

  return 0;
}
