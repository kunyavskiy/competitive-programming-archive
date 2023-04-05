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
#define pb push_back
#define sz(a) (int)(a).size()
#define all(a) (a).begin() (a).end()
#define pw(x) (1ll << (x))


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
typedef long double dbl;

//#define TESTL

struct Linear {
#define ll long double
  static const int INF = 0x3fffffff;
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

    ll nt = (dbl)(b.back() - nb) / (na - a.back());
    //printf("%lld,%lld ; %lld,%lld -> %lld\n", na, nb, a.back(), b.back(), nt);
#ifdef LOCAL
    //assert(na * nt + nb >= a.back() * nt + b.back());
    //assert(na * (nt - 1) + nb < a.back() * (nt - 1) + b.back());
#endif
    a.push_back(na);
    b.push_back(nb);
    t.push_back(nt);
  }
#undef ll
};

void print(vector<double> v) {
  for (double x : v) printf("%.17f\n", x);
}

vector<double> fast(vector<int> a) {
  int n = a.size();

  vector<double> l(n), r(n);
  for (int i = 0; i < n; i++) {
    l[i] = a[i];
    r[i] = 1e9;
  }

  for (int it = 0; it < 80; it++) {
    vector<dbl> left(n), right(n);

    ll sum;

    sum = 0;
    Linear ln1;
    for (int i = 0; i < n; i++) {
      ln1.add(i, -sum);
      left[i] = -ln1.get((l[i] + r[i]) / 2);
      sum += a[i];
    }

    Linear ln2;
    for (int i = n - 1; i >= 0; i--) {
      ln2.add(-(i + 1), sum);
      right[i] = ln2.get((l[i] + r[i]) / 2);
      sum -= a[i];
    }

    for (int i = 0; i < n; i++) {
      if (right[i] >= left[i]) {
        l[i] = (l[i] + r[i]) / 2;
      } else {
        r[i] = (l[i] + r[i]) / 2;
      }
    }
  }

  return l;
}

void test() {
  int n = 1e5;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    a[i] = rand() % (int)1e9;
  }
  fast(a);
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  //freopen("c.out", "w", stdout);
#endif
  //test();

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }

    print(fast(a));
  }

  return 0;
}
