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

string fast(vector<pair<pair<int, int>, int>> ed, int k) {
  int n = ed.size() + 1;
  vector<vector<pair<int, int>>> e(n);
  for (auto o : ed) {
    e[o.first.first].push_back({o.first.second, o.second});
    e[o.first.second].push_back({o.first.first, o.second});
  }

  struct item {
    ll sum;
    int cnt;

    item() {
      sum = 0;
      cnt = 0;
    }
    item(ll _sum, int _cnt) : sum(_sum), cnt(_cnt) {}

    bool operator< (const item &it) const {
      //return sum < it.sum;
      if (sum != it.sum) return sum < it.sum;
      return cnt < it.cnt;
    }

    item operator+ (const item &it) const {
      return item(sum + it.sum, cnt + it.cnt);
    }
  };

  function<item(ll)> solve = [&](ll lambda) {
    // root: not used, used
    function<pair<item, item>(int, int)> dfs = [&](int v, int pr) {
      pair<item, item> res;
      for (auto o : e[v]) {
        int to = o.first;
        if (to == pr) continue;
        auto nw = dfs(to, v);
        res.second = max(res.second + max(nw.first, nw.second), res.first + nw.first + item(o.second + lambda, 1));
        res.first = res.first + max(nw.first, nw.second);
      }
      return res;
    };
    auto res = dfs(0, -1);
    return max(res.first, res.second);
  };
  const ll INF = 3e12;
  ll L = -INF, R = +INF;
  while (R - L > 1) {
    ll M = (L + R) >> 1;
    auto o = solve(M);
    if (o.cnt < k) {
      L = M;
    } else {
      R = M;
    }
  }
  auto o = solve(R);
  if (o.cnt < k) return "Impossible";
//  db3(o.sum, o.cnt, R);
  ll res = o.sum - k * R;
  return to_string(res);
}

int main() {
#ifdef LOCAL
  freopen("m.in", "r", stdin);
  //freopen("m.out", "w", stdout);
#endif

  int n, k;
  while (scanf("%d%d", &n, &k) == 2) {
    vector<pair<pair<int, int>, int>> ed(n - 1);
    for (int i = 0; i < n - 1; i++) {
      scanf("%d%d%d", &ed[i].first.first, &ed[i].first.second, &ed[i].second);
      ed[i].first.first--;
      ed[i].first.second--;
    }
    cout << fast(ed, k) << endl;
  }

  return 0;
}
