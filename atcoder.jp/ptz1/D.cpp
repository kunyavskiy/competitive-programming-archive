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

int n;
vector<vector<int>> e;
vector<bool> used;

vector<int> cur;

void dfs(int v) {
  if (used[v]) return;
  used[v] = true;
  cur.push_back(v);
  for (int u : e[v]) {
    dfs(u);
  }
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    e = vector<vector<int>>(n);
    vector<int> cost(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &cost[i]);
    }
    for (int i = 0; i < m; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      e[a].push_back(b);
      e[b].push_back(a);
    }

    used = vector<bool>(n);

    ll ans = 0;
    int k = 0;
    vector<int> all;

    for (int i = 0; i < n; i++) {
      if (!used[i]) {
        cur.clear();
        dfs(i);
        sort(cur.begin(), cur.end(), [&cost](int a, int b) { return cost[a] < cost[b]; });
        ans += cost[cur[0]];
        k++;
        for (int j = 1; j < (int)cur.size(); j++) {
          all.push_back(cost[cur[j]]);
        }
      }
    }
    if (k == 1) {
      printf("0\n");
    } else if ((int)all.size() < k - 2) {
      printf("Impossible\n");
    } else {
      sort(all.begin(), all.end());
      for (int i = 0; i < k - 2; i++) {
        ans += all[i];
      }
      printf("%lld\n", ans);
    }
  }

  return 0;
}
