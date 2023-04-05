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

const int MAXF = 310 * 310;

int f[MAXF];
int invf[MAXF];

int cnk(int n,int k) {
  return mul(f[n], mul(invf[k], invf[n - k]));
}

struct edge {
  int to;
  int ways;
  int len;

  edge() = default;
  edge(int to, int ways, int len) : to(to), ways(ways), len(len) {}
};

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  f[0] = invf[0] = 1;
  for (int i = 1; i < MAXF; i++) {
    f[i] = mul(f[i - 1], i);
  }
  invf[MAXF - 1] = minv(f[MAXF - 1]);
  for (int i = MAXF - 2; i >= 0; i--) {
    invf[i] = mul(invf[i + 1], i + 1);
  }


  int k, n;
  while (scanf("%d%d", &k, &n) == 2) {
    n += 2;
    int tot_ans = 0;
    vector<vector<int>> v(k, vector<int>(n));
    vector<vector<int>> pos(k, vector<int>(n));
    for (int i = 0; i < k; i++) {
      for (int j = 1; j < n - 1; j++) {
        scanf("%d", &v[i][j]);
        pos[i][v[i][j]] = j;
      }
      v[i][0] = pos[i][0] = 0;
      v[i][n - 1] = pos[i][n - 1] = n - 1;
    }
    for (int l = 0; l < k; l++) {
      vector<vector<edge>> g(n);
      for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
          g[v[l][i]].emplace_back(v[l][j], 1, j - i - 1);
        }
      }
      for (int r = l + 1; r < k; r++) {
        for (int i = 0; i < n; i++) {
          vector<edge> ne;
          for (const edge&e : g[i]) {
            if (pos[r][e.to] > pos[r][i]) {
              int between = pos[r][e.to] - pos[r][i] - 1;
              ne.emplace_back(e.to, mul(e.ways, cnk(e.len + between,between)), e.len + between);
            }
          }
          g[i] = std::move(ne);
        }
        vector<int> ans(n);
        ans[n - 1] = MOD - 1;
        for (int i = n - 2; i >= 0; i--) {
          int id = v[l][i];
          for (const edge &e: g[id]) {
            sub(ans[id], mul(mul(e.ways, f[r - l + 1]), ans[e.to]));
          }
        }
        add(tot_ans, mul(ans[0], invf[r - l + 1]));
      }
    }
    printf("%d\n", tot_ans);
  }

  return 0;
}
