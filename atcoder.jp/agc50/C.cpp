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
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  const int MAXK = 21;
  vector<int> cnt;
  cnt.push_back(0);
  for (int i = 0; i < MAXK; i++) {
    cnt.push_back(cnt.back() * 2+1);
  }
  eprintf("%d\n", cnt.back());

  string s;
  while (cin >> s) {
    vector<int> prevb(s.size() + 1, -1);
    for (int i = 0; i < (int)s.size(); i++) {
      if (s[i] == 'B') {
        prevb[i + 1] = i;
      } else {
        prevb[i + 1] = prevb[i];
      }
    }
    vector<vector<int>> dp(s.size() + 1, vector<int>(MAXK, 0));
    dp[s.size()][0] = 1;
    for (int i = (int) s.size() - 1; i >= 0; i--) {
      if (s[i] == 'S' || s[i] == '?') {
        for (int k = 0; k < MAXK; k++) {
          add(dp[i][k], dp[i + 1][k]);
        }
      }
      if (s[i] == 'B' || s[i] == '?') {
        for (int k = 0; k < MAXK; k++) {
          int should_be_s = max(0, i - cnt[k] - 1);
          if (prevb[i] >= should_be_s) {
            break;
          }
          add(dp[should_be_s][k + 1], dp[i + 1][k]);
        }
      }
    }
    int ans = 1;
    for (char c : s) {
      if (c == '?') {
        ans = mul(ans, 2);
      }
    }
#ifdef LOCAL
    int should_be_ans = -1;
    if (ans == 1) {
      int lf = numeric_limits<int>::max() / 2;
      int rg = numeric_limits<int>::max() / 2;
      for (char c : s) {
        if (c == 'S') {
          if (lf < rg) lf++, rg--;
          else if (lf > rg) lf--, rg++;
        } else {
          if (lf < rg) rg = 0;
          else lf = 0;
        }
      }
      if (lf == 0 && rg == 0) {
        should_be_ans = 1;
      } else {
        should_be_ans = 0;
      }
    }
#endif
    for (int i = 0; i < MAXK; i++) {
      sub(ans, dp[0][i]);
    }
#ifdef LOCAL
    if (should_be_ans != -1) {
      eprintf("%d %d\n", ans, should_be_ans);
      assert(ans == should_be_ans);
    }
#endif
    printf("%d\n", ans);
  }

  return 0;
}
