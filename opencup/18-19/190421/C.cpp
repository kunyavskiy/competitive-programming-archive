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

int ok(int x, int y) {
  if (x % 3 == 0 && y % 3 == 0) return 1;
  if (x % 2 == 1 && y % 3 == 1) return 1;
  if (x % 4 == 3 && y % 3 == 2) return 1;
  if (x % 4 == 0 && (y % 3 == 2 || y % 3 == 1)) return 1;
  return 0;
}

vector<pair<int, int>> neib = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {0, 0}};

vector<string> brute(vector<string> a) {
  int n = a.size();
  int m = a[0].size();

  auto ok = [&](int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < m;
  };

  vector<pair<int, int>> vct;
  vector<vector<int>> can(n, vector<int>(m));

  for (int i = 1; i < n - 1; i++) {
    for (int j = 1; j < m - 1; j++) {
      can[i][j] = 1;
      for (auto o : neib) {
        int nx = i + o.first;
        int ny = j + o.second;
        can[i][j] &= a[nx][ny] == '.';
      }
    }
  }

  function<bool()> rec = [&]() {
//    for (auto s : a) db(s);
    bool can_move = 0;
    for (auto p : vct) {
      int x = p.first, y = p.second;
      for (int t = 0; t < 4; t++) {
        int dx = neib[t].first;
        int dy = neib[t].second;

        int rx = dx == 0 ? 1 : 0;
        int ry = dy == 0 ? 1 : 0;

        int x1 = x + dx - rx, y1 = y + dy - ry;
        int x2 = x + dx + dx, y2 = y + dy + dy;
        int x3 = x + dx + rx, y3 = y + dy + ry;

        vector<pair<int, int>> brd({{x1, y1}, {x2, y2}, {x3, y3}});

        if (ok(x1, y1) && a[x1][y1] == '.' &&
            ok(x2, y2) && a[x2][y2] == '.' &&
            ok(x3, y3) && a[x3][y3] == '.') {
          bool flag = 0;
          for (auto b : brd) {
            for (auto d : neib) {
              pair<int, int> c = make_pair(b.first + d.first, b.second + d.second);
              int dist = abs(c.first - x) + abs(c.second - y);
              if (dist > 2 && ok(c.first, c.second) && can[c.first][c.second]) {
                flag = 1;
                break;
              }
            }
            if (flag) break;
          }
          if (!flag) return false;
          can_move = 1;
        }
      }
    }

    vector<pair<int, int>> cand;
    int x = -1, y = -1;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (can[i][j]) {
          cand.push_back({i, j});
        }
        if (x != -1) break;
      }
      if (x != -1) break;
    }
    if (!cand.empty()) {
      auto o = cand[0];
      x = o.first;
      y = o.second;
    }
    if (x == -1 && y == -1) {
      return !can_move;
    }
    assert(can[x][y]);

//    db2(x, y);
    {
      auto ocan = can;
      vct.push_back({x, y});
      for (auto d1 : neib) {
        for (auto d2 : neib) {
          int nx = x + d1.first + d2.first;
          int ny = y + d1.second + d2.second;
          if (ok(nx, ny)) {
            can[nx][ny] = 0;
          }
        }
      }
      a[x][y] = '+';
      a[x + 1][y] = a[x - 1][y] = '|';
      a[x][y + 1] = a[x][y - 1] = '-';
      if (rec()) {
        return true;
      }
      for (auto d : neib) {
        int nx = x + d.first, ny = y + d.second;
        a[nx][ny] = '.';
      }

      can = ocan;
      vct.pop_back();
    }
    can[x][y] = 0;
    auto res = rec();
    can[x][y] = 1;
    return res;
  };

  bool f = rec();
  assert(f);

  return a;
}

