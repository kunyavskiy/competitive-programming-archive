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

struct point {
  ll x, y;

  point operator - (point a) {
    return {x - a.x, y - a.y};
  }

  bool operator==(const point &rhs) const {
    return std::tie(x, y) == std::tie(rhs.x, rhs.y);
  }

  bool operator!=(const point &rhs) const {
    return !(rhs == *this);
  }
};

int side(point a, point b) {
  ll vp = a.x * b.y - a.y * b.x;
  assert(vp != 0);
  return vp < 0 ? -1 : 1;
}


ll sum(vector<ll> &fn, int r) {
  ll res = 0;
  r--;
  while (r >= 0) {
    res += fn[r];
    r = (r & (r + 1)) - 1;
  }
  return res;
}

ll sum(vector<ll> &fn, int l, int r) {
  return sum(fn, r) - sum(fn, l);
}

void inc(vector<ll> &fn, int x) {
  while (x < (int)fn.size()) {
    fn[x]++;
    x = x | (x + 1);
  }
}



void solve(vector<point> &points, vector<point> d) {
  vector<vector<int>> q(4);
  for (int j = 0; j < (int)points.size(); j++) {
    point &p = points[j];
    int s = 0;
    for (int i = 0; i < 4; i++) {
      int t1 = i ^ 2;
      int t2 = i ^ 3;
      if (d[t1] != d[i] && d[t2] != d[i]) {
        if (side(d[i] - p, d[t1] - p) != side(d[i] - p, d[t2] - p)) {
          q[i].push_back(j);
          s++;
        }
      }
    }
    assert(s == 0 || s == 2);
  }
  int n = points.size();
  vector<int> l(n, -1), r(n, -1);
  int t = 0;
  for (int i : {0,2,1,3}) {
    sort(q[i].begin(), q[i].end(), [&](auto a, auto b) {
      point p = points[a] - d[i];
      point q = points[b] - d[i];
      ll vp = p.x * q.y - p.y * q.x;
      return vp < 0;
    });

    if (i == 1 || i == 2) {
      reverse(q[i].begin(), q[i].end());
    }

    for (int j : q[i]) {
//      cout << i << " " << j << "\n";
      if (l[j] == -1) {
        l[j] = t++;
      } else {
        r[j] = t++;
      }
    }
  }
  vector<pair<int, int>> f;
  for (int i = 0; i < n; i++) {
    if (l[i] != -1) {
      f.emplace_back(l[i], r[i]);
      db2(l[i], r[i]);
    }
  }
  sort(f.begin(), f.end());

  vector<ll> fn(2 * n);
  ll ans = 0;
  for (auto [l, r] : f) {
    ans += sum(fn, l, r);
    inc(fn, r);
  }
  cout << ans << " ";


}

void solve_test() {
  int n;
  scanf("%d", &n);
  vector<point> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld%lld", &a[i].x, &a[i].y);
  }
  int m;
  scanf("%d", &m);
  vector<point> b(m);
  for (int i = 0; i < m; i++) {
    scanf("%lld%lld", &b[i].x, &b[i].y);
  }

  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    solve(b, {a[x], a[(x + 1) % n], a[y], a[(y + 1) % n]});
  }
  cout << "\n";

}

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) solve_test();

  return 0;
}
