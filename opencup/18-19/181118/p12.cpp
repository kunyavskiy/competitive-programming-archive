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
#include <bits/stdc++.h>

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

char buf[1111111];

const int SIGMA = 27;

ll fast(vector<string> a) {
  int n = a.size();
  vector<vector<int>> e(n, vector<int>(SIGMA));
  for (int i = 0; i < n; i++) {
    for (int st = 0; st < SIGMA; st++) {
      int cur = st;
      for (char cc : a[i]) {
        int c = cc - 'a';
        if (cur == SIGMA - 1) {
          cur = c;
        } else {
          if (cur == c) {
            cur = SIGMA - 1;
          }
        }
      }
      e[i][st] = cur;
    }
  }
  vector<vector<ll>> dp(1 << n, vector<ll>(SIGMA));
  dp[0][SIGMA - 1] = 1;
  for (int mask = 0; mask < (1 << n); mask++) {
    for (int c = 0; c < SIGMA; c++) {
      for (int nw = 0; nw < n; nw++) if (!(mask & (1 << nw))) {
        dp[mask | (1 << nw)][e[nw][c]] += dp[mask][c];
      }
    }
  }
  ll ans = 0;
  for (int i = 0; i < SIGMA - 1; i++) ans += dp[(1 << n) - 1][i];
  return ans;
}

ll cnt(string s) {
  int n = s.length();
  vector<ll> last(SIGMA, 0);
  vector<ll> dp(n + 1);
  dp[0] = 1;
  for (int i = 0; i < n; i++) {
    dp[i + 1] = 2 * dp[i] - last[s[i] - 'a'];
    last[s[i] - 'a'] = dp[i];
  }
  return dp[n];
}

ll slow(vector<string> a) {
  int n = a.size();
  vector<int> p(n);
  iota(p.begin(), p.end(), 0);
  ll ans = 0;
  do {
    string t = "";
    for (int i = 0; i < n; i++) t += a[p[i]];
    ans += cnt(t) % 2 == 0;
  } while (next_permutation(p.begin(), p.end()));
  return ans;
}

void stress() {
  for (int it = 0;; it++) {
    db(it);
    srand(it);

    int n = rand() % 7 + 1;
    vector<string> a(n);
    for (int i = 0; i < n; i++) {
      int len = rand() % 10 + 1;
      for (int j = 0; j < len; j++) {
        a[i] += (char)('a' + rand() % 3);
      }
    }
    auto ans1 = fast(a);
    auto ans2 = slow(a);
    assert(ans1 == ans2);
  }
}

int main() {
#ifdef LOCAL
  freopen("p12.in", "r", stdin);
  //freopen("p12.out", "w", stdout);
#endif
 // stress();

  int n;
  while (scanf("%d", &n) == 1) {
    vector<string> a(n);
    for (int i = 0; i < n; i++) {
      scanf("%s", buf);
      a[i] = buf;
    }

    printf("%lld\n", fast(a));
  }

  return 0;
}
