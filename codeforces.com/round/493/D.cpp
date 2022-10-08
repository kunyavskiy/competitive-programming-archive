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

#pragma GCC optimize ("Ofast,tree-vectorize")


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

int cnk[200][200];


int a[4100];
int b[4100];
int dp[4100];
int ndp[4100];


vector<int> get_tree2(int n, int k) {
  for (int i = 0; i < n - 1; i++) {
    scanf("%d %d", &a[i], &b[i]);
    --a[i], --b[i];
  }
  vector<int> ans(k / 2 + 1);
  for (int i = 0; i < n; i++) {
    memset(dp, 0, sizeof(int) * n);
    dp[i] = 1;
    for (int j = 0; j <= k; j++) {
      if (j % 2 == 0) {
        add(ans[j / 2], dp[i]);
      }
      memset(ndp, 0, sizeof(int) * n);
      for (int e = 0; e < n - 1; e++) {
        add(ndp[a[e]], dp[b[e]]);
        add(ndp[b[e]], dp[a[e]]);
      }
      memcpy(dp, ndp, sizeof(int) * n);
    }
  }
  return ans;
}


vector<int> dfs(const vector<vector<int>>& g, vector<int> &ans, int v, int p) {
  vector<int> cur(ans.size());
  cur[0] = 1;
  for (int u : g[v]) {
    if (u == p) continue;
    vector<int> t = dfs(g, ans, u, v);
    for (int i = 1; i < (int)ans.size(); i++) {
      add(cur[i], t[i-1]);
    }
  }
  vector<vector<int>> cur2(ans.size(), vector<int>(ans.size()));
  cur2[1] = cur;
  for (int t = 1; t < (int)ans.size(); t++) {
    for (int i = 1; i < (int) ans.size(); i++) {
      for (int j = 1; j <= i; j++) {
        add(cur2[t][i], mul(cur2[t - 1][i - j], cur[j]));
      }
    }
  }
  add(ans[0], 1);
  for (int i = 1; i < (int)ans.size(); i++) {
    for (int c = 1; c <= i; c++) {
      int t = 0;
      for (int j = 0; j < c; j++) {
        if (i % (c / __gcd(c, j)) == 0)
        add(t, cur2[__gcd(c, j)][i / (c / __gcd(c, j))]);
      }
      t = mul(t, minv(c));
      add(ans[i], t);
    }
  }
  return cur2;
}

vector<int> get_tree(int n, int k) {
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  vector<int> ans(k / 2 + 1);
  dfs(g, ans, 0, -1);
  for (int i = 1; i < (int)ans.size(); i++) {
    for (int j = 2 * i; j < (int)ans.size(); j += i) {
      sub(ans[j], ans[i]);
    }
  }

  for (int i = 1; i < (int)ans.size(); i++) {
    ans[i] = mul(ans[i], 2 * i);
  }

  for (int i = 1; i < (int)ans.size(); i++) {
    for (int j = 2 * i; j < (int)ans.size(); j += i) {
      add(ans[j], ans[i]);
    }
  }

  return ans;
}


int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  cnk[0][0] = 1;
  for (int i = 0; i < 200; i++) {
    for (int j = 0; j < 200; j++) {
      if (i) add(cnk[i][j], cnk[i - 1][j]);
      if (i && j) add(cnk[i][j], cnk[i - 1][j - 1]);
    }
  }

  int n1, n2, k;
  while (scanf("%d%d%d", &n1, &n2, &k) == 3) {
    vector<int> v1 = get_tree(n1, k);
    vector<int> v2 = get_tree(n2, k);
    if (k % 2 == 1) {
      printf("0\n");
      continue;
    }
    k /= 2;
    int ans = 0;
    for (int i = 0; i <= k; i++) {
      add(ans, mul(mul(v1[i], v2[k - i]), cnk[2*k][2*i]));
    }
    printf("%d\n", ans);
  }

  return 0;
}
