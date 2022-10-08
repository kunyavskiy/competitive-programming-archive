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

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  string s;
  while (cin >> s) {
    int n = s.size();
    vector<vector<vector<bool>>> can(n + 1, vector<vector<bool>>(n + 1, vector<bool>(n + 1)));
    can[0][0][0] = true;
    auto make_can = [&](int i, int j, int k) {
      if (i <= n && j <= n && k <= n) {
//        if (!can[i][j][k]) {
//          eprintf("   new can %d %d %d\n", i, j, k);
//        }
        can[i][j][k] = true;
      }
    };
    for (int i = 0; i <= n; i++) {
      for (int j = n; j >= 0; j--) {
        for (int k = n; k >= 0; k--) {
          if (!can[i][j][k]) continue;
//          eprintf("can %d %d %d\n", i, j, k);
          if (i + 2 <= n) make_can(i + 2, j + (s[i] == '0'), k + (s[i] == '1'));
          if (i + 2 <= n) make_can(i + 2, j + (s[i + 1] == '0'), k + (s[i + 1] == '1'));
          if (i + 2 <= n) make_can(i + 1, j, k);
          if (i + 1 <= n && j) make_can(i + 1, j + (s[i] == '0') - 1, k + (s[i] == '1'));
          if (i + 1 <= n && k) make_can(i + 1, j + (s[i] == '0'), k + (s[i] == '1') - 1);
          if (j && (n - i) + j + k >= 2) make_can(i, j - 1, k);
          if (k && (n - i) + j + k >= 2) make_can(i, j, k - 1);
        }
      }
    }

    reverse(s.begin(), s.end());

    vector<int> cnt0(n + 1);
    vector<int> cnt1(n + 1);
    for (int i = 0; i < n; i++) {
      cnt0[i + 1] = cnt0[i];
      cnt1[i + 1] = cnt1[i];
      if (s[i] == '0') {
        cnt0[i + 1]++;
      } else {
        cnt1[i + 1]++;
      }
    }

    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(n + 1, vector<int>(n + 1)));
    dp[0][0][0] = 1;
    int ans = 0;
    for (int i = 0; i <= n; i++) {
      for (int j = 0; i + j <= n; j++) {
        for (int k = 0; k <= i + j; k++) {
          if (dp[i][j][k] == 0) continue;
          if (i + j < n) {
            add(dp[i + 1][j][k + (s[k] == '0')], dp[i][j][k]);
            add(dp[i][j + 1][k + (s[k] == '1')], dp[i][j][k]);
          }

          assert(i >= cnt0[k]);
          assert(j >= cnt1[k]);
          /*std::function<string(int, int, int)> ex = [&](int i, int j, int k) -> string {
            if (i == 0 && j == 0) { assert(k == 0); return ""; }
            assert(dp[i][j][k]);
            if (i && dp[i-1][j][k] && s[k] == '1') return "0" + ex(i - 1, j, k);
            if (i && k && dp[i-1][j][k-1] && s[k-1] == '0') return "0" + ex(i - 1, j, k-1);
            if (j && dp[i][j-1][k] && s[k] == '0') return "1" + ex(i, j-1, k);
            if (j && k && dp[i][j-1][k-1] && s[k-1] == '1') return "1" + ex(i, j-1, k-1);
            assert(false);
          };*/
          if (can[n - k][i - cnt0[k]][j - cnt1[k]]) {
//            eprintf("%d %d %d -> %d [%s] [%d, %d, %d]\n", i, j, k, dp[i][j][k], ex(i, j, k).c_str(), n - k, i - cnt0[k], j - cnt1[k]);
            add(ans, dp[i][j][k]);
          } else {
//            eprintf("%d %d %d -> %d [%s] ! can [%d, %d, %d]\n", i, j, k, dp[i][j][k], ex(i, j, k).c_str(), n - k, i - cnt0[k], j - cnt1[k]);
          }
        }
      }
    }
    printf("%d\n", ans);
//    break;
  }

  return 0;
}
