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
#include <random>

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

int MOD;

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

mt19937 rnd;

int solve(vector<int> &a, int p) {
  int x = rnd() % (a.size() - 1);
  int res2 = -1;
  for (int y = x + 1; y < x + 5 && y < (int)a.size(); y++) {
    MOD = p;
    int q = mul(a[y], minv(a[x]));
    int qr = minv(q);

    int res = 2;
    int nx = mul(a[y], q);

    for (int i = y + 1; i < (int) a.size(); i++) {
      if (a[i] == nx) {
        res++;
        nx = mul(nx, q);
      }
    }
    nx = mul(a[x], qr);
    for (int i = x - 1; i >= 0; i--) {
      if (a[i] == nx) {
        res++;
        nx = mul(nx, qr);
      }
    }
    res2 = max(res2, res);
  }
  if (res2 * 2 < (int) a.size()) return -1;
  return res2;
}

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  vector<vector<int>> a(n);
  vector<int> p(n);
  for (int i = 0; i < n; i++) {
    int m; scanf("%d%d", &m, &p[i]);
    a[i].resize(m);
    for (int j = 0; j < m; j++) {
      scanf("%d", &a[i][j]);
    }
  }

  vector<int> res(n, -1);
  while (clock() / (double)CLOCKS_PER_SEC < 1.5) {
    for (int i = 0; i < n; i++) {
      res[i] = max(res[i], solve(a[i], p[i]));
    }
  }
  for (int i = 0; i < n; i++) {
    cout << res[i] << "\n";
  }

  return 0;
}
