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

ll solve2(ll pp, ll m){
    if (pp == 2) return 2;
    if (m == pp / 4) return 4 * solve2(pp / 2, m % (pp / 2));
    if (m == 3 * pp / 4) return 0;
    return 2 * solve2(pp / 2, m % (pp / 2));
}

ll solvep1(ll pp, ll p, ll m) {
    if (m == 0) {
        ll count = 0;
        ll q = 1;
        while (q < pp) {
            count += pp / q - 1;
            q *= p;
        }
        return pp * 1LL * pp - count * (p - 1) * (pp / p);
    }

    int deg = 0;
    while (m % p == 0) {
        m /= p;
        deg++;
    }
    return (p - 1) * (pp / p) * (deg + 1);
}

ll count(ll pp, ll p) {
    ll res = 0;
    for (ll q = 1; q < pp; q *= p * p) {
        res += pp / q;
        res -= pp / q / p;
    }
#ifdef LOCAL
    ll res2 = 0;
    for (int i = 1; i < pp; i++) {
        int d = 0;
        int j = i;
        while (j % p == 0) {
            d++;
            j /= p;
        }
        if (d % 2 == 0) res2++;
    }
    eprintf("pp = %lld, p = %lld, res2 = %lld, res = %lld\n", pp, p, res2, res);
    assert(res2 == res);
#endif
    return res;
}

ll solvep3(ll pp, ll p, ll a) {
    if (a == 0) {
        if (pp == 1 || pp == p) return 1;
        return solvep3(pp / p / p, p, a) * p * p;
    }
    int d = 0;
    while (a % p == 0) {
        a /= p;
        d++;
    }
    if (d % 2 == 1) return 0;
    return (pp * 1LL * pp - solvep3(pp, p, 0)) / count(pp, p);
}


int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &m, &n) == 2) {
#ifdef LOCAL
      eprintf("==== m = %d\n", m);
      vector<int> anss(m);
      for (int i = 0; i < m; i++) {
          for (int j = 0; j < m; j++) {
              anss[(i * i + j * j) % m]++;
          }
      }
#endif
      vector<pair<int, int>> ps;
      for (int i = 2; i * i <= m; i++) {
          if (m % i == 0) {
              int t = 1;
              while (m % i == 0) {
                  m /= i;
                  t *= i;
              }
              ps.emplace_back(t, i);
          }
      }
      if (m > 1) {
          ps.emplace_back(m, m);
      }

      for (int i = 0; i < n; i++) {
          int a;
          scanf("%d", &a);
          long long ans = 1;
          for (auto [pp, p] : ps) {
              if (p == 2) {
                  ans *= solve2(pp, a % pp);
              } else if (p % 4 == 1){
                  ans *= solvep1(pp, p, a % pp);
              } else {
                  ans *= solvep3(pp, p, a % pp);
              }
          }
#ifdef LOCAL
          eprintf("%d %lld %d\n", a, ans, anss[a]);
          assert(ans == anss[a]);
#endif
          printf("%lld ", ans);
      }
      printf("\n");
  }

  return 0;
}
