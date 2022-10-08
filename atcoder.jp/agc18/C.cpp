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

set<pair<int, int>> s[3][3];

const int MAXN = 300100;

int a[3][MAXN];
int color[MAXN];

void remove_v(int id) {
  for (int i = 0; i < 3; i++) {
    if (i != color[id]) {
      s[color[id]][i].erase({-a[i][id] + a[color[id]][id], id});
    }
  }
}

void add_v(int id) {
  for (int i = 0; i < 3; i++) {
    if (i != color[id]) {
      s[color[id]][i].insert({-a[i][id] + a[color[id]][id], id});
    }
  }
}

void set_color(int id, int val) {
  if (color[id] != -1) {
    remove_v(id);
  }
  color[id] = val;
  add_v(id);
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int x, y, z;
  while (scanf("%d%d%d", &x, &y, &z) == 3) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        s[i][j].clear();
      }
    }

    memset(color, -1, sizeof(color));

    for (int i = 0; i < x + y + z; i++) {
      scanf("%d%d%d", &a[0][i], &a[1][i], &a[2][i]);
      if (i < x) {
        set_color(i, 0);
      } else if (i < x + y) {
        set_color(i, 1);
      } else if (i < x + y + z) {
        set_color(i, 2);
      }
    }

    while (true) {
      bool any = false;

      for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
          if (1LL * s[i][j].begin()->first + s[j][i].begin()->first < 0) {
            int id1 = s[i][j].begin()->second;
            int id2 = s[j][i].begin()->second;
            assert(color[id1] == i);
            assert(color[id2] == j);
            set_color(id1, j);
            set_color(id2, i);
            any = true;
          }
        }
      }

      if (1LL * s[0][1].begin()->first + s[1][2].begin()->first + s[2][0].begin()->first < 0) {
        int id0 = s[0][1].begin()->second;
        int id1 = s[1][2].begin()->second;
        int id2 = s[2][0].begin()->second;
        assert(color[id0] == 0);
        assert(color[id1] == 1);
        assert(color[id2] == 2);
        set_color(id0, 1);
        set_color(id1, 2);
        set_color(id2, 0);
        any = true;
      }

      if (1LL * s[0][2].begin()->first + s[2][1].begin()->first + s[1][0].begin()->first < 0) {
        int id0 = s[0][2].begin()->second;
        int id1 = s[1][0].begin()->second;
        int id2 = s[2][1].begin()->second;
        assert(color[id0] == 0);
        assert(color[id1] == 1);
        assert(color[id2] == 2);
        set_color(id0, 2);
        set_color(id1, 0);
        set_color(id2, 1);
        any = true;
      }

      if (!any) {
        break;
      }
    }

    ll ans = 0;
    for (int i = 0; i < x + y + z; i++) {
      ans += a[color[i]][i];
    }

    printf("%lld\n", ans);
  }

  return 0;
}
