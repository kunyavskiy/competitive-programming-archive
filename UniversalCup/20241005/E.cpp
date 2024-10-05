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
#include <numeric>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x)                                                           \
  eprintf("[" #x "] Time : %.3lf s.\n",                                        \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...)                                                     \
  eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__,                            \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() { TIMESTAMPf("%s", what.data()); }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

const pair<int,int> dirs[4] = {{0, 1}, {0,-1}, {1,0}, {-1,0}};

void solve(int n) {
  if (n >= 5) {
    printf("-1\n");
    return;
  }
  printf(R"(33
-1 0 0 0 0 1
2 0 1 0 1 1
0 -1 -1 -1 -1 0
1 -1 2 -1 2 0
-2 0 -1 0 -1 1
3 0 2 0 2 1
-1 1 0 1 0 2
2 1 1 1 1 2
0 -2 -1 -2 -1 -1
1 -2 2 -2 2 -1
-2 -1 -1 -1 -1 0
3 -1 2 -1 2 0
-3 -1 -3 0 -2 0
4 -1 4 0 3 0
-2 0 -1 0 -1 1
3 0 2 0 2 1
-4 -1 -4 0 -3 0
5 -1 5 0 4 0
-3 -2 -2 -2 -2 -1
4 -2 3 -2 3 -1
-5 -2 -5 -1 -4 -1
6 -2 6 -1 5 -1
-4 -2 -4 -1 -3 -1
5 -2 5 -1 4 -1
-3 -1 -2 -1 -2 0
4 -1 3 -1 3 0
-3 0 -2 0 -2 1
4 0 3 0 3 1
-2 1 -1 1 -1 2
3 1 2 1 2 2
-1 2 0 2 0 3
2 2 1 2 1 3
1 3 0 3 0 4
)");

  return;
  multiset<pair<int, int>> cur;
  for (int x = -10; x <= 10; x++) {
    for (int y = -10; y <= 0; y++) {
      cur.emplace(x, y);
    }
  }
  int target_x = 0;
  int target_y = n;
  vector<tuple<int, int, int, int, int, int>> ans;

  auto dist = [&](int a, int b) {
    return abs(a - target_x) + abs(b - target_y);
  };

  while (true) {
    tuple<int, int, int, int, int, int> best_move;
    int best_score = 10000;

    auto update = [&](int a, int b, int c, int d, int e, int f) {
      if (cur.find({e, f}) != cur.end()) return;
      //int d1 = dist(a, b);
      //int d2 = dist(c, d);
      int d3 = dist(e, f);
      if (/*d3 < d1 && d3 < d2 && */d3 < best_score) {
        best_score = d3;
        best_move = {a,b,c,d,e,f};
      }
    };

    /*for (auto [x, y] : cur) {
      for (auto [dx, dy] : dirs) {
        int cx = x + dx;
        int cy = y + dy;
        if (!cur.count({cx, cy}))
          continue;
        int nx1 = cx + dy;
        int ny1 = cy - dx;
        update(x, y, cx, cy, nx1, ny1);
        int nx2 = cx - dy;
        int ny2 = cy + dx;
        update(x, y, cx, cy, nx2, ny2);
      }
    }*/
    vector<string> s(25, string(25, '.'));
    for (auto [x, y] : cur) {
      s[x + 12][y + 12] = '#';
    }
    s[target_x+12][target_y+12] = '$';
    //printf("best_score = %d (new = %d, %d)\n", best_score, e, f);
    for (auto x : s) {
      printf("%s\n", x.data());
    }
    printf("\n");
    fflush(stdout);

    int aa, bb,cc,dd,ee,ff;
    assert(scanf("%d%d%d%d%d%d", &aa, &bb, &cc, &dd, &ee, &ff) == 6);
    update(aa,bb,cc,dd,ee,ff);
    assert(best_score != 10000);
    ans.push_back(best_move);
    auto [a,b,c,d,e,f] = best_move;
//    eprintf("%d %d %d %d %d %d\n", a, b, c, d, e, f);
//    eprintf("%d %d %d %d %d %d\n", ~a, b, ~c, d, ~e, f);
    assert(cur.find({a, b}) != cur.end());
    assert(cur.find({c, d}) != cur.end());
    assert(cur.find({e, f}) == cur.end());
    assert(abs(c - a) + abs(d - b) == 1);
    assert(abs(e - c) + abs(f - d) == 1);
    cur.erase({a,b});
    cur.erase({c,d});
    cur.insert({e,f});
    if (e == target_x && f == target_y)
      break;

  }


  printf("%d\n", (int)ans.size());
  for (auto [a,b,c,d,e,f] : ans) {
    printf("%d %d %d %d %d %d\n", a, b, c, d, e, f);
    printf("%d %d %d %d %d %d\n", (-a+1), b, (-c+1), d, (-e+1), f);
  }
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    int n;
    scanf("%d", &n);
    solve(n);
  }

  return 0;
}
