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

const int MOD = 1000000007;

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
      vector<vector<int>> color(n, vector<int>(n, -1));
      vector<vector<int>> order(n, vector<int>(n, -1));
      for (int i = 0; i < n * (n - 1) / 2; i++) {
          int a, b;
          scanf("%d%d", &a, &b);
          --a, --b;
          order[a][b] = order[b][a] = i;
      }
      int ans = 1;

      auto dfs = [&](int i, int j, int c, auto dfs) {
          if (color[i][j] == c) return;
          if (color[i][j] == -1) {
              color[i][j] = c;
          } else {
              ans = 0;
              return;
          }
          dfs(j, i, 1 - c, dfs);
          for (int k = 0; k < n; k++) {
              if (k == i || k == j) continue;
              if (order[i][j] > order[i][k] && order[i][j] > order[j][k]) continue;
              if (order[i][k] > order[j][k])
                  dfs(j, k, 1 - c, dfs);
              else
                  dfs(k, i, 1 - c, dfs);
          }
      };

      for (int i = 0; i < n; i++) {
          for (int j = 0; j < n; j++) {
              if (i == j) continue;
              if (color[i][j] == -1) {
                  ans = (ans * 2) % MOD;
                  dfs(i, j, 0, dfs);
              }
          }
      }
      printf("%d\n", ans);
  }

  return 0;
}
