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

const int P = 998244353;

int prod(int a, int b) {
  return (int)(ll(a) * b % P);
}

int sum(int a, int b) {
  if ((a += b) >= P) {
    a -= P;
  }
  return a;
}

const int N = 5010;
const int K = 21;
int dp[N][K][K];
int dp2[2][N][K];

bool solve() {
  int n, k;
  if (scanf("%d%d", &n, &k) != 2 || !n) {
    return false;
  }

  eprintf("%d %d\n", n, k);

  vector <int> turn(n);
  turn[0] = 0;
  vector<vector<int>> child(n);
  for (int i = 1; i < n; ++i) {
    int p;
    scanf("%d", &p);
    child[p].push_back(i);
    turn[i] = turn[p] ^ 1;
  }

  for (int v = n - 1; v >= 0; --v) {
    if (child[v].empty()) {
      for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
          dp[v][i][j] = 1;
        }
      }
      for (int max = 0; max < k; ++max) {
        dp2[0][v][max] = prod(max + 1, k);
        dp2[1][v][max] = prod(max + 1, k);
      }
      continue;
    }

    assert(child[v].size() == 2);
    int v1 = child[v][0];
    int v2 = child[v][1];

    for (int r1 = 0; r1 < k; ++r1) {
      for (int r2 = 0; r2 < k; ++r2) {
        int my_res = (turn[v] == 0 ? r1 : r2);
        int x1 = prod(dp[v1][r1][r2], dp2[turn[v]][v2][my_res]);
        int x2 = prod(dp[v2][r1][r2], dp2[turn[v]][v1][my_res]);
        dp[v][r1][r2] = sum(x1, x2);
        eprintf("dp[%d][%d][%d] = %d\n", v, r1, r2, dp[v][r1][r2]);
      }
    }

    for (int t = 0; t < 2; ++t) {
      for (int max = 0; max < k; ++max) {
        int &res = dp2[t][v][max];
        res = 0;
        if (t == turn[v]) {
          res = prod(2, prod(dp2[t][v1][max], dp2[t][v2][max]));
        } else {
          res = prod(dp2[t][v1][max], dp2[t][v2][k - 1]) + prod(dp2[t][v1][k - 1], dp2[t][v2][max]);
        }
        eprintf("dp2[%d][%d][%d] = %d\n", t, v, max, res);
      }
    }
  }

  int res = 0;
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < k; ++j) {
      res = sum(res, dp[0][i][j]);
    }
  }
  printf("%d\n", res);
  return true;
}

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

  while(solve());

  return 0;
}
