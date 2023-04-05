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

const int N = 1e3;
int dp[N][N][2];
int best[N][N][2];
int opt[N][N][2];

int cost(int x, int y) {
  if (x == -1) x = 0;
  int res = 0;
  for (int i = 0; i < 5; i++) {
    res += x % 10 != y % 10;
    x /= 10;
    y /= 10;
  }
  return res;
}

const int INF = 1e9;

void init() {
  for (int i = 0; i < N; i++) {
    dp[i][i][0] = dp[i][i][1] = 0;
  }
  for (int len = 1; len < N; len++) {
    for (int l = 0; l + len < N; l++) {
      int r = l + len;
      for (int f = 0; f < 2; f++) {
        dp[l][r][f] = INF;
        for (int x = l; x <= r; x++) {
          int mx = 0;
          if (x > l) mx = max(mx, dp[l][x - 1][1]);
          if (x < r) mx = max(mx, dp[x + 1][r][0]);
          int cs = cost(f == 0 ? l - 1 : r + 1, x);
          mx += cs + 1;
          if (dp[l][r][f] > mx || (dp[l][r][f] == mx && best[l][r][f] > cs)) {
            dp[l][r][f] = mx;
            best[l][r][f] = cs;
            opt[l][r][f] = x;
          }
        }
      }
    }
  }
  for (int l = 1; l < N; l++) {
    for (int r = l; r < N; r++) {
      for (int f = 0; f < 2; f++) {
        if (r + N / 10 < N - 1) {
          if (dp[l][r][f] != dp[l + N / 10][r + N / 10][f]) {
            db3(l, r, f);
            db2(dp[l][r][f], dp[l + N / 10][r + N / 10][f]);
            assert(dp[l][r][f] == dp[l + N / 10][r + N / 10][f]);
          }
        }
      }
    }
  }
  cout << dp[0][N - 1][0] << endl;
//  int mx = 0;
//  for (int l = 0; l < N; l++) {
//    for (int r = l; r < N; r++) {
//      for (int f = 0; f < 2; f++) {
//        if (l % 10 == 0 && f == 0) continue;
//        if (r % 10 == 9 && f == 1) continue;
//        if (r - l <= 10) continue;
//
//        mx = max(mx, best[l][r][f]);
//        if (best[l][r][f] == 3) {
//          db3(l, r, f);
//          db(opt[l][r][f]);
//        }
//      }
//    }
//  }
//  db(mx);
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
//  freopen("f.out", "w", stdout);
#endif

  init();

  int T;
  scanf("%d", &T);
  while (T--) {
    int l, r;
    scanf("%d%d", &l, &r);
  }

  return 0;
}
