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

char s[19][19];
vector<short> dp[19][19];
vector<bool> p[19][19];

int main() {
#ifdef LOCAL
  freopen("p2.in", "r", stdin);
  freopen("p2.out", "w", stdout);
#endif

  int w, h;
  scanf("%d%d", &h, &w);
  for (int i = 0; i < h; i++) {
    scanf("%s", s[i]);
  }

  for (int i = 0; i <= w; i++) {
    for (int j = 0; j < h; j++) {
      dp[i][j].resize(1 << h, -1);
      p[i][j].resize(1 << h, false);
    }
  }
  dp[0][0][0] = 0;
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      vector<short> &next = (j == h - 1) ? dp[i + 1][0] : dp[i][j + 1];
      vector<bool> &nextp = (j == h - 1) ? p[i + 1][0] : p[i][j + 1];
      for (int mask = 0; mask < (1 << h); mask++) {
        if (dp[i][j][mask] == -1) continue;
        {
          bool can_dot = false;
          if (i == 0 && j == 0) can_dot = true;
          int prev = 0;
          if (i != 0 && (mask & (1 << j))) prev++;
          if (j != 0 && (mask & (1 << (j - 1)))) prev++;
          if (prev == 1) can_dot = true;
          can_dot &= s[j][i] != 'X';
          if (can_dot && next[mask | (1 << j)] < dp[i][j][mask] + 1) {
            next[mask | (1 << j)] = dp[i][j][mask] + 1;
            nextp[mask | (1 << j)] = (mask >> j) & 1;
          }
        }
        {
          bool can_x = true;
          if (i == 0 && j == 0) can_x = false;
          if (i != 0 && j != h - 1) {
            if (mask & (1 << j)) {
              if (!(mask & (1 << (j + 1)))) {
                can_x = false;
              }
            }
          }
          can_x &= s[j][i] != '.';
          if (can_x && next[mask & ~(1 << j)] < dp[i][j][mask]) {
            next[mask & ~(1 << j)] = dp[i][j][mask];
            nextp[mask & ~(1 << j)] = (mask >> j) & 1;
          }
        }
      }
    }
  }

  vector<string> res(h, string(w, '?'));

  int mask = max_element(dp[w][0].begin(), dp[w][0].end()) - dp[w][0].begin();

  printf("%d\n", dp[w][0][mask]);
  if (dp[w][0][mask] != -1) {
    for (int i = w - 1; i >= 0; i--) {
      for (int j = h - 1; j >= 0; j--) {
        res[j][i] = ((mask >> j) & 1) ? '.' : 'X';
        vector<bool> &nextp = (j == h - 1) ? p[i + 1][0] : p[i][j + 1];
        mask = (mask & ~(1 << j)) | (nextp[mask] << j);
      }
    }
    for (int i = 0; i < h; i++) {
      printf("%s\n", res[i].c_str());
    }
  }




  return 0;
}
