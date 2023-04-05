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

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<int> e(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &e[i]);
      --e[i];
    }

    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a, --b;
      g[a].push_back(b);
      g[b].push_back(a);
    }
    for (int my = 0; my < 3; my++) {
      int a = (my + 1) % 3;
      int b = (my + 2) % 3;
      vector<int> compa(n, -1), compb(n, -1);
      auto dfs = [&](int v, int dis, vector<int> &comp, int cc, auto &dfs) {
        if (comp[v] != -1) return;
        comp[v] = cc;
        for (int u : g[v]) {
          if (e[u] == dis) continue;
          dfs(u, dis, comp, cc, dfs);
        }
      };

      int cca = 0, ccb = 0;
      for (int i = 0; i < n; i++) {
        if (e[i] == my) {
          if (compa[i] == -1) dfs(i, b, compa, cca++, dfs);
          if (compb[i] == -1) dfs(i, a, compb, ccb++, dfs);
        }
      }

      vector<vector<pair<int, int>>> gg(cca);
      for (int i = 0; i < n; i++) {
        if (e[i] == my) {
          gg[compa[i]].emplace_back(compb[i], i);
        }
      }
      vector<int> mt(ccb, -1);
      vector<int> mte(ccb, -1);
      vector<int> bmt(cca, -1);
      vector<int> bmte(cca, -1);
      vector<int> used(cca, -1);
      int usedptr = 0;
      auto kuhn = [&](int v, auto &kuhn) {
        if (used[v] == usedptr) return false;
        used[v] = usedptr;
        for (auto [u, e] : gg[v]) {
          if (mt[u] == -1 || kuhn(mt[u], kuhn)) {
            bmt[v] = u; mt[u] = v;
            bmte[v] = mte[u] = e;
            return true;
          }
        }
        return false;
      };
      for (int i = 0; i < cca; i++) {
        for (auto [u, e] : gg[i]) {
          if (mt[u] == -1) {
            bmt[i] = u; mt[u] = i;
            bmte[i] = mte[u] = e;
            break;
          }
        }
      }
      for (int i = 0; i < cca; i++) {
        if (bmt[i] == -1) {
          if (kuhn(i, kuhn)) {
            usedptr++;
          }
        }
      }

      vector<int> ans;
      for (int i = 0; i < cca; i++) {
        for (auto [u, e] : gg[i]) {
          if (bmt[i] == -1) bmt[i] = u, bmte[i] = e;
          if (mt[u] == -1) mt[u] = i, mte[u] = e;
        }
      }
      ans.insert(ans.end(), mte.begin(), mte.end());
      ans.insert(ans.end(), bmte.begin(), bmte.end());
      sort(ans.begin(), ans.end());
      ans.erase(unique(ans.begin(), ans.end()), ans.end());
      printf("%d", (int)ans.size());
      for (int x : ans) printf(" %d", x + 1);
      printf("\n");
    }
  }

  return 0;
}
