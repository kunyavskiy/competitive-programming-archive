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

int main() {
#ifdef LOCAL
  freopen("p11a.in", "r", stdin);
  freopen("p11a.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  vector<double> x(n), y(n);
  for (int i = 0; i < n; i++) {
    scanf("%lf%lf", &x[i], &y[i]);
  }
  vector<double> a(n), b(n), c(n);
  for (int i = 0; i < n; i++) {
    a[i] = y[(i + 1) % n] - y[i];
    b[i] = x[i] - x[(i + 1) % n];
    c[i] = -a[i] * x[i] - b[i] * y[i];
    double d = sqrt(a[i] * a[i] + b[i] * b[i]);
    a[i] /= d;
    b[i] /= d;
    c[i] /= d;
  }
  int c1, c2, c3;
  scanf("%d%d%d", &c1, &c2, &c3);
  c1--;
  c2--;
  c3--;
  vector<int> col(n);
  int cur = 0;
  for (int i = 0; i < n; i++) {
    if (i == c1 || i == c2 || i == c3) {
      cur++;
      cur %= 3;
    }
    col[i] = cur;
  }

  vector<int> l(n);
  vector<int> r(n);
  for (int i = 0; i < n; i++) {
    r[i] = (i + 1) % n;
    l[i] = (i + n - 1) % n;
  }

  double ansx, ansy;

  auto calc = [&](int i, int j, int k) {
    double a1 = a[i] - a[j];
    double b1 = b[i] - b[j];
    double c1 = c[i] - c[j];
    double a2 = a[i] - a[k];
    double b2 = b[i] - b[k];
    double c2 = c[i] - c[k];
    double x = (c2 * b1 - c1 * b2) / (a1 * b2 - a2 * b1);
    double y = (c2 * a1 - c1 * a2) / (a2 * b1 - a1 * b2);
    double d = -(a[i] * x + b[i] * y + c[i]);
    ansx = x;
    ansy = y;
    return d;
  };

  set<pair<double, int>> events;
  vector<double> t(n);
  vector<decltype(events)::iterator> iters(n);
  for (int i = 0; i < n; i++) {
    int ll = l[i];
    int rr = r[i];
    t[i] = calc(i, ll, rr);
    iters[i] = events.insert({t[i], i}).first;
  }

  vector<int> cnt(3);
  for (int i = 0; i < n; i++) {
    cnt[col[i]]++;
  }

  while (true) {
    auto id = events.begin()->second;
    db(id);
    events.erase(events.begin());
    cnt[col[id]]--;
    if (cnt[col[id]] == 0) {
      calc(id, l[id], r[id]);
      cout << "Yes\n";
      cout.precision(20);
      cout << fixed << ansx << " " << ansy << "\n";
      return 0;
    }
    for (int i : {l[id], r[id]}) {
      events.erase(iters[i]);
    }
    l[r[id]] = l[id];
    r[l[id]] = r[id];
    for (int i : {l[id], r[id]}) {
      int ll = l[i];
      int rr = r[i];
      t[i] = calc(i, ll, rr);
      iters[i] = events.insert({t[i], i}).first;
    }
  }

  return 0;
}
