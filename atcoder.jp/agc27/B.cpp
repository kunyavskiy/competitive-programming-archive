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

//#define TESTL

struct Linear {
  vector<ll> a;
  vector<ll> b;
  vector<ll> t;

#ifdef TESTL
  vector<ll> aa, ab;
#endif

  ll get(ll x) {
    int id = upper_bound(t.begin(), t.end(), x) - t.begin();
    assert(id != 0);
    id--;
    ll res = a[id] * x + b[id];
#ifdef TESTL
    ll res2 = -(1LL << 60);
    int rid = -1;
    for (int i = 0; i < (int) aa.size(); i++) {
      if (res2 < aa[i] * x + ab[i]) {
        rid = i;
        res2 = aa[i] * x + ab[i];
      }
    }
    fprintf(stderr, "get %p %lld => %lld == %lld?\n", this, x, res, res2);
    if (res != res2) {
      fprintf(stderr, "%lld,%lld %lld,%lld\n", a[id], b[id], aa[rid], ab[rid]);
      for (int i = 0; i < (int)a.size(); i++) {
        printf("%lld %lld %lld\n", a[i], b[i], t[i]);
      }
    }
    assert(res == res2);
#endif
    return res;
  }

  void add(ll na, ll nb) {
#ifdef TESTL
    fprintf(stderr, "add %p %lld %lld\n", this, na, nb);
    aa.push_back(na);
    ab.push_back(nb);
#endif
    while (!t.empty() && na * t.back() + nb > a.back() * t.back() + b.back()) {
      a.pop_back();
      b.pop_back();
      t.pop_back();
    }

    if (t.empty()) {
      a.push_back(na);
      b.push_back(nb);
      t.push_back(0);
      return;
    }
    assert(na >= a.back());
    // a1 * x + b1 > a2 * x + b2
    // (a1 - a2) * x > b2 - b1

    ll nt = (b.back() - nb + na - a.back() - 1) / (na - a.back());
    //printf("%lld,%lld ; %lld,%lld -> %lld\n", na, nb, a.back(), b.back(), nt);
    assert(na * nt + nb >= a.back() * nt + b.back());
    assert(na * (nt - 1) + nb < a.back() * (nt - 1) + b.back());
    a.push_back(na);
    b.push_back(nb);
    t.push_back(nt);
  }
};

class LinearSlow {
  vector<ll> a;
  vector<ll> b;
public:

  ll get(ll x) {
    ll res = -(1LL << 60);
    for (int i = 0; i < (int)a.size(); i++) {
      res = max(res, a[i] * x + b[i]);
    }
    return res;
  }

  void add(ll na, ll nb) {
    a.push_back(na);
    b.push_back(nb);
  }
};


int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n;
  while (scanf("%d\n", &n) == 1) {
    ll x;
    scanf("%lld", &x);
    vector<ll> v(n);
    for (ll &a : v) scanf("%lld", &a);

    ll ans = n * x;
    for (int i = 0; i < n; i++) {
      ans += 5LL * v[i];
    }

    vector<ll> dp(n + 1, 1LL << 60);
    vector<ll> prefix_sum(n + 1);
    for (int i = 0; i < n; i++) {
      prefix_sum[i + 1] = prefix_sum[i] + v[i];
    }
    vector<ll> prefix_sum2(n + 1);
    for (int i = 0; i < n; i++) {
      prefix_sum2[i + 1] = prefix_sum2[i] + v[i] * i;
    }
    dp[0] = 0;

    Linear solver;
    solver.add(0, 0);

    for (int i = 0; i < n; i++) {
      dp[i + 1] = -solver.get(i);
      dp[i + 1] -= 2 * prefix_sum2[i];
      dp[i + 1] += 2 * (i - 1) * prefix_sum[i];
      dp[i + 1] += x;
      solver.add(2 * prefix_sum[i + 1], -(dp[i + 1] + 2 * prefix_sum2[i + 1]) - 2 * prefix_sum[i + 1]);
    }

    printf("%lld\n", ans + dp[n]);
  }

  return 0;
}
