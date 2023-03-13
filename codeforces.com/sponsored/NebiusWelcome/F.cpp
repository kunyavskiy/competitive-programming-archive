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
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n, m, q;
  while (scanf("%d%d%d", &n, &m, &q) == 3) {
      vector<vector<int>> g(n);
      for (int i = 0; i < m; i++) {
          int a, b;
          scanf("%d%d", &a, &b);
          --a, --b;
          g[a].push_back(b);
          g[b].push_back(a);
      }

      vector<int> d(n, n);
      vector<pair<int, int>> cd;
      vector<int> dsc(n + 1);
      dsc[n] = n;
      int cur_max = n;
      auto setd = [&](int v, int nd) {
          eprintf("d[%d] is now %d\n", v, nd);
          assert(d[v] > nd);
          dsc[d[v]]--;
          d[v] = nd;
          dsc[d[v]]++;
          while (dsc[cur_max] == 0) cur_max--;
      };
      auto bfs = [&]() {
          sort(cd.begin(), cd.end());
          queue<int> q;
          for (int id = 0; id <= (int)cd.size(); id++) {
              int nd;
              if (id == (int)cd.size()) {
                  nd = n;
              } else {
                  nd = cd[id].first;
              }
              while (!q.empty() && d[q.front()] < nd) {
                  int v = q.front();
                  assert(d[v] < nd);
                  q.pop();
                  for (int u : g[v]) {
                      if (d[u] > d[v] + 1) {
                          setd(u, d[v] + 1);
                          q.push(u);
                      }
                  }
              }
              if (id == (int)cd.size()) continue;
              auto [dd, v] = cd[id];
              assert(dd == nd);
              if (d[v] <= dd) continue;
              setd(v, dd);
              q.push(v);
          }
#ifdef LOCAL
          for (int i = 0; i < n; i++) {
              for (int j : g[i]) {
                  assert(abs(d[i] - d[j]) <= 1);
              }
          }
          assert(d[0] == 0);
#endif
          cd.clear();
      };
      cd.emplace_back(0, 0);
      bfs();
      printf("%d", cur_max);
      int tot = 0;
      for (int i = 0; i < q; i++) {
          int a, b;
          scanf("%d%d", &a, &b);
          --a, --b;
          g[a].push_back(b);
          g[b].push_back(a);
          if (d[a] > d[b] + 1) {
              cd.emplace_back(d[b] + 1, a);
              tot += d[a] - d[b] - 1;
          }
          if (d[b] > d[a] + 1) {
              cd.emplace_back(d[a] + 1, b);
              tot += d[b] - d[a] - 1;
          }

          if (tot >= cur_max / 2 - 5) {
              bfs();
              tot = 0;
          }
          printf(" %d", cur_max);
#ifdef LOCAL
          assert(cur_max == *max_element(d.begin(), d.end()));
#endif
      }
      printf("\n");

#ifndef LOCAL
      break;
#endif
  }

  return 0;
}
