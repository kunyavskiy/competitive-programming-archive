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

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


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
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  int c, p;
  while (scanf("%d%d", &c, &p) == 2) {
      vector<vector<pair<int, double>>> g(c);
      vector<vector<pair<int, double>>> gr(c);
      vector<vector<pair<int, double>>> gp(c);
      for (int i = 0; i < c; i++) {
          int k;
          scanf("%d", &k);
          for (int j = 0; j < k; j++) {
              char t;
              int id;
              double pr;
              scanf(" %c%d:%lf", &t, &id, &pr);
              pr /= 100.0;
              --id;
              if (t == 'C') {
                  g[i].emplace_back(id, pr);
                  gr[id].emplace_back(i, pr);
              } else {
                  gp[i].emplace_back(id, pr);
              }
          }
      }

      vector<int> order;
      vector<int> used(c);
      auto dfs_o = [&](auto dfs, int v) -> void {
          used[v] = 1;
          for (auto [u, _]: g[v]) {
              if (!used[u]) {
                  dfs(dfs, u);
              }
          }
          order.push_back(v);
      };
      for (int i = 0; i < c; i++) {
          if (used[i] == 0) {
              dfs_o(dfs_o, i);
          }
      }
      vector<vector<int>> cs;
      auto dfs_c = [&](auto dfs, int v) -> void {
          cs.back().push_back(v);
          used[v] = 2;
          for (auto [u, _]: gr[v]) {
              if (used[u] != 2) {
                  dfs(dfs, u);
              }
          }
      };

      for (int i = 0; i < c; i++) {
          if (used[i] == 1) {
              cs.emplace_back();
              dfs_c(dfs_c, i);
          }
      }
      reverse(cs.begin(), cs.end());
      vector<vector<double>> ans(c);
      vector<int> id(c, -1);

      for (const auto &comp: cs) {
          int n = comp.size();
          vector<vector<double>> v(n, vector<double>(comp.size() + p));
          for (int i = 0; i < n; i++) {
              id[comp[i]] = i;
          }

          for (int i = 0; i < n; i++) {
              for (auto [u, part]: g[comp[i]]) {
                  if (id[u] >= 0) {
                      v[i][id[u]] -= part;
                  } else {
                      assert(id[u] == -2);
                      for (int j = 0; j < p; j++) {
                          v[i][n + j] += ans[u][j] * part;
                      }
                  }
              }
              for (auto [u, part] : gp[comp[i]]) {
                  v[i][n + u] += part;
              }
              v[i][i] += 1.0;
          }


          for (int i = 0; i < n; i++) {
              for (int j = i + 1; j < n; j++) {
                  if (abs(v[j][i]) > abs(v[i][i])) {
                      v[j].swap(v[i]);
                  }
              }
              double cc = v[i][i];
              for (int j = i; j < n + p; j++) {
                  v[i][j] /= cc;
              }
              for (int j = 0; j < n; j++) {
                  if (j != i) {
                      double ccc = v[j][i];
                      for (int k = i; k < n + p; k++) {
                          v[j][k] -= v[i][k] * ccc;
                      }
                  }
              }
          }

          for (int i = 0; i < n; i++) {
              ans[comp[i]] = vector<double>(v[i].begin() + n, v[i].end());
              id[comp[i]] = -2;
          }
      }


      for (int i = 0; i < c; i++) {
          for (int j = 0; j < p; j++) {
              printf("%.6f ", ans[i][j]);
          }
          printf("\n");
      }
  }

  return 0;
}
