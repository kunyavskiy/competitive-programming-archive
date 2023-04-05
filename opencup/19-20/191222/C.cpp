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

const int MOD = 998244353;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) {
  return mpow(x, MOD - 2);
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int N, k;
  while (scanf("%d%d", &N, &k) == 2) {
    int invk = minv(k);
    int deg_log = 0;
    {
      int deg = 1;
      while (deg <= k) {
        deg *= 2;
        deg_log++;
      }
    }
    vector<vector<int>> f(deg_log, vector<int>(N + 1));
    vector<vector<int>> f2(deg_log, vector<int>(N + 1));

    vector<int> f2_deg(deg_log);
    for (int i = 0; i < deg_log; i++) {
      f2_deg[i] = k & ((1 << (i + 1)) - 1);
    }

    vector<vector<int>> divs(N + 1);
    for (int i = 1; i <= N; i++) {
      for (int j = i; j <= N; j += i) {
        divs[j].push_back(i);
      }
    }

    scanf("%*d");
    for (int deg = 0; deg < deg_log; deg++) {
      f[deg][1] = f2[deg][1] = 1;
    }

    printf("%d", 1);

    for (int n = 2; n <= N; n++) {
      for (int deg = 1; deg < deg_log; deg++) {
        for (int d : divs[n]) {
          add(f[deg][n], mul(f[deg - 1][d], f[deg - 1][n / d]));
        }
        if (f2_deg[deg] != f2_deg[deg - 1]) {
          for (int d : divs[n]) {
            add(f2[deg][n], mul(f2[deg - 1][d], f[deg][n / d]));
          }
        } else {
          f2[deg][n] = f2[deg - 1][n];
        }
      }
      int x;
      scanf("%d", &x);
      sub(x, f2[deg_log - 1][n]);
      x = mul(x, invk);
      printf(" %d", x);
      for (int deg = 0; deg < deg_log; deg++) {
        add(f[deg][n], mul(x, 1 << deg));
        add(f2[deg][n], mul(x, f2_deg[deg]));
      }
//      eprintf("%d %d %d %d\n", f[0][n], f[1][n], f2[0][n], f2[1][n]);
    }
    printf("\n");
  }

  return 0;
}
