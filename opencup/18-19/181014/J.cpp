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

const int INF = 1e9 + 1;

struct item {
  ll value;
  ll cnt;
  int id;

  item(ll value, ll cnt, int id) : value(value), cnt(cnt), id(id) {}

  friend bool operator<(const item &lhs, const item &rhs) {
    return std::tie(lhs.value, lhs.cnt, lhs.id) < std::tie(rhs.value, rhs.cnt, rhs.id);
  }
};

struct gen {
  ll len;
  ll shift;
  ll value;
  ll cur;
  int id;

  ll get_less(ll v) const {
    v /= value;
    if (v == 0) {
      return 0;
    }
    if (v > len) {
      return get_less(len * 1LL * value);
    }
    v--;

    ll A = min(shift, len - shift - 1);
    ll B = len - A - 1;
    ll ans = 0;
    assert(v - B <= A);
    ll t1 = v - (min(A, v)) + 1;
    ll t2 = v - (max(0LL, v - B)) + 1;
    if (t1 <= t2) {
      ans += t2 * (t2 + 1) / 2;
      ans -= t1 * (t1 - 1) / 2;
    }
    ans += (B + 1) * max(0LL, v - B);
    return ans;
  }

  ll get_cnt(ll v) const {
    return get_less(v) - get_less(v - 1);
  }

  item next() {
    cur++;
    return {cur * 1LL * value, get_cnt(cur * value), id};
  }
};


int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> h(n);
    for (int &x : h) {
      scanf("%d", &x);
    }

    ll L, R;
    scanf("%lld %lld", &L, &R);
    L--;

    vector<int> r(n);

    {
      vector<pair<int, int>> st;
      st.emplace_back(-INF, n);
      for (int i = n - 1; i >= 0; i--) {
        while (st.back().first >= h[i]) {
          st.pop_back();
        }
        r[i] = st.back().second;
        st.emplace_back(h[i], i);
      }
    }

    vector<int> l(n);
    {
      vector<pair<int, int>> st;
      st.emplace_back(-INF, -1);
      for (int i = 0; i < n; i++) {
        while (st.back().first > h[i]) {
          st.pop_back();
        }
        l[i] = st.back().second;
        st.emplace_back(h[i], i);
      }
    }

    vector<gen> g(n);

    //dbv(l);
    //dbv(r);

    for (int i = 0; i < n; i++) {
      g[i].len = r[i] - l[i] - 1;
      g[i].shift = i - l[i] - 1;
      g[i].value = h[i];
      g[i].cur = 0;
      g[i].id = i;
    }

    ll lf = 0, rg = 1e18;

    auto get_less_cnt = [&g](ll m) {
      ll tot_cnt = 0;
      for (const auto &x : g) {
        tot_cnt += x.get_less(m);
      }
      return tot_cnt;
    };

    while (rg - lf > 1) {
      ll m = (lf + rg) / 2;
      if (get_less_cnt(m) > L) {
        rg = m;
      } else {
        lf = m;
      }
    }

    ll less_cnt = get_less_cnt(rg);
    less_cnt = min(less_cnt, R);
    assert(less_cnt > L);
    vector<ll> ans;
    for (ll x = L; x < less_cnt; x++) {
      ans.push_back(rg);
    }

    set<item> s;

    auto process = [&](gen &g) {
      auto x = g.next();
      if (x.cnt > 0) {
        s.insert(x);
      }
    };

    for (auto &x : g) {
      x.cur = rg / x.value;
      process(x);
    }

    while ((int)ans.size() < R - L) {
      assert(!s.empty());
      auto x = *s.begin();
      s.erase(s.begin());
      process(g[x.id]);
      for (int i = 0; i < x.cnt && (int)ans.size() < R - L; i++) {
        ans.push_back(x.value);
      }
    }

    for (ll i : ans) {
      printf("%lld ", i);
    }
    printf("\n");
  }

  return 0;
}
