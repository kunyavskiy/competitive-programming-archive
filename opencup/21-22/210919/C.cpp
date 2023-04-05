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

long long safe_div(long long a, long long b) {
  if (b == 0) { assert(a == 0); return 0; }
  return a / b;
}

struct dsu {
  vector<int> p;
  explicit dsu(int n) : p(n) {
    for (int i = 0; i < (int)p.size(); i++) p[i] = i;
  }

  int get(int x) { return p[x] == x ? x : p[x] = get(p[x]); }
  void merge(int x, int y) {
    p[get(x)] = get(y);
  }

};

long long solve_stupid(vector<ll> a) {
  auto mx = *max_element(a.begin(), a.end());
  dsu d(mx);
  for (auto x : a) {
    for (int i = 0; i < x; i++) {
      d.merge(i, x - i - 1);
    }
  }
  int ans = 0;
  for (int i = 1; i <= mx; i++) {
    bool ok = true;
    for (int j = 0; j < i; j++) {
      ok = ok && d.get(j) == d.get(i - j - 1);
    }
    if (ok) {
      eprintf("must be for len = %d\n", i);
      ans++;
    }
  }
  return ans;
}

ll solve_smart(set<ll>& s) {
  if (s.size() == 1) return 1;
  ll max = *s.rbegin();
  ll min = max;
  ll d = 0;
  s.erase(max);
  while (!s.empty() && *s.rbegin() >= min - (d == 0 ? min : d) / 2) {
    ll cur = *s.rbegin();
    if (2 * cur == min && (cur % 2 == 1 || s.count(cur / 2)) == 0) break;
    d = __gcd(max - cur, d);
    s.erase(cur);
    min = max % d + d;
  }
  if (d == 0) {
    return solve_smart(s) + 1;
  }
  if (min != d) {
    s.insert(min - d);
  }
  if (d == 1) {
    return max;
  }
  ll inner = solve_smart(s);
  if (2 * inner == min) return max;
  return inner + (max - min) / d + 1;
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif
  int n;
  while (scanf("%d%*d", &n) == 1) {
    eprintf("%d -1\n", n);
    if (n == 0) break;
    vector<ll> v(n);
    for (auto& x : v) {
      scanf("%lld", &x);
      eprintf("%lld ", x);
    }
#ifdef LOCAL
    vector<ll> vv = v;
#endif
    eprintf("\n");
    set<ll> s(v.begin(), v.end());
    s.insert(1);
    auto ans = solve_smart(s);

#ifdef LOCAL
    assert(ans == solve_stupid(vv));
#endif
    printf("%lld\n", ans);
  }

  return 0;
}