vector<string> solve(int n, int m) {
  const int N = 16;
  const int K = 2;
  if (n >= N) {
    auto a = solve(n - K, m);
    for (int i = 0; i < K; i++) a.push_back(string(m, '.'));
    return brute(a);
  }
  if (m >= N) {
    auto a = solve(n, m - K);
    for (int i = 0; i < n; i++) a[i] += string(K, '.');
    return brute(a);
  }
  return brute(vector<string>(n, string(m, '.')));
  /*vector<string> a(n, string(m, '.'));

  auto ok = [&](int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < m;
  };

  vector<pair<int, int>> vct;
  vector<vector<char>> can(n, vector<char>(m));

  for (int i = 1; i < n - 1; i++)
    for (int j = 1; j < m - 1; j++)
      can[i][j] = 1;

  function<bool()> rec = [&]() {
//    for (auto s : a) db(s);
    bool can_move = 0;
    for (auto p : vct) {
      int x = p.first, y = p.second;
      for (int t = 0; t < 4; t++) {
        int dx = neib[t].first;
        int dy = neib[t].second;

        int rx = dx == 0 ? 1 : 0;
        int ry = dy == 0 ? 1 : 0;

        int x1 = x + dx - rx, y1 = y + dy - ry;
        int x2 = x + dx + dx, y2 = y + dy + dy;
        int x3 = x + dx + rx, y3 = y + dy + ry;

        vector<pair<int, int>> brd({{x1, y1}, {x2, y2}, {x3, y3}});

        if (ok(x1, y1) && a[x1][y1] == '.' &&
            ok(x2, y2) && a[x2][y2] == '.' &&
            ok(x3, y3) && a[x3][y3] == '.') {
          bool flag = 0;
          for (auto b : brd) {
            for (auto d : neib) {
              pair<int, int> c = make_pair(b.first + d.first, b.second + d.second);
              int dist = abs(c.first - x) + abs(c.second - y);
              if (dist > 2 && ok(c.first, c.second) && can[c.first][c.second]) {
                flag = 1;
                break;
              }
            }
            if (flag) break;
          }
          if (!flag) return false;
          can_move = 1;
        }
      }
    }

    vector<pair<int, int>> cand;
    int x = -1, y = -1;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (can[i][j]) {
          cand.push_back({i, j});
//          x = i;
//          y = j;
        }
        if (x != -1) break;
      }
      if (x != -1) break;
    }
    if (!cand.empty()) {
//      sort(cand.begin(), cand.end(), [&](pair<int, int> p1, pair<int, int> p2) {
//        if (p1.first % 3 != p2.first % 3) {
//          return p1.first % 3 < p2.first % 3;
//        }
//        if (p1.second % 3 != p2.second % 3) {
//          return p1.second % 3 < p2.second % 3;
//        }
//        return p1 < p2;
//      });
      auto o = cand[0];
      x = o.first;
      y = o.second;
    }
    if (x == -1 && y == -1) {
      return !can_move;
    }
    assert(can[x][y]);

//    db2(x, y);
    {
      auto ocan = can;
      vct.push_back({x, y});
      for (auto d1 : neib) {
        for (auto d2 : neib) {
          int nx = x + d1.first + d2.first;
          int ny = y + d1.second + d2.second;
          if (ok(nx, ny)) {
            can[nx][ny] = 0;
          }
        }
      }
      a[x][y] = '+';
      a[x + 1][y] = a[x - 1][y] = '|';
      a[x][y + 1] = a[x][y - 1] = '-';
      if (rec()) {
        return true;
      }
      for (auto d : neib) {
        int nx = x + d.first, ny = y + d.second;
        a[nx][ny] = '.';
      }

      can = ocan;
      vct.pop_back();
    }
    can[x][y] = 0;
    auto res = rec();
    can[x][y] = 1;
    return res;
  };

  bool f = rec();
  assert(f);

  return a;*/
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
//  freopen("c.out", "w", stdout);
#endif

//  int n = 100, m = 100;
//  int sum = 0;
//  vector<vector<int>> c(n, vector<int>(m));
//  for (int i = 10; i <= n; i++) {
//    for (int j = 10; j <= m; j++) {
//      bool f = 0;
//      if (ok(i, j) || ok(j, i)) f = 1;
//      cout << f;
//
//      sum += f;
//      if (!f) {
//        cout << i << " " << j << endl;
//        return 0;
//      }
//    }
//    cout << endl;
//  }
//
//  cout << sum * 1.0 / (n * m) << " covered" << endl;
//  return 0;

  for (int n = 10; n <= 100; n++) {
    for (int m = 10; m <= 100; m++) {
      db2(n, m);
      auto a = solve(n, m);
//      for (auto s : a) db(s);
    }
  }

  int n, m;
  while (cin >> n >> m) {
    auto a = solve(n ,m);
    for (auto s : a) cout << s << endl;
  }

  return 0;
}
