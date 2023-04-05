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

const int INF = 1e9;

void test() {
  int N = 500;
  vector<int> dp(N + 1, INF);
  dp[0] = dp[1] = 0;

  /*for (int n = 2; n <= N; n++) {
    for (int a = 0; a <= n; a++) {
      for (int b = 0; a + 1 + b + 1 + a <= n; b++) {
        if (a + 1 + b + 1 + a != n) continue;

        int cur = 0;
        cur += a;
        cur += b + b;
        cur += a;
        cur += 1;
        cur += dp[a] + dp[b] + dp[a];
        dp[n] = min(dp[n], cur);
      }
    }
  }*/
  /*for (int n = 2; n <= N; n++) {
    for (int a = 0; a <= n; a++) {
      for (int b = 0; b <= n; b++) {
        int c = n - a - 1 - b - 1;
        if (c < 0) continue;

        int cur = 0;
        cur += a;
        cur += b + b;
        cur += c;
        cur += 1;
        cur += dp[a] + dp[b] + dp[c];
        dp[n] = min(dp[n], cur);
      }
    }
  }*/
//  for (int n = 2; n <= N; n++) {
//    for (int a = 0; a <= n; a++) {
//      for (int b = 0; b <= n; b++) {
//        int c = n - a - 1 - b - 1;
//        if (c < 0) continue;
//
//        int cur = 0;
//        cur += a;
//        cur += b + b;
//        cur += c + c;
//        cur += b + b;
//        cur += a;
//        cur += 6;
//        cur += dp[a] + dp[b] + dp[c] + dp[b] + dp[a];
//        dp[n] = min(dp[n], cur);
//      }
//    }
//  }
  /*for (int n = 2; n <= N; n++) {
    for (int a = 0; a <= n; a++) {
      for (int b = 0; a + b <= n; b++) {
        for (int c = 0; a + b + c <= n; c++) {
          int d = n - a - 1 - b - 1 - c - 1;
          if (d < 0) continue;
//          if (abs(a - d) > 1) continue;
//          if (abs(b - c) > 1) continue;
          //if (b != c) continue;

          {
            int cur = 0;
            cur += a;
            cur += b + b;
            cur += c + c;
            cur += d;
            cur += 3;
            cur += dp[a] + dp[b] + dp[c] + dp[d];
            dp[n] = min(dp[n], cur);
          }
          {
            int cur = 0;
            cur += a;
            cur += b + b;
            cur += c + c;
            cur += b + b;
            cur += d;
            cur += 6;
            cur += dp[a] + dp[b] + dp[c] + dp[b] + dp[d];
            dp[n] = min(dp[n], cur);
          }
        }
      }
    }
  }*/

  for (int n = 2; n <= N; n++) {
    db(n);
    function<void(vector<int>)> rec = [&](vector<int> vct) {
      if (vct.size() >= 4 && vct[2] < vct[1]) return;

      int cnt = (int)vct.size() - 1;
      int used = cnt;
      for (int x : vct) used += x;

      assert(used <= n);
      if (used == n && (vct.empty() || abs(vct[0] - vct.back()) <= 1)) {

        int cost = 0;
        cost += (cnt - 1) * (cnt - 2) / 2;
        for (int i = 0; i < (int)vct.size(); i++) {
          cost += dp[vct[i]];
          if (i == 0 || i + 1 == (int)vct.size()) {
            cost += vct[i];
          } else {
            cost += vct[i] * 2;
          }
        }
        dp[n] = min(dp[n], cost);
      }

      if (vct.size() >= 3) return;
      for (int x = 0; used + 1 + x <= n; x++) {
        auto nvct = vct;
        nvct.push_back(x);
        rec(nvct);
      }
    };
    rec(vector<int>());

    cout << n << " " << dp[n] << endl;
    if (dp[n] > 5 * n) {
      cout << "FAIL" << endl;
    }
  }
  cout << dp[23] << endl;
  cout << "OK" << endl;
  exit(0);
}

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
//  freopen("i.out", "w", stdout);
#endif

  test();

  return 0;
}
