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
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


using namespace std;

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");

#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

struct point {
  int x, y, t;

  bool operator<(const point &a) const {
    return x < a.x || (x == a.x && y < a.y);
  }

  point operator+(const point a) const {
    return {x + a.x, y + a.y, 0};
  }

  point operator-(const point a) const {
    return {x - a.x, y - a.y, 0};
  }

  point operator*(const int a) const {
    return {x * a, y * a, 0};
  }

  ll operator*(const point a) const {
    return 1ll * x * a.y - 1ll * y * a.x;
  }
};

void solve_test() {
  int n;
  scanf("%d", &n);
  vector<point> p(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &p[i].x, &p[i].y);
  }

  if (n == 1) {
    cout << "-1000000 0 -1000000 1" << endl;
    return;
  }

  sort(p.begin(), p.end());

  for (int i = 0; i < n; i++) {
//    cout << p[i].x << "," << p[i].y << " ";
    p[i].t = i;
  }
//  cout << endl;

  int n1 = n / 2;
  point p1 = p[n1 - 1];
  point p2 = p[n1];

  vector<pair<point, point>> res;

  if (p2.x > p1.x) {
    res.push_back({{p1.x,     -100000000, 0},
                   {p1.x + 1, 100000000,  0}});
  } else {
    res.push_back({{(p1.x - 1), p2.y + 100000000, 0},
                   {p1.x + 1,   p1.y - 100000000, 0}});
  }

  int cc = 1;

  vector<bool> del(n);

  while (cc < (n + 1) / 2) {

    vector<point> s;
    for (auto pp: p) {
      if (del[pp.t]) continue;
      while (s.size() >= 2) {
        ll x1 = s[s.size() - 1].x - s[s.size() - 2].x;
        ll y1 = s[s.size() - 1].y - s[s.size() - 2].y;
        ll x2 = pp.x - s[s.size() - 1].x;
        ll y2 = pp.y - s[s.size() - 1].y;
//        cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x1 * y2 - x2 * y1 << endl;
        if (x1 * y2 - x2 * y1 > 0) {
          s.pop_back();
        } else {
          break;
        }
      }
      s.push_back(pp);
    }

//    for (int i = 0; i < (int) s.size(); i++) {
//      cout << s[i].t << " ";
//    }
//    cout << endl;

    bool ok = false;
    for (int i = 0; i < (int) s.size(); i++) {
      if (s[i].t < n1 && s[i + 1].t >= n1) {
        auto A = s[i];
        auto B = s[i + 1];
        auto BB = B + (B - A);
        auto AA = A + (A - B) * 100000;
        AA.y--;
        if (A.x == B.x) AA.x++;
        res.push_back({AA, BB});
        cc++;
        del[s[i].t] = true;
        del[s[i + 1].t] = true;
        ok = true;

//        cout << s[i].t << " " << s[i + 1].t << endl;
        break;
      }
    }
    assert(ok);
  }

  for (auto l : res) {
    assert(l.first.x >= -1e9 && l.first.x <= 1e9);
    assert(l.first.y >= -1e9 && l.first.y <= 1e9);
    assert(l.second.x >= -1e9 && l.second.x <= 1e9);
    assert(l.second.y >= -1e9 && l.second.y <= 1e9);
    cout << l.first.x << " " << l.first.y << " " << l.second.x << " " << l.second.y << endl;
  }

  int ccc = 0;
  for (int i = 0; i < (int)res.size(); i++) {
    for (int j = i + 1; j < (int)res.size(); j++) {
      ll s1 = (res[i].second - res[i].first) * (res[j].first - res[i].first);
      ll s2 = (res[i].second - res[i].first) * (res[j].second - res[i].first);
      if (s1 == 0 && s2 == 0) {
        res[j].first = {12123123, 0, 0};
        res[j].second = {12123123 + ccc, 12123123, 0};
        ccc++;
      }
    }
  }

//  for (int i = 0; i < (int)res.size(); i++) {
//    for (int j = i + 1; j < (int)res.size(); j++) {
//      ll s1 = (res[i].second - res[i].first) * (res[j].first - res[i].first);
//      ll s2 = (res[i].second - res[i].first) * (res[j].second - res[i].first);
//      if (s1 == 0 && s2 == 0) {
//        assert(false);
//      }
//    }
//  }

//  for (int i = 0; i < n; i++) {
//    for (int j = i + 1; j < n; j++) {
//      bool ok = false;
//      for (auto l: res) {
//        ll s1 = (l.second - l.first) * (p[i] - l.first);
//        ll s2 = (l.second - l.first) * (p[j] - l.first);
//        if (s1 == 0 || s2 == 0) {
//          cout << n << endl;
//          for (auto pp : p) {
//            cout << pp.x << " " << pp.y << endl;
//          }
//        }
//        assert(s1 != 0 && s2 != 0);
//        if ((s1 < 0) ^ (s2 < 0)) {
//          ok = true;
//        }
//      }
//      if (!ok) {
//        cout << n << endl;
//        for (auto pp : p) {
//          cout << pp.x << " " << pp.y << endl;
//        }
//        cout << i << "=" << j << endl;
//      }
//      assert(ok);
//    }
//  }

}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    solve_test();
  }

  return 0;
}
