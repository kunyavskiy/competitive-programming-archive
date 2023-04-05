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

int bin(int a, int n) {
  int res = 1;
  while (n) {
    if (n & 1) res = mul(a, res);
    a = mul(a, a);
    n >>= 1;
  }
  return res;
}

int inv(int x) {
  return bin(x, MOD - 2);
}

vector<int> find_berlekamp(vector<int> a) {
  vector<int> p({1}), r({1});
  int dif = 1;
  for (int i = 0; i < (int)a.size(); i++) {
    int u = 0;
    for (int j = 0; j < (int)p.size(); j++) {
      add(u, mul(p[j], a[i - j]));
    }
    if (u == 0) {
      r.insert(r.begin(), 0);
    } else {
      auto op = p;
      p.resize(max(p.size(), r.size() + 1));
      int idif = inv(dif);
      for (int j = 0; j < (int)r.size(); j++) {
        add(p[j + 1], MOD - mul(r[j], mul(idif, u)));
//        p[j + 1] -= r[j] * idif * u;
      }
      dif = u;
      r = op;
    }
  }
  assert(p[0] == 1);
  p.erase(p.begin());
  for (int &x : p) x = (MOD - x) % MOD;
  return p;
}


int solve(int n, int m) {
  if (n % 2 == 1 && m % 2 == 1) {
    return 1;
  }

  struct state {
    int i;
//    char a[15];
    int mask;
    char last;

    char get(int id) {
      return (mask >> (2 * id)) & 3;
    }

    void set(int it, int val) {
      mask = (mask & ~(3 << (2 * it))) | (val << (2 * it));
    }

    bool operator< (const state &s) const {
      if (i != s.i) return i < s.i;
      if (last != s.last) return last < s.last;
      return mask < s.mask;
//      for (int j = 0; j < 15; j++) if (a[j] != s.a[j]) return a[j] < s.a[j];
//      return 0;
    }
  };

  auto nok = [&](char a1, char a2, char a3, char a4) {
    vector<vector<int>> a(4, vector<int>(4));
    a[a1 / 2 + 0][a1 % 2 + 0] = 1;
    a[a2 / 2 + 0][a2 % 2 + 2] = 1;
    a[a3 / 2 + 2][a3 % 2 + 0] = 1;
    a[a4 / 2 + 2][a4 % 2 + 2] = 1;
    for (int i= 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (a[i][j] + a[i + 1][j] + a[i][j + 1] + a[i + 1][j + 1] == 0) {
          return false;
        }
      }
    }
    return true;
  };
//  vector<char> good(4 * 4 * 4 * 4);
  bool good[4][4][4][4];
  for (int a1 = 0; a1 < 4; a1++)
    for (int a2 = 0; a2 < 4; a2++)
      for (int a3 = 0; a3 < 4; a3++)
        for (int a4 = 0; a4 < 4; a4++) {
          good[a1][a2][a3][a4] = nok(a1, a2, a3, a4);
        }

  auto ok = [&](int a1, int a2, int a3, int a4) {
          return good[a1][a2][a3][a4];
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
    vector<char> a;
    a.push_back(3);
    for (int i = 0; i < n / 2; i++) {
      a.push_back(3);
    }
//    state start{1, a, 2};
    state start;
    start.i = 1;
    start.last = 2;
    for (int i = 0; i <= n / 2; i++) {
      start.set(i, a[i]);
    }

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

      if (ok(s.get(s.i - 1), s.last, s.get(s.i), i)) {
        state ns = s;
        ns.set(s.i - 1, s.last);
        if (s.i == 1) {
          ns.set(s.i - 1, 3);
        } else {
          int old = ns.get(s.i - 1);
//          if (old == 2) old = 0;
          ns.set(s.i - 1, old);
        }

        ns.last = i;
        ns.i++;
        if (ns.i == n / 2 + 1) {
          ns.set(s.i, ns.last);
          ns.i = 1;
          ns.last = 2;
        } else {
          int old = ns.get(s.i);
//          if (old == 1) old = 0;
          ns.set(s.i, old);
        }
        if (ns.i == 1 && n % 2 == 1 && ns.get(s.i) / 2 == 0) continue;


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
  TIMESTAMP(aaa);

  vector<char> good_finish(sz);
  for (int i = 0; i < sz; i++) {
    good_finish[i] = vct[i].i == 1;
    if (m % 2 == 1) {
      for (int j = 1; j <= n / 2; j++) {
        good_finish[i] &= vct[i].get(j) % 2 == 1;
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

  int sum = 0;
  for (int x : good_finish) sum += x;
  db(sum);

  /*ll S = 0;
  for (int i = 0; i < sz; i++) {
    if (!good_finish[i]) continue;
    queue<int> q;
    q.push(i);

    vector<char> vis(sz);
    int res = 0;
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (int to : e[v]) {
        if (vis[to]) continue;
        vis[to] = 1;
        if (vct[to].i == 1) {
          res++;
          continue;
        }
        q.push(to);
      }
    }
    S += res;
    db2(res, S);
  }
  exit(0);*/

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
  if (0) {
    for (int n = 2; n <= 10; n += 2) {
      for (int m = 2; m <= 10; m += 2) {
        cout << solve(n, m) << " ";
      }
      cout << endl;
    }
    return 0;
  }

  int n, m;
  while (scanf("%d%d%d", &n, &m, &MOD) == 3) {
    cout << solve(n, m) << endl;
  }

  return 0;
}
