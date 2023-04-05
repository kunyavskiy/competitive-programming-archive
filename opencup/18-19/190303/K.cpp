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

ll INF = 1e18;

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  vector<int> r(n);
  vector<int> c(n);
  vector<int> a(n);
  vector<int> x(n);
  vector<int> p(n);

  for (int i = 0; i < n; i++) {
    int aa;
    int bb;
    scanf("%d%d%d%d%d", &r[i], &c[i], &aa, &bb, &p[i]);
    a[i] = __gcd(aa, bb);
    x[i] = (aa / a[i] + bb / a[i]) % 2;

//    cout << a[i] << " " << x[i] << endl;
  }

  if (r[0] == 0 && c[0] == 0) {
    cout << 0 << endl;
    return 0;
  }

  vector<int> div;
  for (int aa : a) {
    for (int i = 1; i * i <= a[0]; i++) {
      if (aa % i == 0) {
        div.push_back(i);
        div.push_back(aa / i);
      }
    }
  }

  sort(div.begin(), div.end());
  div.erase(unique(div.begin(), div.end()), div.end());
  reverse(div.begin(), div.end());

  vector<vector<ll>> d(2, vector<ll>(div.size(), INF));
  
  for (int i = 0; i < n; i++) {
    if (r[i] == r[0] && c[i] == c[0]) {
      int l = 0;
      int r = div.size();
      while (r > l + 1) {
        int m = (l + r) / 2;
        if (div[m] >= a[i]) {
          l = m;
        } else {
          r = m;
        }
      }
      d[x[i]][l] = p[i];
    }
  }

  ll res = INF;

  for (int i = 0; i < (int)div.size(); i++) {
    int a1 = div[i];
    for (int x1 = 0; x1 < 2; x1++) {
      if (d[x1][i] == INF) continue;

      {
        bool ok = true;
        int dr = abs(r[0]);
        int dc = abs(c[0]);
        if (dr % a1 != 0) ok = false;
        if (dc % a1 != 0) ok = false;
        if (x1 == 0 && ((dr / a1 + dc / a1) % 2 == 1)) ok = false;
        if (ok) {
          res = min(res, d[x1][i]);
        }
      }

      for (int j = 0; j < n; j++) {

        {
          int dr = abs(r[j] - r[0]);
          int dc = abs(c[j] - c[0]);
          if (dr % a1 != 0) continue;
          if (dc % a1 != 0) continue;
          if (x1 == 0 && ((dr / a1 + dc / a1) % 2 == 1)) continue;
        }

        int a2 = a[j];
        int x2 = x[j];

        int aa = __gcd(a1, a2);
        int xx = 0;

        if (x1 && ((a1 / aa) % 2)) xx = 1;
        if (x2 && ((a2 / aa) % 2)) xx = 1;

        int l = 0;
        int r = div.size();
        while (r > l + 1) {
          int m = (l + r) / 2;
          if (div[m] >= aa) {
            l = m;
          } else {
            r = m;
          }
        }

        d[xx][l] = min(d[xx][l], d[x1][i] + p[j]);
      }
    }
  }

  cout << (res == INF ? -1 : res) << endl;

  return 0;
}
