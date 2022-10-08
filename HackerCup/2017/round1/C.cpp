//#include <iostream>
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
#include <stdarg.h>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if (_WIN32 || __WIN32__)
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "C"

typedef long long ll;
typedef long double ld;

const int MAXN = 200;
const int INF = (int) 1e9;

int g[MAXN][MAXN];


void solve() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      g[i][j] = INF * (i != j);
    }
  for (int i = 0; i < m; i++) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    --a, --b;
    g[a][b] = min(g[a][b], c);
    g[b][a] = min(g[b][a], c);
  }
  for (int q = 0; q < n; q++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        g[i][j] = min(g[i][j], g[i][q] + g[q][j]);
      }

  vector<int> s(k + 1), t(k + 1);
  for (int i = 1; i <= k; i++) {
    scanf("%d%d", &s[i], &t[i]);
    --s[i], --t[i];
  }

  for (int i = 1; i <= k; i++) {
    if (g[s[i]][t[i]] == INF || g[0][s[i]] == INF) {
      printf("-1\n");
      return;
    }
  }

  // ans[0] = in t[i-1];
  // ans[1] = in s[i];
  int ans0, ans1;
  ans0 = INF;
  ans1 = g[0][s[1]];

  for (int i = 1; i < k; i++) {
    int f1 = t[i-1];
    int f2 = s[i];
    int ne = s[i+1];
    int cur = t[i];
    int nans0 = min(ans0 + g[f1][ne] + g[ne][cur], ans1 + g[f2][ne] + g[ne][cur]);
    int nans1 = min(ans0 + g[f1][cur] + g[cur][ne], ans1 + g[f2][cur] + g[cur][ne]);
    ans0 = nans0;
    ans1 = nans1;
  }

  printf("%d\n", min(ans0 + g[t[k-1]][t[k]], ans1 + g[s[k]][t[k]]));
}

int main() {
  freopen(TASKNAME".in", "r", stdin);
  freopen(TASKNAME".out", "w", stdout);

  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    printf("Case #%d: ", i);
    solve();
  }

  return 0;
}
