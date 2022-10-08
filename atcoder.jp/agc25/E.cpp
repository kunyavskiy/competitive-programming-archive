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

const int MAXN = 2100;

vector<int> g[MAXN];
int pp[MAXN];
vector<int> segs[MAXN];

void dfs(int v, int p) {
  pp[v] = p;
  for (int u : g[v]) {
    if (u != p) {
      dfs(u, v);
    }
  }
}


bool dfs2(int v, int p, int to, int id) {
  if (v == to) {
    return true;
  }
  for (int u : g[v]) {
    if (u != p) {
      if (dfs2(u, v, to, id)) {
        if (pp[v] == u) {
          segs[v].push_back(2 * id);
        } else {
          assert(pp[u] == v);
          segs[u].push_back(2 * id + 1);
        }
        return true;
      }
    }
  }
  return false;
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    for (int i = 0; i < n; i++) {
      g[i].clear();
      segs[i].clear();
    }

    for (int i = 1; i < n; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a, --b;
      g[a].push_back(b);
      g[b].push_back(a);
    }
    dfs(0, -1);

    vector<pair<int, int>> ps;

    for (int i = 0; i < m; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      --u, --v;
      dfs2(u, -1, v, i);
      ps.push_back({u, v});
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
      if (segs[i].size() == 1) {
        ans++;
        segs[i].clear();
      }
      if (segs[i].size()) {
        ans += 2;
      }
    }

    vector<bool> have[2];
    have[0] = have[1] = vector<bool>(n);
    vector<int> cnt(n);
    vector<vector<int>> rsegs(m);
    for (int i = 0; i < n; i++) {
      for (int u : segs[i]) {
        rsegs[u / 2].push_back(2 * i + (u % 2));
      }
    }

    for (int i = 0; i < n; i++) {
      cnt[i] = segs[i].size();
    }

    vector<int> val(m, -1);

    for (int it = 0; it < m; it++) {
      int only = -1;
      for (int i = 0; i < n; i++) {
        if (cnt[i] == 1) {
          only = i;
        }
      }

      int id = -1;
      if (only != -1) {
        for (int x : segs[only]) {
          if (val[x / 2] == -1) {
            assert(id == -1);
            id = x;
          }
        }
        assert(have[0][only] || have[1][only]);
        if (have[0][only]) {
          id ^= 1;
        }
        val[id / 2] = id % 2;
      } else {
        for (int i = 0; i < m; i++) {
          if (val[i] == -1) {
            id = 2 * i;
            val[i] = 0;
            break;
          }
        }
      }


      assert(id != -1);

//      eprintf("id = %d, set %d to %d\n", id, id / 2, val[id / 2]);

      for (int s : rsegs[id / 2]) {
        if (have[0][s / 2] && have[1][s / 2]) {
          continue;
        }
        int v = (s % 2) ^(id % 2);
        have[v][s / 2] = 1;
        if (have[0][s / 2] && have[1][s / 2]) {
          cnt[s / 2] = 0;
          continue;
        }
        cnt[s / 2]--;
        assert(cnt[s / 2] != 0);
      }

    }

    printf("%d\n", ans);

    for (int i = 0; i < m; i++) {
      if (val[i]) {
        printf("%d %d\n", ps[i].second + 1, ps[i].first + 1);
      } else {
        printf("%d %d\n", ps[i].first + 1, ps[i].second + 1);
      }
    }
  }

  return 0;
}
