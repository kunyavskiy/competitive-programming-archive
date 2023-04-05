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
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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

const int INF = 0x3fffffff;

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
struct val {
  int a, pos, ord;
};

vector<Linear> tree;

ll get(int at, int pos, int lst) {
  ll ans = -at;
  int v = 1;
  int l = 0;
  int r = lst;
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (pos <= m) {
      r = m;
      v = 2 * v;
    } else {
      ll cur = tree[2 * v].get(at);
//      eprintf("get %lld from %d\n", cur, 2 * v);
      ans = max(ans, cur);
      l = m;
      v = 2 * v + 1;
    }
  }
  ll cur = tree[v].get(at);
//  eprintf("get %lld from %d\n", cur, v);
  ans = max(ans, cur);
//  eprintf("ans = %lld\n", ans);
  return ans;
}

void add(int pos, ll a, ll b, int lst) {
  int v = 1;
  int l = 0;
  int r = lst;
  while (r - l > 1) {
//    eprintf("add [%lld, %lld] to %d\n", a, b, v);
    tree[v].add(a, b);
    int m = (l + r) / 2;
    if (pos < m) {
      r = m;
      v = 2 * v;
    } else {
      l = m;
      v = 2 * v + 1;
    }
  }
  tree[v].add(a, b);
}


int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  {
    Linear test;
    test.add(0, 1);
    test.add(2, -1);
    test.get(4);
  }

  int n;
  scanf("%d", &n);

  vector<val> v(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &v[i].a);
    v[i].pos = i;
  }
  sort(v.begin(), v.end(), [](const val& a, const val& b) { return a.a < b.a;});

  int ord = -1;
  for (int i = 0; i < n; i++) {
    if (i == 0 || v[i].a != v[i-1].a) {
      ord++;
    }
    v[i].ord = ord;
  }
  ord++;
  sort(v.begin(), v.end(), [](const val& a, const val& b) { return a.pos < b.pos;});

  int lst = 2;
  while (lst < ord) lst *= 2;

  tree = vector<Linear>(2 * lst);
  for (int i = 1; i < 2 * lst; i++) {
    tree[i].add(0, -(1LL << 60));
  }

  for (int i = 0; i < n; i++) {
    ll val = v[i].a - i * 1LL * (i - 1) / 2 + get(i, v[i].ord + 1, lst);
    add(v[i].ord, i, val - i * 1LL * (i + 1) / 2, lst);
    eprintf("%d %lld %d\n", i, val, v[i].ord);
  }

  printf("%lld\n", get(n, ord + 1, lst) - n * 1LL * (n - 1) / 2);


  return 0;
}
