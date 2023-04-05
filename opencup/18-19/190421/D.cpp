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

const int dx[2] = {0, 1};
const int dy[2] = {1, 0};

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
//  freopen("d.out", "w", stdout);
#endif

  function<pair<int, int>(vector<string>&)> rec = [&](vector<string> &a) {
    int cnt = 0;
    int x = -1, y = -1;
    for (int i = 0; i < (int)a.size(); i++) {
      for (int j = 0; j < (int)a[0].length(); j++) {
        if (a[i][j] == '.') {
          x = i;
          y = j;
          break;
        }
      }
      if (x != -1) break;
    }
    if (x == -1 && y == -1) {
      return make_pair(0, 1);
    }
    cnt++;

    for (int k = 0; k < 2; k++) {
      int nx = x + dx[k];
      int ny = y + dy[k];
      if (nx < (int)a.size() && ny < (int)a[0].size() && a[nx][ny] == '.') {
        a[x][y] = a[nx][ny] = 'x';
        auto o = rec(a);
        a[x][y] = a[nx][ny] = '.';
        cnt += o.first;
        if (o.second) {
          return make_pair(cnt, 1);
        }
      }
    }
    return make_pair(cnt, 0);
  };

  auto gen = [&](int k) {
    int n, m;
    vector<string> a;
    if (k == 0) {
      n = 1, m = 2;
      a = vector<string>(n, string(m, '.'));
    } else {
      n = 4;
      m = 3 + 2 * k;
      a = vector<string>(n, string(m, 'x'));
      for (int i = 0; i < n; i++) a[i][0] = '.';
      for (int j = 0; j < m; j++) a[0][j] = '.';
      for (int j = 2; j < m - 1; j++) a[1][j] = '.';
    }
//    for (string s : a) db(s);
    auto o = rec(a);

//    db2(o.first, o.second);
    assert(o.second == 1);
    return make_pair(a, o.first);
  };

  vector<pair<vector<string>, int>> vct;
  for (int k = 0; (int)vct.size() < 15; k++) {
    auto o = gen(k);
    if (o.second > 1e7) break;
    vct.push_back(o);
  }

//  auto check = [&](int x) {
//    int res = 0;
//    while (x > 1) {
//      int k = (int)vct.size() - 1;
//      while (vct[k].second > x) k--;
//      if (k == 0) break;
//      res++;
//      x -= vct[k].second;
//    }
//    return res;
//  };
//
//  int mx = 0;
//  for (int i = 1; i <= 1e7; i++) mx = max(mx, check(i));
//  db(mx);
//  return 0;

  auto solve = [&](int k) {
    int n = 100;

    vector<string> a(n, string(n, 'x'));
    vector<pair<int, int>> pos;
    for (int i = 0; i < n / 5; i++) for (int j = 0; j < 1; j++) pos.push_back({i * 5, j * 33});
    for (int i = 0; i < 20; i++) pos.push_back({n - 1, n / 5 + 3 * i});

    function<void(int, int)> go = [&](int cpos, int k) {
      if (k == 0) {
        return;
      }
      int x = pos[cpos].first;
      int y = pos[cpos].second;
      int t = (int)vct.size() - 1;
      while (vct[t].second > k) t--;
      k -= vct[t].second;
      for (int i = 0; i < (int)vct[t].first.size(); i++) {
        for (int j = 0; j < (int)vct[t].first[0].length(); j++) {
          a[x + i][y + j] = vct[t].first[i][j];
        }
      }
      go(cpos + 1, k);
    };
    go(0, k - 1);
//    auto o = rec(a);
//    assert(o.second == 1);
//    db2(o.first, k - 1);
//    for (auto s : a) db(s);
//    assert(o.first == k - 1);
    return a;
  };

  int k;
  while (cin >> k) {
    auto a = solve(k);
    int n = a.size();
    int m = a[0].length();
    cout << n << " " << m << endl;
    for (auto s : a) cout << s << endl;
  }

  return 0;
}
