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

const int MAXN = 100100;

vector<int> g[MAXN];
int used[MAXN];
bool ok;
int p[3];

void dfs(int v, int c) {
  if (used[v] != 0) {
    if (used[v] != c) ok = false;
    return;
  }
  used[v] = c;
  p[c]++;
  for (int u : g[v]) {
    dfs(u, 3 - c);
  }
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  ll es = -m;

  for (int i = 0; i < n; i++) {
    if (used[i] == 0) {
      ok = true;
      p[1] = p[2] = 0;
      dfs(i, 1);
      if (ok) {
        es += p[1] * 1LL * p[2];
      } else {
        es += (p[1] + p[2]) * 1LL * (p[1] + p[2] - 1) / 2;
      }
    }
  }

  printf("%lld\n", es);


  return 0;
}
