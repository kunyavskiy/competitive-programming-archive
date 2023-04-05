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
#include <random>

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

struct rect {
  int x, y;
  double p;
  int id;
};

struct segtree {
  int n, N;
  vector<rect> a;
  vector<set<pair<int, int>>> t;

  segtree(vector<rect> _a) {
    a = _a;
    n = a.size();
    N = 1;
    while (N < n) N <<= 1;
    t.resize(2 * N);
    for (int i = 0; i < n; i++) {
      t[N + i].insert({a[i].y, a[i].id});
    }
    for (int i = N - 1; i >= 1; i--) {
      t[i].insert(t[i * 2].begin(), t[i * 2].end());
      t[i].insert(t[i * 2 + 1].begin(), t[i * 2 + 1].end());
    }
  }

  void get_all(int v, int ly, int ry, vector<int> &ans) {
    auto it = t[v].lower_bound({ly, -1});
    while (it != t[v].end() && it->first <= ry) {
      ans.push_back(it->second);
      it++;
    }
  }

  vector<int> get_all(int L, int R, int ly, int ry) {
    L += N;
    R += N;
    vector<int> ans;
    while (L <= R) {
      if (L & 1) get_all(L, ly, ry, ans);
      if (!(R & 1)) get_all(R, ly, ry, ans);
      L = (L + 1) >> 1;
      R = (R - 1) >> 1;
    }
    return ans;
  }

  void del(int x, rect r) {
    x += N;
    while (x > 0) {
      t[x].erase({r.y, r.id});
      x >>= 1;
    }
  }
};

const int INF = 1e9;


// threshold multiplied by 1e3
vector<int> solve(int n, int s, ll threshold, vector<rect> a) {
  auto old = a;
  auto comp_x = [&](const rect &l, const rect &r) {
    if (l.x != r.x) return l.x < r.x;
    if (l.y != r.y) return l.y < r.y;
    return l.id < r.id;
  };
  sort(a.begin(), a.end(), comp_x);

  auto intersect = [&](const rect &r1, const rect &r2) {
    ll dx = max(0, s - abs(r1.x - r2.x));
    ll dy = max(0, s - abs(r1.y - r2.y));
    return dx * dy;
  };

  segtree tr(a);
  vector<char> deleted(n);
  vector<int> ans;
  sort(a.begin(), a.end(), [&](const rect &r1, const rect &r2) {
    return r1.p > r2.p;
  });
  for (auto p : a) {
    if (deleted[p.id]) continue;
    ans.push_back(p.id + 1);

    int L = lower_bound(tr.a.begin(), tr.a.end(), rect({p.x - s, -INF, -INF, -INF}), comp_x) - tr.a.begin();
    int R = lower_bound(tr.a.begin(), tr.a.end(), rect({p.x + s, -INF, -INF, -INF}), comp_x) - tr.a.begin();
    auto ids = tr.get_all(L, R - 1, p.y - s, p.y + s);
    for (auto id : ids) {
      auto r = old[id];

      ll intersection = intersect(p, r);
      if (intersection * (ll)1e3 > threshold * (2LL * s * s - intersection)) {
        deleted[id] = 1;
        int pos = lower_bound(tr.a.begin(), tr.a.end(), r, comp_x) - tr.a.begin();
        assert(tr.a[pos].id == r.id);
        tr.del(pos, r);
      }
    }
  }
  sort(ans.begin(), ans.end());
  return ans;
}

vector<int> slow(int n, int s, ll threshold, vector<rect> a) {
  (void)n;
  vector<int> ans;
  while (!a.empty()) {
    auto r = *min_element(a.begin(), a.end(), [&](const rect &r1, const rect &r2) {
      return r1.p > r2.p;
    });
    ans.push_back(r.id + 1);
    vector<rect> b;
    for (auto p : a) {
      ll dx = max(0, s - abs(r.x - p.x));
      ll dy = max(0, s - abs(r.y - p.y));
      ll inter = dx * dy;

      if (inter * (ll)1e3 <= threshold * (2LL * s * s - inter)) {
        b.push_back(p);
      }
    }
    a = b;
  }
  sort(ans.begin(), ans.end());
  return ans;
}

void stress() {
  for (int it = 0;; it++ ){
    mt19937 rnd(it);
    db(it);

    int C = 1e7;
    int n = rnd() % 50 + 1;
    int s = rnd() % C * 2 + 1;
    ll thresh = rnd() % (int)4e2 + 3e2;
    vector<rect> a(n);
    for (int i = 0; i < n; i++) {
      a[i].x = rnd() % C;
      a[i].y = rnd() % C;
      a[i].id = i;
      a[i].p = rnd();
    }
    auto ans1 = solve(n, s, thresh, a);
    db("");
    auto ans2 = slow(n, s, thresh, a);
    dbv(ans1);
    dbv(ans2);
    assert(ans1 == ans2);
  }
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
//  freopen("e.out", "w", stdout);
#endif
//  stress();

  int T;
  scanf("%d", &T);
  for (int test = 1; test <= T; test++) {
    int n, s;
    double threshold;
    scanf("%d%d%lf", &n, &s, &threshold);
    s *= 2;
    vector<rect> a(n);
    for (int i = 0; i < n; i++) {
      scanf("%d%d%lf", &a[i].x, &a[i].y, &a[i].p);
      a[i].x *= 2;
      a[i].y *= 2;
      a[i].x += s / 2;
      a[i].y += s / 2;
      a[i].id = i;
    }
    auto ans = solve(n, s, round(threshold * 1e3), a);
    printf("Case #%d: %d\n", test, (int)ans.size());
    for (int i = 0; i < (int)ans.size(); i++) printf("%d%c", ans[i], " \n"[i + 1 == (int)ans.size()]);
  }


  return 0;
}
