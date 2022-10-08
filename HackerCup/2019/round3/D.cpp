#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <functional>
#include <cassert>

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

void PreCalc() {
}

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
vector<int> t;
vector<int> tin;
vector<int> tout;
int timer;

int dfs(int v) {
  tin[v] = timer++;
  int minv = 1e9;
  int sminv = 1e9;
  for (int u : g[v]) {
    int tmp = dfs(u);
    if (tmp < minv) {
      swap(tmp,minv);
    }
    if (tmp < sminv) {
      swap(tmp, sminv);
    }
  }
  t[v] = min(sminv, v);
  tout[v] = timer;
  return min(minv, v);
}

struct Tree {
  vector<int> v;
  Tree(int n): v(n) {}

  void add(int x, int val) {
    while (x < (int)v.size()) {
      v[x] += val;
      x = x | (x + 1);
    }
  }
  int get(int x) {
    int ans = 0;
    while (x != -1) {
      ans += v[x];
      x = (x & (x + 1)) - 1;
    }
    return ans;
  }

  int get(int l, int r) {
    return get(r - 1) - get(l - 1);
  }
};

void solve() {
  int n;
  scanf("%d", &n);
  g = vector<vector<int>>(n);
  t = vector<int>(n);
  tin = vector<int>(n);
  tout = vector<int>(n);
  timer = 0;
  int root = -1;
  for (int i = 0; i < n; i++) {
    int x;
    scanf("%d", &x);
    --x;
    if (x == -1) {
      root = i;
    } else {
      g[x].push_back(i);
    }
  }
  assert(root != -1);

  dfs(root);
  int ans = 1;
  ll cur = 0;
  vector<vector<int>> order(n);
  for (int i = 0; i < n; i++) {
    order[t[i]].push_back(i);
  }

  Tree tree(n), tree2(n);

  for (int i = 0; i < n; i++) {
    for (int v : order[i]) {
      cur += tree.get(tin[v], tout[v]);
      tree2.add(tin[v], 1);
      tree2.add(tout[v], -1);
    }
    cur += tree2.get(0, tin[i] + 1);
    tree.add(tin[i], 1);
    ans = mul(ans, cur % MOD);
  }

  printf("%d\n", ans);
}



int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  PreCalc();
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
