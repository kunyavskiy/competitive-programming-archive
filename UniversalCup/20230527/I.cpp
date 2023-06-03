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

#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("Ofast,no-stack-protector")

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() { TIMESTAMPf("%s", what.data()); }
}__TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

const int MOD = 1000000007;

void add(int &a, int b) {
  if ((a += b) >= MOD)
    a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0)
    a += MOD;
}

int mul(int a, int b) { return (int)((a * 1LL * b) % MOD); }

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1)
      res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) { return mpow(x, MOD - 2); }

struct packed {
  long long x;
  int get(int pos) {
    return ((x >> (7 * pos)) & 0x7f) - 64;
  }
  packed set(int pos, int val) {
    return {(x & ~((0x7fL) << (7 * pos))) | ((val + 64L) << (7 * pos))};
  }
};

const int MAGIC = 400031;

struct HashTable {
  long long vals[MAGIC];
  int res[MAGIC];

  HashTable() {
    memset(vals, -1, sizeof(vals));
    memset(res, -1, sizeof(res));
  }

  int& operator[](long long value) {
    assert(value >= 0);
    int pos = value % MAGIC;
    while (vals[pos] != value && vals[pos] != -1) {
      pos++;
      if (pos == MAGIC) pos = 0;
    }
    if (vals[pos] == -1) {
      vals[pos] = value;
    }
    return res[pos];
  }
};

HashTable dp[51];
int ops;
int calc(int len, packed v) {
  if (len == 0) {
    if (v.get(0) >= 0)
      return 1;
    return 0;
  }
  if (v.get(0) < -len) {
    return 0;
  }
  int &ans = dp[len][v.x];
  if (ans != -1) {
    return ans;
  }
  if (ops++ % 1000000 == 0) {
    eprintf("%d\n", ops);
  }
  ans = 0;
  int lim = len + min(0, 2 * v.get(0));
  if (v.get(8) > lim) {
    for (int i = 8; i >= 0 && v.get(i) > lim; i--) {
      v = v.set(i, lim);
    }
    return ans = calc(len, v);
  }
  for (int i = 0; i < 9;) {
    int j = i;
    while (j <= 9 && v.get(j) == v.get(i)) {
      j++;
    }
    int t = calc(len - 1, v.set(i, v.get(i) - 1));
    add(ans, mul(j - i, t));
    i = j;
  }
  for (int i = 0; i < 9; i++) {
    v = v.set(i, v.get(i) + 1);
  }
  add(ans, calc(len - 1, v));
  return ans;
}

void solve() {
  char s[100];
  scanf("%s", s);
  int n = strlen(s);
  int ans = 0;
  for (int d = 1; d <= 9; d++) {
    int res = 0;
    vector<int> v(10);
    auto norm = [&](vector<int> v, int d) {
      packed val{0};
      int p = v[d];
      for (int i = 0; i < 10; i++) {
        v[i] = p - v[i];
        if (i > d) v[i]--;
      }
      v.erase(v.begin() + d);
      sort(v.begin(), v.end());
      for (int i = 0; i < 9; i++) {
        val = val.set(i, v[i]);
      }
      return val;
    };
    for (int j = 1; j < n; j++) {
      for (int dd = 1; dd <= 9; dd++) {
        v[dd]++;
        add(res, calc(j - 1, norm(v, d)));
        v[dd]--;
      }
      eprintf("j = %d, ops = %d\n", j, ops);
    }
    eprintf("ops = %d\n", ops);
    for (int j = 0; j < n; j++) {
      for (int dd = (j == 0 ? 1 : 0); dd < s[j] - '0'; dd++) {
        v[dd]++;
        add(res, calc(n - j - 1, norm(v, d)));
        v[dd]--;
      }
      v[s[j] - '0']++;
    }
    add(res, calc(0, norm(v, d)));
    eprintf("d = %d, res = %d\n", d, res);
    add(ans, mul(res, d));
  }
  printf("%d\n", ans);
}

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  TIMESTAMP("main");

  int t;
  scanf("%d", &t);
  while (t-->0) {
    solve();
  }

  eprintf("%d\n", (int)sizeof(dp) / 1024 / 1024);

  for (int i = 0; i <= 50; i++) {
    eprintf("%d : %d\n", i, MAGIC - (int)count(dp[i].vals, dp[i].vals + MAGIC, -1));
  }
  return 0;
}
