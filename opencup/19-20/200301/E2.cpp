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

int MOD = 1e9 + 7;

void add(int &x, int y) {
  x += y;
  if (x >= MOD) x -= MOD;
}

int mul(int x, int y) {
  return 1LL * x * y % MOD;
}

int solve(int n, int m) {
  if (n % 2 == 1 && m % 2 == 1) {
    return 1;
  }

  struct state {
    int i;
    vector<pair<int, int>> a;
    pair<int, int> last;

    bool operator< (const state &s) const {
      if (i != s.i) return i < s.i;
      if (last != s.last) return last < s.last;
      return a < s.a;
    }
  };

  auto ok = [&](pair<int, int> a1, pair<int, int> a2, pair<int, int> a3, pair<int, int> a4) {
    vector<vector<int>> a(4, vector<int>(4));
    a[a1.first + 0][a1.second + 0] = 1;
    a[a2.first + 0][a2.second + 2] = 1;
    a[a3.first + 2][a3.second + 0] = 1;
    a[a4.first + 2][a4.second + 2] = 1;
    for (int i= 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (a[i][j] + a[i + 1][j] + a[i][j + 1] + a[i + 1][j + 1] == 0) {
          return false;
        }
      }
    }
    return true;
  };

  vector<state> vct;
  map<state, int> mp;
  auto get_id = [&](const state &s) {
    if (!mp.count(s)) {
      int sz = vct.size();
      vct.push_back(s);
      mp[s] = sz;
    }
    return mp[s];
  };

  queue<state> q;
  {
    vector<pair<int, int>> a;
    a.push_back({1, 1});
    for (int i = 0; i < n / 2; i++) {
      a.push_back({1, 1});
    }
    state start{1, a, {1, 0}};
    int id = get_id(start);
    assert(id == 0);
    q.push(start);
  }

  vector<pair<int, int>> ed;
  while (!q.empty()) {
    auto s = q.front();
    q.pop();
    int cur_id = get_id(s);

    for (int i = 0; i < 4; i++) {
      int x = i / 2;
      int y = i % 2;

      if (ok(s.a[s.i - 1], s.last, s.a[s.i], {x, y})) {
        state ns = s;
        ns.a[s.i - 1] = s.last;
        if (s.i == 1) ns.a[s.i - 1] = {1, 1};

        ns.last = {x, y};
        ns.i++;
        if (ns.i == n / 2 + 1) {
          ns.a[s.i] = ns.last;
          ns.i = 1;
          ns.last = {1, 0};
        }
        if (ns.i == 1 && n % 2 == 1 && ns.a.back().first == 0) continue;

        if (!mp.count(ns)) {
          q.push(ns);
        }
        int new_id = get_id(ns);
        ed.push_back({cur_id, new_id});
      }
    }
  }


  int sz = vct.size();
  db2(sz, ed.size());
  /*for (auto o : vct) {
    db(o.i);
    db2(o.last.first, o.last.second);
    for (auto z : o.a) {
      db2(z.first, z.second);
    }
  }
  exit(0);*/

  vector<char> good_finish(sz);
  for (int i = 0; i < sz; i++) {
    good_finish[i] = vct[i].i == 1;
    if (m % 2 == 1) {
      for (int j = 1; j <= n / 2; j++) {
        good_finish[i] &= vct[i].a[j].second == 1;
      }
    }
  }

  vector<int> p(sz);
  for (int i = 0; i < sz; i++) p[i] = i;
  sort(p.begin(), p.end(), [&](int i, int j) {
    return vct[i].i < vct[j].i;
  });

  vector<vector<int>> e(sz);
  for (auto o : ed) e[o.first].push_back(o.second);
  for (int i = 0; i < sz; i++) {
    for (int j = 0; j < (int)e[i].size(); j++) {
      if (e[i][j] == i) {
        swap(e[i][j], e[i].back());
        break;
      }
    }
  }

  vector<int> dp(sz);
  dp[0] = 1;

  if (m / 2 == 1) {
    for (int i = 0; i < m / 2; i++) {
      vector<int> ndp(sz);
      for (auto id : p) {
        for (auto to : e[id]) {
          add(ndp[to], dp[id]);
        }
      }
      dp = ndp;
    }
  } else {
    for (int i = 0; i < m / 2; i++) {
      for (auto id : p) {
        for (auto to : e[id]) {
          add(dp[to], dp[id]);
        }
        dp[id] = 0;
      }
    }
  }
  int ans = 0;
  for (int i = 0; i < sz; i++) {
    add(ans, good_finish[i] * dp[i]);
  }

  return ans;
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
//  freopen("e.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d%d", &n, &m, &MOD) == 3) {
    cout << solve(n, m) << endl;
  }

  return 0;
}
