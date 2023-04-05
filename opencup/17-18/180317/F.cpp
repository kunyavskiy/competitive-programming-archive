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
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  vector<int> a(m);
  vector<int> b(m);
  for (int i = 0; i < m; i++) {
    scanf("%d%d", &a[i], &b[i]);
    a[i]--;
    b[i]--;
  }

  vector<ll> fact(n + 1);
  fact[0] = 1;
  for (int i = 1; i <= n; i++) {
    fact[i] = fact[i - 1] * i;
  }
  vector<ll> d((1 << n));
  d[0] = 1;

  ll res = 0;

  for (int x = 0; x < (1 << n); x++) {
    int q[n];
    for (int i = 0; i < n; i++) {
      q[i] = (x >> i) & 1;
    }
    for (int i = 0; i < m; i++) {
      if (q[a[i]] > q[b[i]]) {
        swap(q[a[i]], q[b[i]]);
      }
    }
    bool ok = true;
    for (int i = 0; i < n - 1; i++) {
      if (q[i] > q[i + 1]) {
        ok = false;
        break;
      }
    }

//    for (int i = 0; i < n; i++) {
//      cout << q[i] << " ";
//    }
//    cout << x << " " << ok << "\n";

    if (ok) {
      for (int j = 0; j < n; j++) {
        if (!(x & (1 << j))) {
          int xx = x | (1 << j);
          d[xx] += d[x];
        }
      }
    } else {
      int c = 0;
      for (int j = 0; j < n; j++) {
        if (!(x & (1 << j))) {
          c++;
        }
      }
      res += d[x] * fact[c];
    }
  }

  cout << res << "\n";

  return 0;
}
