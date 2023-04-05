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

const ll MOD = 998244353;
int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif
  int n;
  ll x;
  scanf("%d%lld", &n, &x);
  if (x == 0) {
    ll res = 1;
    for (int i = 0; i < n; i++) {
      res = res * 2;
      res %= MOD;
    }
    res--;
    if (res < 0) res += MOD;
    cout << res << "\n";
    return 0;
  }
  x--;

  vector<ll> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &a[i]);
  }

  if (x == 0) {
    map<ll, int> aa;
    for (ll x : a) {
      aa[x]++;
    }
    ll res = 1;
    for (auto p : aa) {
      res *= (p.second + 1);
      res %= MOD;
    }
    res -= 1;
    if (res < 0) res += MOD;
    cout << res << "\n";
    return 0;
  }

  int last = 62;
  while (!((x >> last) & 1)) last--;

  map<ll, vector<ll>> cl;
  for (ll q: a) {
    cl[q >> (last + 1)].push_back(q);
  }

  ll res = 1;
  for (auto p : cl) {
    ll s = p.second.size() + 1;

    int nn = p.second.size();
    vector<ll> d(nn * 62);
    vector<vector<int>> g(2, vector<int>(nn * 62, -1));
    int m = 1;

    for (ll q: p.second) {
      if ((q >> last) & 1) continue;
//      cerr << "0-" << q << "\n";
      int c = 0;
      for (int j = 60; j >= 0; j--) {
        int b = (q >> j) & 1;
        if (g[b][c] == -1) {
          g[b][c] = m++;
        }
        c = g[b][c];
        d[c]++;
      }
    }

    for (ll q: p.second) {
      if (!((q >> last) & 1)) continue;
//      cerr << "1-" << q << "\n";
      int c = 0;
      for (int j = 60; j >= 0; j--) {
        int b = (q >> j) & 1;
        int bx = (x >> j) & 1;
        if (bx == 0 && g[1 - b][c] != -1) {
          s += d[g[1 - b][c]];
        }
        if (g[b ^ bx][c] == -1) {
          break;
        }
        c = g[b ^ bx][c];
      }
    }

    res *= s;
    res %= MOD;
  }

  res -= 1;
  if (res < 0) res += MOD;

  cout << res << "\n";

  return 0;
}
