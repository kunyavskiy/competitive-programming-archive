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
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  int n, k, m;
  while (scanf("%d%d%d", &n, &k, &m) == 3) {
    --k;
    vector<ll> v(1 << n, 0);
    for (int i = 0; i < n; i++) {
      v[1 << i] = 1LL << m;
    }

    for (int i = 0; i < m; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a, --b;
      for (int j = 0; j < (1 << n); j++) {
        if (((j >> a) & 1) != ((j >> b) & 1)) {
          ll half = v[j] / 2;
          assert(v[j] % 2 == 0);
          v[j] -= half;
          v[j | (1 << a) | (1 << b)] += half;
        }
      }
    }

    ll total = 0;
    vector<ll> ill(n);
    for (int i = 0; i < (1 << n); i++) {
      if (i & (1 << k)) {
        total += v[i];
        for (int j = 0; j < n; j++) {
          if (i & (1 << j)) {
            ill[j] += v[i];
          }
        }
      }
    }
    for (int i = 0; i < n; i++) {
      ll g = __gcd(total, ill[i]);
      printf("%lld/%lld\n", ill[i] / g, total / g);
    }
  }


  return 0;
}
