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


void solve() {
  int n;
  scanf("%d", &n);
  vector<int> fs(n + 1), ifs(n + 1);
  fs[0] = ifs[0] = 1;
  for (int i = 1; i <= n; i++) {
    fs[i] = mul(fs[i - 1], i);
    ifs[i] = minv(fs[i]);
  }
  vector<int> p(n, -1);
  vector<int> st;
  int ans = 1;
  for (int i = 0; i < n; i++) {
    int v;
    scanf("%d", &v);
    --v;

    if (v > (int)st.size()) {
      ans = 0;
      v = st.size();
    }

    int last = -1;
    while ((int) st.size() > v) {
      last = st.back();
      st.pop_back();
    }
    if (last != -1) {
      p[last] = i;
    }

    if (!st.empty()) {
      p[i] = st.back();
    } else {
      p[i] = -1;
    }
    st.push_back(i);
  }

  vector<vector<int>> g(n);
  for (int i = 0; i < n; i++) {
    if (p[i] == -1) {
      assert(i == st[0]);
    } else {
      g[p[i]].push_back(i);
    }
  }

  auto dfs = [&](int v, auto dfs) -> int {
    int sz = 0;
    for (int u : g[v]) {
      int s = dfs(u, dfs);
      ans = mul(ans, ifs[s]);
      sz += s;
    }
    ans = mul(ans, fs[sz]);
    return sz + 1;
  };
  assert(p[st[0]] == -1);
  dfs(st[0], dfs);
  printf("%d\n", ans);
}


int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  TIMESTAMP(PreCalc);

  char buf[1000];
  int testNum;
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d", &testNum);

  for (int testId = 1; testId <= testNum; testId++) {
    if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
      TIMESTAMPf("Test %d", testId);
    printf("Case #%d: ", testId);
    solve();
  }

  TIMESTAMP(end);
  return 0;
}
