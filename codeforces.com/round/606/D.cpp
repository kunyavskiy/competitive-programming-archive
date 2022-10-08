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

const int MOD = 998244353;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) {
  return mpow(x, MOD - 2);
}

struct lin_fun {
  int a = 0, b = 0;

  lin_fun() = default;
  lin_fun(int a, int b) : a(a), b(b) {}

  int apply(int v) {
    v = mul(a, v);
    add(v, b);
    return v;
  }

  lin_fun merge(lin_fun x) {
    lin_fun res{};
    res.a = mul(a, x.a);
    res.b = mul(a, x.b);
    add(res.b, b);
    return res;
  }

  lin_fun inv() {
    // a1 (ax + b) + b1
    lin_fun res{};
    res.a = minv(a);
    res.b = 0;
    sub(res.b, mul(res.a, b));
    assert(merge(res) == lin_fun(1, 0));
    assert(res.merge(*this) == lin_fun(1, 0));
    return res;
  }

  bool operator==(const lin_fun &rhs) const {
    return std::tie(a, b) == std::tie(rhs.a, rhs.b);
  }
};

struct mult_map {
  lin_fun mult;
  map<int, int> vals;

  int get(int x) {
    return mult.apply(vals[x]);
  }

  void set(int x, int v) {
    vals[x] = mult.inv().apply(v);
  }

  void apply_all(lin_fun v) {
    mult = v.merge(mult);
  }
};

int dsu_get(vector<int>&p, int a) {
  if (p[a] == a) return a;
  return p[a] = dsu_get(p, p[a]);
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  vector<int> p(n);
  vector<mult_map> m(n);
  for (int i = 0; i < n; i++) {
    p[i] = i;
    m[i].mult = {1, 0};
    m[i].vals[-1] = m[i].vals[i] = 1;
  }


  for (int i = 1; i < n; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    int ar = dsu_get(p, a);
    int br = dsu_get(p, b);
    if (m[ar].vals.size() > m[br].vals.size()) {
      swap(a, b);
      swap(ar, br);
    }
    int cnt_all_a = m[ar].get(-1);
    int cnt_alive_a = m[ar].get(a);
    int cnt_all_b = m[br].get(-1);
    int cnt_alive_b = m[br].get(b);

    p[a] = b;

    m[ar].vals.erase(-1);
    m[ar].vals.erase(a);
    m[br].vals.erase(b);

    m[ar].apply_all({cnt_all_b, 0});
    m[br].apply_all({cnt_all_a, 0});

    for (auto [x, _] : m[a].vals) {
      m[br].set(x, m[ar].get(x));
    }
    m[a].vals.clear();

    int cnt_alive = mul(cnt_alive_a, cnt_alive_b);

    m[br].apply_all({1, cnt_alive});
    m[br].set(a, mul(cnt_alive_a, cnt_all_b));
    m[br].set(b, mul(cnt_all_a, cnt_alive_b));
  }

  printf("%d\n", m[dsu_get(p, 0)].get(-1));

  return 0;
}
