#include <iostream>
#include <fstream>
#include <vector>
#include <set>

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
vector<int> c;

vector<multiset<int>> s;

ll ans;

void dfs(int v) {
  s[v].insert(v);
  for (int u : g[v]) {
    dfs(u);
    if (s[v].size() < s[u].size()) {
      s[v].swap(s[u]);
    }
    for (int x: s[u]) {
      s[v].insert(x);
    }
    s[u].clear();
  }

  while (!s[v].empty() && c[v] > 0) {
    c[v]--;
    ans += *s[v].rbegin();
    s[v].erase(--s[v].end());
  }
}

void solve() {
  int n, m, a, b;
  scanf("%d%d%d%d", &n, &m, &a, &b);
  g = vector<vector<int>>(n);
  for (int i = 1; i < n; i++) {
    int p;
    scanf("%d", &p);
    g[p].push_back(i);
  }
  c = vector<int>(n);
  for (int i = 0; i < m; i++) {
    int x = (a * 1LL * i + b) % n;
    c[x] += 1;
  }
  s = vector<multiset<int>>(n);
  ans = 0;
  dfs(0);
  printf("%lld\n", ans);
}


int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
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
