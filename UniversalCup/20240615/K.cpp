#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x)                                                           \
  eprintf("[" #x "] Time : %.3lf s.\n",                                        \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...)                                                     \
  eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__,                            \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y)                                                              \
  cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z)                                                           \
  cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y   \
       << ", " << z << ")\n"
#define dbv(a)                                                                 \
  cerr << #a << " = ";                                                         \
  for (auto xxxx : a)                                                          \
    cerr << xxxx << " ";                                                       \
  cerr << endl

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() { TIMESTAMPf("%s", what.data()); }
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

  bool operator==(const HV &x) const { return f == x.f && s == x.s; }

  long long hash() {
    return ((ll)f << 32) + s;
  }
};

HV operator+(const HV &a, const HV &b) {
  return {(a.f + b.f) % MOD1, (a.s + b.s) % MOD2};
}

HV operator-(const HV &a, const HV &b) {
  return {(a.f - b.f + MOD1) % MOD1, (a.s - b.s + MOD2) % MOD2};
}

HV operator*(const HV &a, const HV &b) {
  return {(int)((a.f * 1LL * b.f) % MOD1), (int)((a.s * 1LL * b.s) % MOD2)};
}

const int MAXC = 1001000;

HV p2[MAXC];
HV p2m1[MAXC];
vector<vector<int>> ss;

vector<int> touched;
int a[MAXC];
int amin = 0;
int amax = 0;
HV ahash = {0, 0};

void add1(int x) {
  while (a[x] == 1) {
    a[x] = 0;
    ahash = ahash - p2[x];
    if (x == amin) amin++;
    x++;
  }
  amax = max(amax, x);
  amin = min(amin, x);
  a[x] = 1;
  ahash = ahash + p2[x];
  touched.push_back(x);
}

void clear() {
  ahash = {0, 0};
  amin = std::numeric_limits<int>::max();
  amax = 0;
  for (int x : touched) {
    a[x] = 0;
  }
  touched.clear();
}

void found(int l, int r) {
  ss[r].push_back(l);
}

void generate(const vector<int>&vals, int l, int r) {
  if (l == r) return;
  if (l == r - 1) {
    found(l, r);
    return;
  }
  int mid = (l + r) / 2;
  generate(vals, l, mid);
  generate(vals, mid, r);

  vector<pair<int, HV>> lhashes;
  vector<pair<int, HV>> rhashes;
  map<ll, int> rvals;
  map<ll, int> lvals;
  clear();
  for (int i = mid; i < r; i++) {
    add1(vals[i]);
    rhashes.emplace_back(amax, ahash);
    rvals[ahash.hash()] = i;
  }
  clear();
  for (int i = mid - 1; i >= l; i--) {
    add1(vals[i]);
    lhashes.emplace_back(amax, ahash - p2[amin] + p2m1[amin]);
    lvals[lhashes.back().second.hash()] = i;
  }

  for (int i = mid; i < r; i++) {
    auto [max, hash] = rhashes[i - mid];
    auto it = lvals.find((p2m1[max + 1] - hash).hash());
    if (it == lvals.end())
      continue;
    found(it->second, i + 1);
  }
  for (int i = mid - 1; i >= l; i--) {
    auto [max, hash] = lhashes[mid - i - 1];
    auto it = rvals.find((p2m1[max + 1] - hash).hash());
    if (it == rvals.end())
      continue;
    found(i, it->second + 1);
  }

}

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

  p2[0] = HV{1, 1};
  p2[1] = HV{29, 31};
  for (int i = 2; i < MAXC; i++) {
    p2[i] = p2[i - 1] * p2[1];
  }
  p2m1[0] = HV{0, 0};
  for (int i = 1; i < MAXC; i++) {
    p2m1[i] = p2m1[i - 1] + p2[i - 1];
  }

  int n;
  scanf("%d", &n);
  vector<int> vals(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &vals[i]);
  }
  ss.resize(n + 1);
  generate(vals, 0, n);

  for (auto& s : ss) {
    sort(s.begin(), s.end());
    s.erase(unique(s.begin(), s.end()), s.end());
  }

  const int ANSMOD = 1000000007;
  auto add = [](int& a, int b) {
    a += b;
    if (a >= ANSMOD) a -= ANSMOD;
  };
  vector<int> ans(n + 1);
  ans[0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j : ss[i]) {
      eprintf("%d..%d\n", j, i);
      add(ans[i], ans[j]);
    }
  }
  printf("%d\n", ans.back());

#ifdef LOCAL
  vector<int> ans2(n + 1);
  ans2[0] = 1;
  auto check = [&](int l, int r) -> bool {
    vector<int> v(vals.begin() + l, vals.begin() + r);
    sort(v.begin(), v.end());
    vector<int> st;
    for (int x : v) {
      while (!st.empty() && st.back() == x) {
        st.pop_back();
        x++;
      }
      st.push_back(x);
    }
    return st.size() == 1;
  };
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < i; j++) {
      if (check(j, i)) {
        add(ans2[i], ans2[j]);
      }
    }
  }
  assert(ans == ans2);
#endif

  return 0;
}
