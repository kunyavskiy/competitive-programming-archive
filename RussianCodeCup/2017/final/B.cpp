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

const int MOD1 = 1000000007;
const int MOD2 = 1000000009;

struct HV {
  int f, s;

  bool operator<(const HV &rhs) const {
    if (f != rhs.f)
      return f < rhs.f;
    return s < rhs.s;
  }

  bool operator==(const HV &x) const {
    return f == x.f && s == x.s;
  }

  explicit HV(int val) {
    f = val % MOD1;
    s = val % MOD2;
  }

  HV(int a, int b) : f(a), s(b) {
  }

  ll to_long() const {
    return (((ll)f) << 32) + s;
  }
};

HV operator+(const HV &a, const HV &b) {
  return {(a.f + b.f) % MOD1, (a.s + b.s) % MOD2};
}

HV operator-(const HV &a, const HV &b) {
  return {(a.f - b.f + MOD1) % MOD1, (a.s - b.s + MOD2) % MOD2};
}

HV operator*(const HV &a, const HV &b) {
  return {(int) ((a.f * 1LL * b.f) % MOD1), (int) ((a.s * 1LL * b.s) % MOD2)};
}

struct word {
  ll a, b;
};

char buf[1000100];
const int P = 23917;

vector<word> v[1000100];

void solve() {
  int n;
  scanf("%d", &n);
  int clean_ptr = 0;
  for (int it = 0; it < n; it++) {
    scanf("%s", buf);
    HV a = HV(1);
    HV b = a * HV(P) + HV(buf[0]);
    v[0].push_back({a.to_long(), b.to_long()});
    for (int i = 1; buf[i]; i++) {
      clean_ptr = max(clean_ptr, i);
      a = a * HV(P) + HV(buf[i]);
      b = b * HV(P) + HV(buf[i]);
      v[i].push_back({a.to_long(), b.to_long()});
    }
  }
  TIMESTAMP("build");
  set<ll> bad, nbad;
  int ans = 0;
  for (int i = clean_ptr; i >= 0; i--) {
    for (const word &w : v[i]) {
      if (!bad.count(w.b)) {
        nbad.insert(w.a);
        bad.insert(w.b);
        ans++;
      }
    }
    bad.swap(nbad);
    nbad.clear();
    v[i].clear();
  }
  printf("%d\n", ans);
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t --> 0)
    solve();

  return 0;
}
