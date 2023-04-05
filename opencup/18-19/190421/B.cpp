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
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


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

int MOD = 1000000007;

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

const int MAXN = 110;

int cnk[MAXN][MAXN];
int f[MAXN];

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n;
  while (scanf("%d%d", &n, &MOD) == 2) {
    if (n == 1) {
      printf("%d\n", 1 % MOD);
      continue;
    }
    if (n == 2) {
      printf("%d\n%d\n", 2 % MOD, 2 % MOD);
      continue;
    }
    if (n == 3) {
      printf("%d\n%d\n%d\n", 6 % MOD, 6 % MOD, 6 % MOD);
      continue;
    }
    f[0] = 1;
    for (int i = 1; i < MAXN; i++) {
      f[i] = mul(f[i - 1], i);
    }

#ifdef LOCAL2
    vector<int> stupid_ans(n + 1);
    {
      vector<int> r(n);
      for (int i = 0; i < n; i++) {
        r[i] = i + 1;
      }
      do {
        int ans = 0;
        for (int i = 0; i < n; i++) {
          bool ok = true;
          for (int j = 0; j < i; j++) {
            if (__gcd(r[i], r[j]) != 1) {
              ok = false;
            }
          }
          if (!ok) break;
          ans = i + 1;
        }
        stupid_ans[ans]++;
      } while (next_permutation(r.begin(), r.end()));
      while (stupid_ans.back() == 0) stupid_ans.pop_back();
      for (int & x : stupid_ans) x %= MOD;
    }
#endif

    memset(cnk, 0, sizeof(cnk));
    cnk[0][0] = 1;
    for (int i = 0; i < MAXN; i++) {
      for (int j = 0; j < MAXN; j++) {
        if (i) add(cnk[i][j], cnk[i - 1][j]);
        if (i && j) add(cnk[i][j], cnk[i - 1][j - 1]);
      }
    }

    vector<int> primes;
    for (int i = 2; i <= n; i++) {
      bool ok = true;
      for (int j = 2; j * j <= i; j++) {
        if (i % j == 0) {
          ok = false;
        }
      }
      if (ok) {
        primes.push_back(i);
      }
    }

    int small_mask = 0;
    int small_cnt = 0;
    for (int i = 0; i < (int) primes.size(); i++) {
      if (2 * primes[i] <= n) {
        small_mask |= (1 << i);
        small_cnt++;
      }
    }

    vector<int> mask;
    int big = 0;
    for (int i = 1; i <= n; i++) {
      int ps = 0;
      for (int j = 0; j < (int) primes.size(); j++) {
        if (i % primes[j] == 0) {
          ps |= (1 << j);
        }
      }
      if (ps & small_mask) {
        mask.push_back(ps);
      } else {
        big++;
      }
    }

    vector<int> dp(small_mask + 1);

    vector<int> cnt(primes.size() + 2);
    dp[0] = 1;

    for (int i = 0; i <= small_cnt; i++) {
      vector<int> ndp(small_mask + 1);
      for (int j = 0; j <= small_mask; j++) {
        int bad = 0;
        for (int x : mask) {
          if (x & j) {
            bad++;
          } else {
            add(ndp[x | j], dp[j]);
          }
        }
        add(cnt[i], mul(dp[j], bad - i));
      }
      dp = ndp;
    }

    vector<int> ncnt(primes.size() + 2);

    for (int i = 0; i < (int)ncnt.size(); i++) {
      for (int j = 0; j <= i; j++) {
        int cur = cnt[j];
        cur = mul(cur, cnk[big][i - j]);
        cur = mul(cur, cnk[i][j]);
        cur = mul(cur, f[i - j]);
        add(ncnt[i], cur);
      }
      ncnt[i] = mul(ncnt[i], f[n - i - 1]);
    }
#ifdef LOCAL2
    for (int i = 1; i < (int)ncnt.size(); i++) {
      eprintf("%d %d\n", ncnt[i], stupid_ans[i]);
    }
    assert(stupid_ans == ncnt);
#endif

    for (int i = (int)ncnt.size() - 2; i >= 0; i--) {
      add(ncnt[i], ncnt[i + 1]);
    }


    for (int i = 1; i < (int)ncnt.size(); i++) {
      printf("%d\n", ncnt[i] % MOD);
    }
#ifdef LOCAL
    printf("====\n");
#endif
  }

  return 0;
}
