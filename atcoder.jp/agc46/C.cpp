#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

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

int dp[310][310][310];

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  string s; int k;
  while (cin >> s >> k) {
    s += '0';
    vector<int> cnts;
    {
      int cnt = 0;
      for (char c : s) {
        if (c == '1') {
          cnt++;
        } else {
          cnts.push_back(cnt);
          cnt = 0;
        }
      }
    }
    int total = accumulate(cnts.begin(), cnts.end(), 0);
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;
    int prefix_tot = 0;
    for (int pos = 0; pos < (int)cnts.size(); pos++) {
      prefix_tot += cnts[pos];
      for (int cnt = 0; cnt <= total; cnt++) {
        for (int cost = 0; cost <= cnt; cost++) {
          for (int next = max(0, prefix_tot - cnt); cnt + next <= total; next++) {
            int add_cost = max(0, next - cnts[pos]);
            add(dp[pos + 1][cnt + next][cost + add_cost], dp[pos][cnt][cost]);
          }
        }
      }
    }
    int ans = 0;
    for (int cost = 0; cost <= total && cost <= k; cost++) {
      add(ans, dp[cnts.size()][total][cost]);
    }
    printf("%d\n", ans);
  }

  return 0;
}
