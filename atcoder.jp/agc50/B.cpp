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

const int MAXN = 510;

int dp1[MAXN][MAXN];
int dp2[MAXN][MAXN][3];
int dp3[MAXN][MAXN][3];
int a[MAXN];

int calc1(int l, int r);
int calc2(int l, int r, int rem);
int calc3(int l, int r, int rem);

int calc1(int l, int r) {
  int& ans = dp1[l][r];
  if (ans != numeric_limits<int>::min()) return ans;
  if (l == r) return ans = 0;
  ans = max(ans, calc1(l + 1, r));
  ans = max(ans, a[l] + calc2(l + 1, r, l % 3));
  return ans;
}

int calc2(int l, int r, int rem) {
  int& ans = dp2[l][r][rem];
  if (ans != numeric_limits<int>::min()) return ans;
  ans = numeric_limits<int>::min() / 3;
  for (int i = l; i < r; i++) {
    if (i % 3 == (rem + 1) % 3) {
      ans = max(ans, calc1(l, i) + a[i] + calc3(i + 1, r, rem));
    }
  }
  return ans;
}

int calc3(int l, int r, int rem) {
  int& ans = dp3[l][r][rem];
  if (ans != numeric_limits<int>::min()) return ans;
  ans = numeric_limits<int>::min() / 3;
  for (int i = l; i < r; i++) {
    if (i % 3 == (rem + 2) % 3) {
      ans = max(ans, calc1(l, i) + a[i] + calc1(i + 1, r));
    }
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= n; j++) {
        dp1[i][j] = numeric_limits<int>::min();
        for (int k = 0; k < 3; k++) {
          dp2[i][j][k] = numeric_limits<int>::min();
          dp3[i][j][k] = numeric_limits<int>::min();
        }
      }
    }
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }

    printf("%d\n", calc1(0, n));
  }

  return 0;
}
