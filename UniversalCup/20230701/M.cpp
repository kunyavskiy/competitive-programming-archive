#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x)                                                           \
  eprintf("[" #x "] Time : %.3lf s.\n",                                        \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...)                                                     \
  eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__,                            \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() { TIMESTAMPf("%s", what.data()); }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  n++;
  vector<int> a(n);
  vector<int> d(n);
  vector<vector<int>> byd(n);
  vector<vector<int>> chld(n);
  byd[0].push_back(0);
  vector<bool> isk(n);
  for (int i = 1; i < n; i++) {
    scanf("%d", &a[i]);
    d[i] = d[a[i]] + 1;
    byd[d[i]].push_back(i);
    chld[a[i]].push_back(i);
  }
  for (int i = 0; i < m; i++) {
    int v;
    scanf("%d", &v);
    isk[v] = true;
  }

  vector<int> val(n);
  vector<int> nxt(n, - 1);

  vector<int> lst_start(n);
  vector<int> lst_end(n);
  vector<int> lst_size(n);

  auto cmp_lists = [&](int i, int j) {
    int sti = lst_start[i];
    int stj = lst_start[j];
    while (sti != -1 && stj != -1) {
      if (val[sti] != val[stj]) {
        return val[sti] < val[stj];
      }
      sti = nxt[sti];
      stj = nxt[stj];
    }
    if (sti != stj) {
      return sti != -1;
    }
    return i < j;
  };


  int lfid = 0, rgid = 1;

  for (int curd = (int)byd.size() - 1; curd >= 0; curd--) {
    vector<vector<int>> children(26);
    vector<int> tot_lst_size(26);
    for (int v : byd[curd]) {
      vector<int> &c = chld[v];
      sort(c.begin(), c.end(),
           [&](int a, int b) { return cmp_lists(a, b); });
      for (int i = 0; i < (int)c.size(); i++) {
        children[i].push_back(c[i]);
        tot_lst_size[i] += lst_size[c[i]];
      }
    }
    int max_id = max_element(tot_lst_size.begin(), tot_lst_size.end()) - tot_lst_size.begin();

    auto renumerate = [&](const vector<int>& lst, bool left, int expected) {
      vector<int> all_id;
      for (int v : lst) {
        int st = lst_start[v];
        while (st != -1) {
          all_id.push_back(val[st]);
          st = nxt[st];
        }
      }
      assert((int)all_id.size() == expected);
      sort(all_id.begin(), all_id.end());
      all_id.erase(unique(all_id.begin(), all_id.end()), all_id.end());
      int from;
      if (left) {
        lfid -= all_id.size();
        from = lfid;
      } else {
        from = rgid;
        rgid += all_id.size();
      }
      for (int v : lst) {
        int st = lst_start[v];
        while (st != -1) {
          val[st] = from + (lower_bound(all_id.begin(), all_id.end(), val[st]) - all_id.begin());
          st = nxt[st];
        }
      }
    };

    for (int i = max_id - 1; i >= 0; i--) {
      renumerate(children[i], true, tot_lst_size[i]);
    }
    for (int i = max_id + 1; i < 26; i++) {
      renumerate(children[i], false, tot_lst_size[i]);
    }

    --lfid;
    for (int v : byd[curd]) {
      for (int i = 1; i < (int)chld[v].size(); i++) {
        nxt[lst_end[chld[v][i - 1]]] = lst_start[chld[v][i]];
      }
      for (int i = 0; i < (int)chld[v].size(); i++) {
        lst_size[v] += lst_size[chld[v][i]];
      }
      lst_size[v] += isk[v];
      if (chld[v].empty()) {
        assert(isk[v]);
        lst_start[v] = lst_end[v] = v;
        nxt[v] = -1;
        val[v] = lfid;
      } else {
        lst_start[v] = lst_start[chld[v][0]];
        lst_end[v] = lst_end[chld[v].back()];
        if (isk[v]) {
          val[v] = lfid;
          nxt[v] = lst_start[v];
          lst_start[v] = v;
        }
      }

    }
  }

  string ans(n - 1, '?');
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < (int)chld[i].size(); j++) {
      ans[chld[i][j] - 1] = 'a' + j;
    }
  }
  printf("%s\n", ans.c_str());
}

int main() {
#ifdef LOCAL
  freopen("m.in", "r", stdin);
  freopen("m.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    solve();
  }

  return 0;
}
