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

const int N = 110;

char a[N][N];
char b[N][N];

using bigint = ll;
void print(bigint x) {
  printf("%lld\n", x);
}

__int128_t cycle[N][N];
bool different[N][N];
int cycle_pw[2 * N];
int changed[2 * N];
__int128_t current[N][N];

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int n, m, q;
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 0; i < n; i++) {
    scanf("%s", a[i]);
  }
  for (int i = 0; i < n; i++) {
    scanf("%s", b[i]);
  }
  current[0][0] = 1;
  for (int s = 0; s < n + m; s++) {
    changed[s] = -1;
    for (int i = 0; i < n; i++) {
      int j = s - i;
      if (j < 0 || j >= m) continue;
      cycle[i][j] = current[i][j];
      if (current[i][j] & 1) {
        changed[s] = j;
      }
    }
    if (changed[s] == -1) {
      cycle_pw[s] = cycle_pw[s - 1];
    } else {
      cycle_pw[s] = (s == 0 ? 0 : cycle_pw[s - 1]) + 1;
      for (int i = 0; i < n; i++) {
        int j = s - i;
        if (j < 0 || j >= m) continue;
        current[i][j] *= 2;
      }
    }
    for (int i = 0; i < n; i++) {
      int j = s - i;
      if (j < 0 || j >= m) continue;
      if (a[i + 1][j] != '.') current[i + 1][j] += current[i][j] / 2;
      if (a[i][j + 1] != '.') current[i][j + 1] += current[i][j] / 2;
    }
  }
  auto ok = [&](int s) {
    for (int i = max(0, s - m + 1), up = min(n, s + 1); i < up; i++) {
      int j = s - i;
      if ((current[i][j] & 1) != (a[i][j] != b[i][j])) {
//        eprintf("%d is not ok at(%d,%d)\n", s, i, j);
        return false;
      }
    }
//    eprintf("%d is ok\n", s);
    return true;
  };

  auto solve = [&]() -> vector<int> {
    vector<int> pws;
    current[0][0] = 0;
    memset(current, 0, sizeof(current));
    for (int s = 0; s < n + m; s++) {
      if (!ok(s)) {
        pws.push_back(cycle_pw[s] - 1);
        for (int i = max(0, s - m + 1), up = min(n, s + 1); i < up; i++) {
          int j = s - i;
          current[i][j] += cycle[i][j];
        }
        if (!ok(s)) return {-1};
      }
      /*for (int i = 0; i < n; i++) {
        int j = s + 1 - i;
        if (j < 0 || j >= m) continue;
        current[i][j] = 0;
      }*/
      for (int i = max(0, s - m + 1), up = min(n, s + 1); i < up; i++) {
        int j = s - i;
        if (a[i+1][j] != '.') current[i + 1][j] += (current[i][j] + (a[i][j] == 'v')) / 2;
        if (a[i][j+1] != '.') current[i][j + 1] += (current[i][j] + (a[i][j] == '>')) / 2;
      }
    }
    return pws;
  };
  auto solve_and_print = [&] {
    auto pws = solve();
    if (!pws.empty()) {
      if (pws.back() == -1) {
        printf("-1\n");
        return;
      }
      if (pws.back() == cycle_pw[n + m - 1] - 1) {
        vector<int> npws;
        for (int i = cycle_pw[n + m - 1] - 1; i >= 0; i--) {
          if (!pws.empty() && pws.back() == i) {
            pws.pop_back();
          } else {
            npws.push_back(i);
          }
        }
        npws.push_back(0);
        while (npws.size() >= 2 && npws[npws.size() - 1] == npws[npws.size() - 2]) {
          npws.pop_back();
          npws.back()++;
        }
        reverse(npws.begin(), npws.end());
        pws = npws;
      }
    }

    bigint ans = 0;
    bigint x = 1;
    int pt = 0;
    pws.push_back(-1);
    for (int i = 0; i < cycle_pw[n+m-1]; i++) {
      if (i == pws[pt]) {
        pt++;
        ans = ans + x;
      }
      x = x + x;
    }
    print(x);
  };

  solve_and_print();
  for (int i = 0; i < q; i++) {
    int t, x, y;
    scanf("%d%d%d", &t, &x, &y);
    --x, --y;
    if (t == 1) {
      a[x][y] ^= 'v' ^ '>';
    } else {
      b[x][y] ^= 'v' ^ '>';
    }
    solve_and_print();
  }

  return 0;
}
