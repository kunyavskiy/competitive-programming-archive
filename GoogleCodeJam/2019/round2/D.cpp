#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

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

vector<vector<int>> g;
vector<vector<int>> gr;
vector<bool> used;
vector<int> ts;
vector<int> comp;

void dfs(int v, vector<vector<int>> &g, vector<bool>& used, vector<int> &ts) {
  if (used[v]) return;
  used[v] = true;
  for (int u : g[v]) {
    dfs(u, g, used, ts);
  }
  ts.push_back(v);
}

void dfs_comp(int v, int c, vector<int>& cl) {
  if (comp[v] != -1) return;
  cl.push_back(v);
  comp[v] = c;
  for (int u : g[v]) {
    dfs_comp(u, c, cl);
  }
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

void solve() {
  int n;
  scanf("%d", &n);
  g = gr = vector<vector<int>>(n);
  for (int i = 0; i < n; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    g[i].push_back(a);
    g[i].push_back(b);
    gr[a].push_back(i);
    gr[b].push_back(i);
  }
  vector<int> have(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &have[i]);
  }
  used = vector<bool>(n);
  ts.clear();
  dfs(0, gr, used, ts);
  {
    vector<int> tmp;
    vector<bool> active(n);
    for (int i = 0; i < n; i++) {
      if (have[i] > 0) {
        dfs(i, g, active, tmp);
      }
    }
    for (int i = 0; i < n; i++) {
      used[i] = used[i] && active[i];
    }
  }
  for (int i = 0; i < n; i++) {
    if (!used[i]) {
      g[i].clear();
      gr[i].clear();
    }
    gr[i].erase(remove_if(gr[i].begin(), gr[i].end(), [&](int x) { return !used[x];}), gr[i].end());
    g[i].erase(remove_if(g[i].begin(), g[i].end(), [&](int x) { return !used[x];}), g[i].end());
  }
  used = vector<bool>(n);
  ts.clear();
  dfs(0, gr, used, ts);
  comp = vector<int>(n, -1);
  reverse(ts.begin(), ts.end());
  int cc = 0;
  for (int x : ts) {
    if (comp[x] == -1) {
      vector<int> cl;
      dfs_comp(x, cc++, cl);
      if (cl.size() > 1 || find(g[cl[0]].begin(), g[cl[0]].end(), cl[0]) != g[cl[0]].end()) {
        for (int u : cl) {
          if (g[u].size() > 1) {
            printf("UNBOUNDED\n");
            return;
          }
        }
      }
    }
  }
  g[0].clear();
  ts.clear();
  used = vector<bool>(n);
  dfs(0, gr, used, ts);

  for (int x : ts) {
    for (int u : g[x]) {
      add(have[u], have[x]);
    }
  }

  printf("%d\n", have[0]);
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
