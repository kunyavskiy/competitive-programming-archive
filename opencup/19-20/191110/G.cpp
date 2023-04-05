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

template <typename T>
struct fenwick {
  int n;
  vector<T> f;

  fenwick() {}

  fenwick(int N) {
    n = N;
    f.assign(N, T(0));
  }

  fenwick(vector<T> a) {
    n = a.size();
    for (int i = 0; i < n; i++) add(i, a[i]);
  }

  void add(int x, T y) {
    for (; x < n; x |= x + 1) f[x] += y;
  }

  T get(int x) {
    T res(0);
    for (; x >= 0; x = (x & (x + 1)) - 1) res += f[x];
    return res;
  }

  T get(int l, int r) {
    return get(r) - get(l - 1);
  }

  // return min i: sum(0, i) > x
  int upper_bound(T x) {
    int k = 1;
    while (2 * k <= n) k *= 2;

    int res = 0;
    while (k > 0) {
      if (f[res + k - 1] <= x) {
        x -= f[res + k - 1];
        res += k;
      }
      k /= 2;
    }
    return res;
  }
};

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
//  freopen("g.out", "w", stdout);
#endif

  int T;
  scanf("%d", &T);
  while (T--) {
    int n, k;
    scanf("%d%d", &n, &k);
    vector<int> a(n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    vector<pair<int, int>> b(k);
    for (int i = 0; i < k; i++) scanf("%d%d", &b[i].first, &b[i].second);

    vector<pair<pair<int, int>, int>> vct;
    vct.push_back({{-INF, +INF}, -1});

    int m = *max_element(a.begin(), a.end()) + 5;
    for (auto &o : b) {
      o.first = min(o.first, m - 1);
      o.second = min(o.second, m - 1);
    }
    vector<vector<pair<int, int>>> ev(m);

    for (int i = 0; i < n; i++) {
      for (auto &o : vct) {
        o.first.first = min(o.first.first, a[i]);
        o.first.second = max(o.first.second, a[i]);
      }
      vct.push_back({{a[i], a[i]}, i});
      vector<pair<pair<int, int>, int>> nvct;
      for (auto o : vct) {
        if (!nvct.empty() && nvct.back().first == o.first) {
          nvct.back().second = o.second;
        } else {
          nvct.push_back(o);
        }
      }
      vct = nvct;

      for (int j = 1; j < (int)vct.size(); j++) {
        ev[vct[j].first.first].push_back({vct[j].first.second, vct[j].second - vct[j - 1].second});
      }
    }

    vector<vector<int>> q(m);
    for (int i = 0; i < k; i++) {
      q[b[i].first].push_back(i);
    }

    vector<ll> ans(k);
    fenwick<ll> f(m);
    for (int i = m - 1; i >= 0; i--) {
      for (auto o : ev[i]) {
        f.add(o.first, o.second);
      }

      for (int id : q[i]) {
        ans[id] = f.get(b[id].second);
      }
    }
    for (int i = 0; i < k; i++) printf("%lld\n", ans[i]);
  }

  return 0;
}
