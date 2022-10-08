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

const int MAXN = 110000;

vector<int> g[MAXN];
vector<int> w[MAXN];

ll ans = 0;
int n;

int id1 = -1, id2 = -1;

int dfs(int v, int p = -1) {
  int size = 1;
  bool have_big = 0;
  for (int i = 0; i < (int)g[v].size(); i++) {
    if (g[v][i] == p) continue;
    int s = dfs(g[v][i], v);
    if (s > n / 2) have_big = true;
    size += s;
    ans += 2LL * w[v][i] * min(s, n - s);
  }
  if (n - size > n / 2) have_big = true;
  if (!have_big) {
    if (id1 == -1) {
      id1 = v;
    } else if (id2 == -1) {
      id2 = v;
    } else {
      assert(0);
    }
  }
  return size;
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  scanf("%d", &n);
  for (int i = 0; i < n - 1; i++) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    --a, --b;
    g[a].push_back(b); w[a].push_back(c);
    g[b].push_back(a); w[b].push_back(c);
  }

  dfs(0);

  assert(id1 != -1);
  eprintf("%d %d\n", id1, id2);
  if (id2 == -1) {
    ans -= *min_element(w[id1].begin(), w[id1].end());
  } else {
    int id = find(g[id1].begin(), g[id1].end(), id2) - g[id1].begin();
    assert(id != (int)g[id1].size());
    ans -= w[id1][id];
  }

  printf("%lld\n", ans);
  return 0;
}
