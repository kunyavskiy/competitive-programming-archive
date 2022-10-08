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

struct pt {
  ll x, y;
  int hpl() const {
    return y < 0 || (y == 0 && x < 0);
  }
};

pt operator-(const pt& a, const pt&b) {
  return {a.x - b.x, a.y - b.y};
}

ll sp(const pt& a, const pt& b) {
  return a.x * b.x + a.y * b.y;
}

ll vp(const pt& a, const pt& b) {
  return a.x * b.y - a.y * b.x;
}

int calc_good(vector<pt> v) {
  sort(v.begin(), v.end(), [](const pt& a, const pt& b) {
    int hpla = a.hpl();
    int hplb = b.hpl();
    if (hpla != hplb) return hpla < hplb;
    return vp(a, b) > 0;
  });

  int n = (int)v.size();
  for (int i = 0; i < n; i++) {
    v.push_back(v[i]);
  }

  int ans = 0;

  int p1, p2;
  p1 = p2 = 0;
  for (int i = 0; i < n; i++) {
    if (p1 < i) p1 = i;
    while (p1 < i + n && vp(v[p1], v[i]) == 0) p1++;
    if (p2 < p1) p2 = p1;
    while (p2 < i + n && (sp(v[i], v[p2]) > 0 && vp(v[i], v[p2]) > 0)) p2++;
    ans += p2 - p1;
  }
  return ans;
}

int same_line(vector<pt> v) {
  sort(v.begin(), v.end(), [](const pt& a, const pt& b) {
    return vp(a, b) > 0;
  });

  int ans = 0;

  int n = (int) v.size();

  int p1 = 0;
  for (int i = 0; i < n; i++) {
    if (p1 < i) p1 = i;
    while (p1 < n && vp(v[p1], v[i]) == 0) p1++;
    ans += p1 - i - 1;
  }
  return ans;
}


void solve() {
  int n;
  scanf("%d", &n);
  vector<pt> v(n);
  for (auto& p : v) {
    scanf("%lld%lld", &p.x, &p.y);
  }

  sort(v.begin(), v.end(), [](const pt& a, const pt& b) {
    if (a.y != b.y) return a.y < b.y;
    return a.x < b.x;
  });

  ll ans = - 2 * n * 1LL * (n - 1) * 1LL * (n - 2) / 6;

  for (int i = 0; i < n; i++) {
    vector<pt> vv;
    for (int j = 0; j < n; j++) {
      if (i != j) {
        vv.push_back(v[j] - v[i]);
      }
    }
    int t = calc_good(vv);
    eprintf("%lld %lld %d\n", v[i].x, v[i].y, t);
    ans += t;
  }

  for (int i = 0; i < n; i++) {
    vector<pt> vv;
    for (int j = i + 1; j < n; j++) {
      vv.push_back(v[j] - v[i]);
    }
    int t = same_line(vv);
    eprintf("%lld %lld %d\n", v[i].x, v[i].y, t);
    ans += t * 2;
  }

  printf("%lld\n", ans);
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);

  while (t --> 0)
    solve();

  return 0;
}
