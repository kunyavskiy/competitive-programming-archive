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
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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

vector<vector<int>> g;
vector<int> red;

vector<int> dfs(int v) {
  vector<int> ans;
  ans.resize(1);
  ans[0] = 1;
  for (int u : g[v]) {
    vector<int> r = dfs(u);
    int nmx = ans.size() + r.size() - 1;
    vector<int> nans(nmx);
    for (int i = 0; i < (int) ans.size(); i++) {
      for (int j = 0; j < (int) r.size(); j++) {
        add(nans[i + j], mul(ans[i], r[j]));
      }
    }
    ans = nans;
  }
  if (red[v]) {
    if (ans.size() < 2) ans.resize(2);
    add(ans[1], 1);
  } else {
    if (ans.size() < 1) ans.resize(1);
    add(ans[0], 1);
  }

//  eprintf("v = %d:", v);
//  for (int i : ans) {
//    eprintf(" %d", i);
//  }
//  eprintf("\n");
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    g = vector<vector<int>>(n);
    for (int i = 1; i < n; i++) {
      int p;
      scanf("%d", &p);
      --p;
      g[p].push_back(i);
    }
    red = vector<int>(n);
    for (int i = 0; i < m; i++) {
      int r;
      scanf("%d", &r);
      --r;
      red[r] = true;
    }
    vector<int> r = dfs(0);
    while (r.size() <= m) r.push_back(0);
    for (int i = 0; i <= m; i++) {
      printf("%d\n", r[i]);
    }
  }

  return 0;
}
