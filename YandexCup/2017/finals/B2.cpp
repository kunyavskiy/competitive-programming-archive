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

const int MAXN = 300100;

vector<int> g[MAXN];
int power[MAXN];
int size[MAXN];
int have_bad[MAXN];
int besth[MAXN];
ll sum[MAXN];
int n;

void dfs0(int v, int p) {
  sum[v] = power[v];
  size[v] = 1;
  for (int u : g[v]) {
    if (u != p) {
      dfs0(u, v);
      size[v] += size[u];
      sum[v] += sum[u];
    }
  }
}

void dfs1(int v, int p) {
  for (int u : g[v]) {
    if (u == p) continue;
    if (sum[u] < size[u]) {
      have_bad[v] = 2;
      return;
    }
    dfs1(u, v);
    if (have_bad[u] == 2) {
      have_bad[v] = 2;
      return;
    }
    int my_bad = have_bad[u] || (sum[0] - sum[u] < n - size[u]);
    if (my_bad && have_bad[v] == 1) {
      have_bad[v] = 2;
      return;
    }
    if (my_bad) {
      have_bad[v] = 1;
    }
    if (my_bad) {
      besth[v] = besth[u] + 1;
    } else if (!have_bad[v]) {
      besth[v] = max(besth[v], besth[u] + 1);
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
//  freopen("b.out", "w", stdout);
#endif

  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &power[i]);
  }
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  dfs0(0, -1);
  dfs1(0, -1);

  eprintf("%d %d\n", have_bad[0], besth[0]);

  if (have_bad[0] == 2 || 2 * n - 2 - besth[0] > sum[0]) {
    printf("-1\n");
  } else {
    printf("%d\n", 2 * n - 2 - besth[0]);
  }

  return 0;
}
