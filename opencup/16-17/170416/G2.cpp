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

struct Rect {
  int xl, yl, xr, yr;
  int v;
};

vector<Rect> v;
int c[55][55];

int n, m, k;

vector<int> p;
vector<int> pex;
vector<int> pey;
vector<int> minv;
vector<int> used;
int used_version;



map<int, int> sold[55][55];

int bfs(int start, int have) {
  if (used[start] == used_version) {
    return 0;
  }
//  eprintf("start = %d, have = %d\n", start, have);
  used[start] = used_version;

  queue<int> q;
  q.push(start);
  p[start] = pex[start] = pey[start] = -1;
  minv[start] = have;

  while (!q.empty()) {

    int vx = q.front();
    q.pop();

    for (int x = v[vx].xl; x < v[vx].xr; x++) {
      for (int y = v[vx].yl; y < v[vx].yr; y++) if (c[x][y]) {
        int mval = min(c[x][y], minv[vx]);
        v[start].v -= mval;

        c[x][y] -= mval;
        sold[x][y][vx] += mval;

        while (vx != start) {
          int xx = pex[vx];
          int yy = pey[vx];

          sold[xx][yy][vx] -= mval;
          if (sold[xx][yy][vx] == 0) {
            sold[xx][yy].erase(vx);
          }

          vx = p[vx];

          sold[xx][yy][vx] += mval;
        }

        return mval;
      }
    }

    for (int x = v[vx].xl; x < v[vx].xr; x++) {
      for (int y = v[vx].yl; y < v[vx].yr; y++) {
        for (auto t: sold[x][y]) {
          int id = t.first;
          if (used[id] == used_version) continue;
          q.push(id);
          p[id] = vx;
          pex[id] = x;
          pey[id] = y;
          minv[id] = min(minv[vx], t.second);
          used[id] = used_version;
        }
      }
    }
  }

  return 0;
}

int main() {
#ifdef LOCAL
//  freopen("g.in", "r", stdin);
//  freopen("g.out", "w", stdout);
#endif

  scanf("%d%d%d", &n, &m, &k);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", &c[i][j]);
    }
  }

  v.resize(k);
  for (int i = 0; i < k; i++) {
    scanf("%d%d%d%d%d", &v[i].xl, &v[i].xr, &v[i].yl, &v[i].yr, &v[i].v);
    v[i].xl--;
    v[i].yl--;
  }

  long long ans = 0;

  int ops = 0;

  for (int i = 0; i < k; i++) {
    for (int x = v[i].xl; x < v[i].xr && v[i].v; x++) {
      for (int y = v[i].yl; y < v[i].yr && v[i].v; y++) {
        if (c[x][y] > 0) {
          int mval = min(c[x][y], v[i].v);
          v[i].v -= mval;
          c[x][y] -= mval;
          sold[x][y][i] += mval;
          ans += mval;
          ++ops;
        }
      }
    }
  }

  eprintf("ops = %d\n", ops);

  TIMESTAMP("gready");

  p.resize(k);
  pex.resize(k);
  pey.resize(k);
  minv.resize(k);
  used.resize(k);


//  int at_least = 1 << 30;
//  while (at_least > 0) {
//    TIMESTAMPf("%d", at_least);
    ++used_version;
    for (int i = 0; i < k; i++) {
      if (i % 1000 == 0) {
        TIMESTAMPf("%d", i);
      }
//    eprintf("i = %d\n", i);
      while (v[i].v > 0) {
//        eprintf("v[i].v = %d\n", v[i].v);
        ++used_version;
        int done = bfs(i, v[i].v);
        ans += done;
        if (!done) break;
      }
    }
//    at_least /= 2;
//  }

  printf("%lld\n", ans);

  return 0;
}
