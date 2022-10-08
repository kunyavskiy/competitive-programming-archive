#include <algorithm>
#include <fstream>
#include <iostream>
#include <tuple>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

using namespace std;

typedef long long ll;
typedef long double ld;

void PreCalc() {
}

struct item {
  int dx;
  int dy;
  int j;
  bool operator<(const item &rhs) const {
    return std::tie(dx, dy) < std::tie(rhs.dx, rhs.dy);
  }
};


void solve() {
  int n;
  scanf("%d", &n);
  vector<int> x(n), y(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &x[i], &y[i]);
  }

  vector<vector<item>> dir(n, vector<item>(n));
  vector<pair<int, int>> dirs;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j) {
        int dx = x[i] - x[j];
        int dy = y[i] - y[j];
        if (dx < 0 || (dx == 0 && dy < 0)) {
          dx *= -1;
          dy *= -1;
        }
        int g = __gcd(dx, abs(dy));
        dx /= g;
        dy /= g;
        dir[i][j] = item{dx, dy, j};
        dirs.emplace_back(dx, dy);
      }
    }
  }

  sort(dirs.begin(), dirs.end());
  dirs.erase(unique(dirs.begin(), dirs.end()), dirs.end());

  for (int i = 0; i < n; i++) {
    sort(dir[i].begin(), dir[i].end());
  }

  int res = 1;
  for (auto d : dirs) {
    vector<bool> used(n);
    int ans = 0;
    int odds = 0, ones = 0;
    for (int i = 0; i < n; i++) {
      if (!used[i]) {
        int sz = 1;
        used[i] = true;
        auto lit = equal_range(dir[i].begin(), dir[i].end(), item{d.first, d.second, -1});
        sz += lit.second - lit.first;
        for_each(lit.first, lit.second, [&](item a) { used[a.j] = true; });
        if (sz == 1) {
          ones++;
        } else {
          if (sz % 2 == 1) {
            odds++;
          }
          ans += sz;
        }
      }
    }
    if (odds % 2 == 0) {
      ans += min(ones, 2);
    } else {
      ans += min(ones, 1);
    }
    res = max(res, ans);
  }
  printf("%d\n", res);
}


int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  PreCalc();
  TIMESTAMP(PreCalc);

  char buf[1000];
  int testNum;
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d", &testNum);

  for (int testId = 1; testId <= testNum; testId++) {
    if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
      TIMESTAMPf("Test %d", testId);
    printf("Case #%d: ", testId);
    solve();
  }

  TIMESTAMP(end);
  return 0;
}
