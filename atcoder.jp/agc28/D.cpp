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

const int MAXN = 1010;

const int MOD = 1000000007;

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

int ways[MAXN];

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  ways[0] = 1;
  ways[1] = 0;
  for (int i = 2; i < MAXN; i++) {
    ways[i] = mul(ways[i - 2], i - 1);
  }

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    n *= 2;
    vector<int> a(m), b(m);
    for (int i = 0; i < m; i++) {
      scanf("%d%d", &a[i], &b[i]);
      a[i]--, b[i]--;
      a[i] *= 2;
      b[i] *= 2;
    }

    int ans = ways[n - 2 * m];
    eprintf("tot = %d\n", ans);


    for (int i = 1; i < 2 * n; i += 2) {
      for (int j = i + 2; j < 2 * n; j += 2) {
        int inside, outside;
        inside = (j - i) / 2;
        outside = n - inside;
        bool fail = false;
        for (int k = 0; k < m; k++) {
          bool inside_a = i <= a[k] && a[k] <= j;
          bool inside_b = i <= b[k] && b[k] <= j;
          if (inside_a && inside_b) {
            inside -= 2;
          } else if (!inside_a && !inside_b) {
            outside -= 2;
          } else {
            fail = true;
          }
        }
        assert(inside >= 0 && outside >= 0);
        if (!fail) {
          int cur = mul(ways[inside], ways[outside]);
          eprintf("%d ways to split at (%d, %d)\n", cur, i, j);
          add(ans, cur);
        }
      }
    }
    printf("%d\n", ans);
  }

  return 0;
}
