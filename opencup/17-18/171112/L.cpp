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

const int INF = 1000000000;

struct BoundingBox {
  int x1 = INF, y1 = INF;
  int x2 = -INF, y2 = -INF;

  void add(int x, int y) {
    x1 = min(x1, x);
    x2 = max(x2, x);
    y1 = min(y1, y);
    y2 = max(y2, y);
  }
};

int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
#endif

  int h, w;
  while (scanf("%d%d", &h, &w) == 2) {
    eprintf("=====\n");
    vector<vector<int>> f(h, vector<int>(w));
    vector<int> ids;
    for (int y = 0; y < h; y++)
      for (int x = 0; x < w; x++) {
        scanf("%d", &f[y][x]);
        ids.push_back(f[y][x]);
      }
    sort(ids.begin(), ids.end());
    ids.erase(unique(ids.begin(), ids.end()), ids.end());
    vector<int> newIds(*max_element(ids.begin(), ids.end()) + 1);
    for (int i = 0; i < (int) ids.size(); i++) {
      newIds[ids[i]] = i;
    }

    int n = (int) ids.size();
    vector<int> sizes(n);
    vector<BoundingBox> boxes(n);
    for (int y = 0; y < h; y++)
      for (int x = 0; x < w; x++) {
        f[y][x] = newIds[f[y][x]];
        sizes[f[y][x]]++;
        boxes[f[y][x]].add(x, y);
      }
    //for (int i = 0; i < n; i++)
      //eprintf("(%d,%d)..(%d,%d), size=%d\n", boxes[i].x1, boxes[i].y1, boxes[i].x2, boxes[i].y2, sizes[i]);

    vector<pair<int, int>> verSizes(n);
    int ver = 0;

    int ans = 0;
    for (int orig = 0; orig < n; orig++) {
      const BoundingBox &b = boxes[orig];
      static vector<int> met;
      met.clear();

      ver++;
      for (int y = b.y1; y <= b.y2; y++)
        for (int x = b.x1; x <= b.x2; x++) {
          int c = f[y][x];
          if (verSizes[c].first < ver) {
            verSizes[c] = make_pair(ver, 0);
            met.push_back(c);
          }
          verSizes[c].second++;
        }
      int cans = 0;
      for (int c : met) {
        assert(verSizes[c].first == ver);
        assert(verSizes[c].second <= sizes[c]);
        if (verSizes[c].second == sizes[c]) {
          //eprintf("outside=%d, inside=%d\n", ids[orig], ids[c]);
          cans++;
        }
      }
      assert(cans >= 1);
      ans += cans - 1;
    }
    printf("%d\n", ans);
  }

  return 0;
}
