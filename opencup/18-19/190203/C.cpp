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
#define pb push_back
#define sz(a) (int)(a).size()
#define all(a) (a).begin() (a).end()
#define pw(x) (1ll << (x))


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

const int N = 100100;

int dp[N];

ll solve(string s) {
  int n = s.length();

  for (int i = 0; i < n; i++) s += '$';

  ll ans = 0;
  for (int l = 2; l <= n; l++) {
    memset(dp, 0, sizeof(dp));

    int sum = l;
    for (int i = n - l - 1; i >= 0; i--) {
      if (sum <= 1) {
        dp[i] = dp[i + l] + 1;
      } else dp[i] = 0;
      ans += dp[i];
      sum -= s[i + l - 1] != s[i + l + l - 1];
      if (i > 0) {
        sum += s[i - 1] != s[i + l - 1];
      }
    }
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  //freopen("c.out", "w", stdout);
#endif

  string s;
  while (cin >> s) {
    cout << solve(s) << endl;
  }

  return 0;
}
