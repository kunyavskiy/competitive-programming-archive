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

int main() {
#ifdef LOCAL
  freopen("p10.in", "r", stdin);
  freopen("p10.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    map<int, vector<pair<int, int>>> rv;
    vector<vector<int>> v(n, vector<int>(n));
    vector<tuple<int, int, int, int>> ans;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        scanf("%d", &v[i][j]);
        rv[v[i][j]].emplace_back(i, j);
      }
    }
    auto do_swap = [&](int x1, int y1, int x2, int y2) {
      int& val1 = v[x1][y1];
      int& val2 = v[x2][y2];
      assert(val1 != val2);
      ans.emplace_back(x1 + 1, y1 + 1, x2 + 1, y2 + 1);
      auto &m1 = rv[val1];
      auto it1 = find(m1.begin(), m1.end(), pair<int, int>{x1, y1});
      assert(it1 != m1.end());
      auto &m2 = rv[val2];
      auto it2 = find(m2.begin(), m2.end(), pair<int, int>{x2, y2});
      assert(it2 != m2.end());
      swap(val1, val2);
      swap(*it1, *it2);
    };

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i == j) continue;
        auto &m = rv[v[i][j]];
        if (m.size() == 1) continue;
        int nx = m[0].first ^ m[1].first ^ i;
        int ny = m[0].second ^ m[1].second ^ j;
        assert(v[nx][ny] == v[i][j]);
        if (tie(nx, ny) != tie(j, i)) {
          do_swap(nx, ny, j, i);
        }
        assert(v[i][j] == v[j][i]);
      }
    }

    vector<int> bad;
    for (int i = 0; i < n; i++) {
      auto &m = rv[v[i][i]];
      if (m.size() != 1) {
        bad.push_back(v[i][i]);
      }
    }
    sort(bad.begin(), bad.end());
    assert(bad.size() % 2 == 0);
    for (int i = 0; i < (int)bad.size(); i += 2) {
      assert(bad[i] == bad[i + 1]);
    }
    int pt = 0;

    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        auto &m = rv[v[i][j]];
        if (m.size() == 1) {
          int oval = v[j][i];
          assert(rv[oval].size() == 1);
          assert(pt < (int)bad.size());
          do_swap(i, j, rv[bad[pt]][0].first, rv[bad[pt]][0].second);
          do_swap(j, i, rv[bad[pt]][1].first, rv[bad[pt]][1].second);
          pt += 2;
        }
      }
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        assert(v[i][j] == v[j][i]);
      }
    }

    printf("%d\n", (int)ans.size());
    for (auto x : ans) {
      printf("%d %d %d %d\n", get<0>(x), get<1>(x), get<2>(x), get<3>(x));
    }
  }

  return 0;
}
