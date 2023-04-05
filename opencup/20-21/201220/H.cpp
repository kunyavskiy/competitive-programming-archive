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

#define div div_aaaa
#define long long long

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

void addAns1(vector<int> &ans, int a, int b) {
  add(ans[0], (long) b * b % MOD);
  add(ans[1], (long) 2 * b * a % MOD);
  add(ans[2], (long) a * a % MOD);
}

void addAns(vector<int>& ans, int a, int b, int p, int q, int r) {
  add(ans[2], (long) p * a % MOD * a % MOD);

  add(ans[1], (long) q * a % MOD);
  add(ans[1], (long) 2 * p * a % MOD * b % MOD);

  add(ans[0], (long) p * b % MOD * b % MOD);
  add(ans[0], (long) q * b % MOD);
  add(ans[0], r);
}

vector<vector<int>> ans;
vector<int> a;
vector<int> b;
vector<int> div;

long getAns() {
  int div = (2 - a[2] - a[3]);
  while (div < 0) {
    div += MOD;
  }
  div = minv(div);
  long x = (int) ((long) (b[2] + b[3]) * div % MOD);
  vector<int>& ans = ::ans[1];
  long result = ans[2];
  result = (result * x + ans[1]) % MOD;
  result = (result * x + ans[0]) % MOD;
  return result;
}

void update(int i) {
  int left = 2 * i, right = 2 * i + 1;
  if (a[i] == 0) {
    int div = (3 - a[left] - a[right]);
    while (div < 0) {
      div += MOD;
    }
    div = minv(div);
    a[i] = div;
  }
  b[i] = (int) ((long) (b[left] + b[right]) * a[i] % MOD);

  vector<int>& curAns = ans[i];
  fill(curAns.begin(), curAns.end(), 0);
  addAns(curAns, a[left], b[left], ans[left][2], ans[left][1], ans[left][0]);
  addAns(curAns, a[right], b[right], ans[right][2], ans[right][1], ans[right][0]);

  addAns1(curAns, a[left] + MOD - 1, b[left]);
  addAns1(curAns, a[right] + MOD - 1, b[right]);
}


void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  int N = (1 << n);
  a = vector<int>(N);
  b = vector<int>(N);
  div = vector<int>(N, -1);
  ans = vector<vector<int>>(N, vector<int>(3));
  for (int i = N / 2; i < N; i++) {
    a[i] = 0;
    scanf("%d", &b[i]);
    b[i] %= MOD;
  }

  for (int i = N / 2 - 1; i >= 1; i--) {
    update(i);
  }

  printf("%lld\n", getAns());
  for (int i = 0; i < m; i++) {
    int pos;
    scanf("%d", &pos);
    scanf("%d", &b[pos]);
    b[pos] %= MOD;
    pos /= 2;
    while (pos > 0) {
      update(pos);
      pos /= 2;
    }
    printf("%lld\n", getAns());
  }
}


int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  solve();

  return 0;
}
