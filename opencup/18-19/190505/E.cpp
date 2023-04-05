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
typedef pair<int,int> pii;

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  vector<vector<int>> a(2, vector<int>(2 * n));
  for (int i = 0; i < 2 * n; ++i) {
    scanf("%d%d", &a[0][i], &a[1][i]);
  }

  vector<int> z(2 * n, -1);
  set<pii> used[2];
  set<pii> avail[2];
  set<pii> flip[2];

  ll sum = 0;
  auto del = [&](int i, int ind) {
    avail[0].insert({a[0][ind], ind});
    avail[1].insert({a[1][ind], ind});
    used[i].erase({a[i][ind], ind});
    flip[i].erase({a[i^1][ind] - a[i][ind], ind});
    sum -= a[i][ind];
    z[ind] = -1;
  };

  auto add = [&](int i, int ind) {
    avail[0].erase({a[0][ind], ind});
    avail[1].erase({a[1][ind], ind});
    used[i].insert({a[i][ind], ind});
    flip[i].insert({a[i^1][ind] - a[i][ind], ind});
    sum += a[i][ind];
    z[ind] = i;
  };


  for (int i = 0; i < 2 * n; ++i) {
    avail[0].insert({a[0][i], i});
    avail[1].insert({a[1][i], i});
  }

  for (int k = 1; k <= n; ++k) {
    for (int i = 0; i < 2; ++i) {
      int ind = avail[i].begin()->second;
      add(i, ind);
    }

    while (1) {
      bool changed = false;
      for (int i = 0; i < 2; ++i) {
        if (avail[i].empty()) { continue; }
        int ind_old = used[i].rbegin()->second;
        int ind_new = avail[i].begin()->second;

        if (a[i][ind_old] > a[i][ind_new]) {
          changed = true;
          del(i, ind_old);
          add(i, ind_new);
        }
      }

      for (int i = 0; i < 2; ++i) {
        if (flip[i].begin()->first + flip[i^1].begin()->first >= 0) { continue; }
        int ind1 = flip[i].begin()->second;
        int ind2 = flip[i^1].begin()->second;
        changed = true;
        del(i, ind1);
        del(i^1, ind2);
        add(i^1, ind1);
        add(i, ind2);
      }

      for (int i = 0; i < 2; ++i) {
        if (avail[i^1].empty()) { continue; }

        if (-used[i].rbegin()->first + flip[i^1].begin()->first + avail[i^1].begin()->first < 0) {
          int ind1 = used[i].rbegin()->second;
          int ind2 = flip[i^1].begin()->second;
          int ind3 = avail[i^1].begin()->second;

          del(i, ind1);
          del(i^1, ind2);
          add(i, ind2);
          add(i^1, ind3);
          changed = true;
        }
      }

      if (!changed) {
        break;
      }
    }

    printf("%lld\n", sum);
//    for (int i = 0; i < 2 * n; ++i) {
//      eprintf("%d ", z[i]);
//    }
//    eprintf("\n");
  }

  return 0;
}


