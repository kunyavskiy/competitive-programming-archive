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

const int MAXN = 3010;

int dp[MAXN];
int ndp[MAXN];

int l[2 * MAXN];
int r[2 * MAXN];

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);

  dp[0] = 1;

  for (int i = 0; i <= 2 * m; i++) {
    memset(ndp, 0, sizeof(ndp));
    for (int j = 0; j <= n; j++) {
      add(l[i], dp[j]);
    }

    eprintf("l[%d] = %d\n", i, l[i]);

    if (i % 2 == 1) {
      for (int j = 0; j <= n; j++) {
        add(ndp[j], dp[j]);
        if (j) add(ndp[j - 1], dp[j]);
      }
    } else {
      for (int j = 0; j <= n; j++) {
        add(ndp[j], dp[j]);
        if (j < n) add(ndp[j + 1], dp[j]);
      }
    }


    memcpy(dp, ndp, sizeof(dp));
  }

  memset(dp, 0, sizeof(dp));
  dp[0] = 1;

  for (int i = 0; i <= 2 * m; i++) {
    memset(ndp, 0, sizeof(ndp));
    for (int j = 0; j <= n; j++) {
      add(r[i], dp[j]);
    }
    eprintf("r[%d] = %d\n", i, r[i]);

    if (i % 2 == 1) {
      for (int j = 0; j <= n; j++) {
        if (j) add(ndp[j], dp[j]);
        if (j > 1) add(ndp[j - 1], dp[j]);
      }
    } else {
      for (int j = 0; j <= n; j++) {
        if (j) add(ndp[j], dp[j]);
        if (j < n) add(ndp[j + 1], dp[j]);
      }
    }

    memcpy(dp, ndp, sizeof(dp));
  }

  vector<int> atans(2 * m);

  for (int i = 0; i < (1 << (2 * m)); i++) {
    int bal = 0;

    int min_bal = 0;
    int max_bal = 0;
    int min_bal_last = 0;

    string s;

    for (int j = 0; j < (2 * m); j++) {
      if (i & (1 << j)) {
        if (j % 2) {
          bal++;
        } else {
          bal--;
        }
      }
      if (j % 2) {
        s += "BR"[(i >> j) & 1];
      } else {
        s += "RB"[(i >> j) & 1];
      }
      min_bal = min(min_bal, bal);
      if (min_bal == bal) {
        min_bal_last = j;
      }
      max_bal = max(max_bal, bal);
    }
    if (max_bal - min_bal <= n) {
      printf("%s\n", s.c_str());
      atans[min_bal_last]++;
    }
  }


  int ans = 0;
  for (int i = 1; i <= 2 * m; i += 2) {
    eprintf("i = %d, l * r = %d, at = %d\n", i, l[i] * r[2 * m - i], atans[i]);
    add(ans, (l[i] * 1LL * r[2 * m - i]) % MOD);
  }

  printf("%d\n", ans);
  return 0;
}
