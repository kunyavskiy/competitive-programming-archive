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

int dp[100][100];
char s[100];

int solve_dp(int l, int r) {
  assert((r - l) % 2 == 1);
  if (r - l == 1) {
    return dp[l][r] = (s[l] == '1');
  }
  if (dp[l][r] != -1) return dp[l][r];
  for (int k = l + 1; k <= r; k += 2) {
    for (int t = k + 1; t <= r; t += 2) {
      int cnt = solve_dp(l, k) + solve_dp(k, t) + solve_dp(t, r);
      if (cnt >= 2) {
        return dp[l][r] = 1;
      }
    }
  }
  return dp[l][r] = 0;
}

const int N = 7;

int nxt[N][2] = {
    {1, 2}, // ""
    {3, 0}, // 0
    {4, 5}, // 1
    {1, 1}, // 00
    {6, 2}, // 10
    {5, 5}, // 11
    {4, 4}, //100
};

const char *val[N] = {
    "",
    "0",
    "1",
    "00",
    "10",
    "11",
    "100",
};

int solve_greedy() {
  int state = 0;
  for (int i = 0; s[i]; i++) {
    state = nxt[state][s[i] - '0'];
  }
  return state == 2 || state == 5;
  string cur = "";
  for (int i = 0; s[i]; i++) {
    int old = state;
    state = nxt[old][s[i] - '0'];
    cur += s[i];
    if (cur == "000" || cur == "001") cur = "0";
    else if (cur == "01") cur = "";
    else if (cur == "1000" || cur == "1001") cur = "10";
    else if (cur == "101") cur = "1";
    else if (cur == "11") return 1;
    eprintf("old = %d, c = %c, state = %d, cur = %s, val[state] = %s\n", old, s[i], state, cur.c_str(), val[state]);
    assert(val[state] == cur);
  }
  return cur == "1";
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  /*
  while (true) {
    int n = 2 * (rand() % 25) + 1;
    int p = rand();
    for (int i = 0; i < n; i++) {
      if (rand() < p) {
        s[i] = '0';
      } else {
        s[i] = '1';
      }
    }
    eprintf("try %s\n", s);
    s[n] = 0;
    memset(dp, -1, sizeof(dp));
    int r1 = solve_dp(0, n);
    eprintf("r1 = %d\n", r1);
    int r2 = solve_greedy();
    eprintf("%s %d %d\n", s, r1, r2);
    if (r1 != r2) {
      break;
    }
  }*/

  string s;
  while (cin >> s) {
    vector<int> dp(N);
    dp[0] = 1;
    for (int i = 0; i < (int)s.size(); i++) {
      vector<int> ndp(N);
      if (s[i] == '0' || s[i] == '?') {
        for (int j = 0; j < N; j++) {
          add(ndp[nxt[j][0]], dp[j]);
        }
      }
      if (s[i] == '1' || s[i] == '?') {
        for (int j = 0; j < N; j++) {
          add(ndp[nxt[j][1]], dp[j]);
        }
      }
      dp = ndp;
    }
    int ans = 0;
    add(ans, dp[2]);
    add(ans, dp[5]);
    printf("%d\n", ans);
  }

  return 0;
}
