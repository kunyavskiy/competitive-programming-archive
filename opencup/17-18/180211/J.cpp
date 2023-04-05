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

const int MOD = 1000000007;

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

struct query {
  int l, r, id;
};

vector<int> ans;
vector<int> a;
int mod;

struct item {
  vector<int> v;
  item() {  }
  item(int m) : v(m) {
    v[0] = 1;
  }
};

item operator+(const item& a, int b) {
  assert((int)a.v.size() == mod);
  item res(mod);
  for (int i = 0; i < mod; i++) {
    res.v[i] = a.v[i];
    add(res.v[i], a.v[(i - b + mod) % mod]);
  }
  return res;
}

int operator*(const item& a, const item& b) {
  assert((int)a.v.size() == mod);
  assert((int)b.v.size() == mod);
  int res = mul(a.v[0], b.v[0]);
  for (int i = 1; i < mod; i++) {
    add(res, mul(a.v[i], b.v[mod-i]));
  }
  return res;
}

vector<item> vals;

void solve(int l, int r, vector<query> q) {
  if (r - l == 1) {
    for (const auto &x : q) {
      ans[x.id] = 1 + (a[l] == 0);
    }
    return;
  }
  vector<query> lf, mid, rg;
  int m = (l + r) / 2;
  for (const auto &x : q) {
    if (x.r <= m) {
      lf.push_back(x);
    } else if (x.l >= m) {
      rg.push_back(x);
    } else {
      mid.push_back(x);
    }
  }
  solve(l, m, lf);
  solve(m, r, rg);

  vals[m] = item(::mod);
  for (int i = m; i < r; i++) {
    vals[i + 1] = vals[i] + a[i];
  }

  for (int i = m - 1; i >= l; i--) {
    vals[i] = vals[i + 1] + a[i];
  }

  for (const query &x : mid) {
    ans[x.id] = vals[x.l] * vals[x.r];
  }

}

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int n;
  scanf("%d%d", &n, &mod);
  a.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    a[i] %= mod;
  }
  int qs;
  scanf("%d", &qs);
  vector<query> q(qs);
  ans.resize(qs);
  for (int i = 0; i < qs; i++) {
    scanf("%d%d", &q[i].l, &q[i].r);
    q[i].l--;
    q[i].id = i;
  }
  vals.resize(n + 1);

  solve(0, n, q);

  for (int i = 0; i < qs; i++) {
    printf("%d\n", ans[i]);
  }
  return 0;
}
