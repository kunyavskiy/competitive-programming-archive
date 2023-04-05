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

ll calc(vector<int> a) {
  ll res = 1e18;
  int n = a.size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      ll d = abs(a[i] - a[j]);
      int t = a[i];
      a[i] = a[j];
      set<int> s;
      for (int k = 0; k < n; k++) {
        s.insert(a[k]);
        d += (k + 1) * s.size();
      }
      a[i] = t;
      res = min(res, d);
//      cout << a[i] << " " << a[j] << " " << d << endl;
    }
  }
  return res;
}

void solve_test() {
  int n;
  scanf("%d", &n);
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  map<int, int> last;
  vector<int> next(n);
  for (int i = n - 1; i >= 0; i--) {
    if (last[a[i]] == 0) {
      next[i] = n;
    } else {
      next[i] = last[a[i]];
    }
    last[a[i]] = i;
  }

  set<int> has;
  ll s = 0;
  ll best = 0;
  vector<bool> good(n);
  for (int i = 0; i < n; i++) {
    if (has.count(a[i])) continue;
    good[i] = true;
    s += 1ll * (i + 1 + n) * (n - i) / 2;
    if (has.size() > 0) {
      auto p = has.upper_bound(a[i]);
      int d = (int)2e9;
      if (p != has.end()) {
        int y = *p;
        d = min(d, abs(a[i] - y));
      }
      if (p != has.begin()) {
        --p;
        int y = *p;
        d = min(d, abs(a[i] - y));
      }
      ll ds = d - 1ll * (i + 1 + n) * (n - i) / 2;
      int j = next[i];
      ds += 1ll * (j + 1 + n) * (n - j) / 2;
      best = min(best, ds);
    }
    has.insert(a[i]);
  }

  {
    set<pair<int, ll>> b;
    for (int i = n - 1; i >= 0; i--) {
      if (good[i]) {
        auto p = b.upper_bound({a[i], 0});
        if (p != b.end()) {
          ll ds = (*p).second - a[i];
          int j = next[i];
          ds += 1ll * (j + 1 + n) * (n - j) / 2;
          best = min(best, ds);
        }
        ll dd = -1ll * (i + 1 + n) * (n - i) / 2 + a[i];
        while (true) {
          p = b.upper_bound({a[i], 0});
          if (p == b.begin() || (--p)->second < dd) {
            break;
          }
          b.erase(p);
        }
        bool ok = true;
        p = b.upper_bound({a[i], 0});
        if (p != b.end()) {
          if (p->second <= dd) ok = false;
        }
        if (ok) b.insert({a[i], dd});
      }
    }
  }

  {
    set<pair<int, ll>> b;
    for (int i = n - 1; i >= 0; i--) {
      if (good[i]) {
        auto p = b.upper_bound({-a[i], 0});
        if (p != b.end()) {
          ll ds = (*p).second + a[i];
          int j = next[i];
          ds += 1ll * (j + 1 + n) * (n - j) / 2;
          best = min(best, ds);
        }
        ll dd = -1ll * (i + 1 + n) * (n - i) / 2 - a[i];
        while (true) {
          p = b.upper_bound({-a[i], 0});
          if (p == b.begin() || (--p)->second < dd) {
            break;
          }
          b.erase(p);
        }
        bool ok = true;
        p = b.upper_bound({-a[i], 0});
        if (p != b.end()) {
          if (p->second <= dd) ok = false;
        }
        if (ok) b.insert({-a[i], dd});
      }
    }
  }

//  cout << s << " " << best << endl;
//
//  calc(a);

//  if (s + best != calc(a)) {
//    for (int i = 0; i < n; i++) {
//      cout << a[i] << " ";
//    }
//    cout << endl;
//    cout << s + best << " " << calc(a) << endl;
//  }

  cout << s + best << endl;
}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    solve_test();
  }

  return 0;
}
