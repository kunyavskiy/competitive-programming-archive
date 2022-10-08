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

struct dsu {
  vector<int> h;
  vector<int> parent;
  vector<int> p;
  vector<int> size;
  vector<int> ans_size;
  vector<int> child_size;
  vector<int> child_cnt;
  vector<bool> in_ans;
  ll result;

  dsu(vector<int> h_, vector<int> parent) :
    h(std::move(h_)), parent(std::move(parent)), p(h.size()), size(h.size()),
    ans_size(h.size()), child_size(h.size()), child_cnt(h.size()), in_ans(h.size()), result(0) {
    for (int i = 0; i < (int) h.size(); i++) {
      size[i] = 1;
      p[i] = i;
    }
  }

  int get(int x) {
    if (x == p[x]) return x;
    return p[x] = get(p[x]);
  }

  ll get_ans(int x) {
    return (h[x] - in_ans[x]) * 1LL * ans_size[x];
  }
  ll get_child_ans(int x) {
    if (in_ans[x] || child_cnt[x] == 1) return 0;
    return -child_size[x];
  }

  void add_size(int x, int s) {
    x = get(x);
    result -= get_ans(x);
    ans_size[x] += s;
    result += get_ans(x);
  }


  void set_in_ans(int x) {
    assert(x == get(x) && !in_ans[x]);
    result -= get_child_ans(x);
    result -= get_ans(x);
    in_ans[x] = true;
    result += get_ans(x);
    result += get_child_ans(x);
  }
  void add_child(int x) {
    result -= get_child_ans(x);
    child_size[x]++;
    child_cnt[x]++;
    result += get_child_ans(x);
  }
  void add_child_size(int x, int s) {
    result -= get_child_ans(x);
    child_size[x] += s;
    result += get_child_ans(x);
  }

  void merge(int x, int y) {
    x = get(x);
    y = get(y);
    assert(get(parent[x]) == y);
    add_size(y, -size[x]);
    assert(!in_ans[parent[y]]);
    add_child_size(parent[y], size[x]);
    add_size(parent[parent[y]], size[x]);
    add_size(y,  ans_size[x]);
    add_size(x, -ans_size[x]);
    p[x] = y;
    size[y] += size[x];
  }

};

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
  vector<int> par(n + 2);
  vector<int> h(n + 2);
  vector<vector<int>> g(n + 2);
  for (int i = 0; i <= n; i++) {
    int x;
    if (i == n) {
      x = n + 1;
    } else {
      scanf("%d", &x);
      --x;
      if (x == -1) {
        x = n;
      }
    }
    g[x].push_back(i);
    par[i] = x;
  }
  function<void(int)> dfs = [&](int v) {
    for (int u : g[v]) {
      h[u] = h[v] + 1;
      dfs(u);
    }
  };
  dfs(n +1);

  dsu d(h, par);

  int ans = 1;
  ll cur = 0;
  for (int i = 0; i < n; i++) {
    d.add_size(par[d.get(par[i])], 1);
    d.set_in_ans(i);
    cur += h[i] - 1;
    if (par[i] < i) {
      d.merge(i, par[i]);
    } else {
      d.add_child(par[i]);
    }
    for (int u : g[i]) {
      if (u < i) {
        d.merge(u, i);
      }
    }
    ans = mul(ans, (cur - d.result) % MOD);
    eprintf("temp = %lld\n", cur - d.result);
    for (int i = 0; i < n + 2; i++) {
      eprintf("%d %d\n", d.ans_size[i], h[i]);
    }
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
