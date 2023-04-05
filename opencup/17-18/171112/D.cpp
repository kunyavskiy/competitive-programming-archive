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

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int h, w, k;
  while (scanf("%d%d%d", &h, &w, &k) == 3) {
    vector<vector<int>> f(h, vector<int>(w, 0));
    for (int y = 0; y < h; y++) {
      static char buf[210];
      scanf("%s", buf);
      assert((int) strlen(buf) == w);
      for (int x = 0; x < w; x++) {
        f[y][x] = buf[x] - '0';
        assert(f[y][x] == !!f[y][x]);
      }
    }

    eprintf("=====\n");
    vector<int> xcut, ycut;
    xcut.push_back(0);
    {
      int ccnt = 0, x = 0;
      for (int i = 0; i < k; i++) {
        const int need = (i + 1) * k;
        while (x < w && ccnt < need) {
          for (int y = 0; y < h; y++)
            ccnt += f[y][x];
          x++;
        }
        eprintf("x=%d; i=%d/%d, ccnt=%d, need=%d\n", x, i, k, ccnt, need);
        if (ccnt != need) {
          printf("NO\n");
          goto end;
        }
        xcut.push_back(x);
      }
    }
    ycut.push_back(0);
    {
      int ccnt = 0, y = 0;
      for (int i = 0; i < k; i++) {
        const int need = (i + 1) * k;
        while (y < h && ccnt < need) {
          for (int x = 0; x < w; x++)
            ccnt += f[y][x];
          y++;
        }
        eprintf("y=%d; i=%d/%d, ccnt=%d, need=%d\n", y, i, k, ccnt, need);
        if (ccnt != need) {
          printf("NO\n");
          goto end;
        }
        ycut.push_back(y);
      }
    }
    assert((int)xcut.size() == k + 1);
    assert((int)ycut.size() == k + 1);

    for (int i = 0; i < k; i++)
      for (int j = 0; j < k; j++) {
        int cnt = 0;
        for (int y = ycut[i]; y < ycut[i + 1]; y++)
          for (int x = xcut[i]; x < xcut[i + 1]; x++)
            cnt += f[y][x];
        if (cnt != 1) {
          printf("NO\n");
          goto end;
        }
      }
    printf("YES\n");
    for (int i = 1; i < k; i++)
      printf("%d%c", ycut[i], "\n "[i + 1 < k]);  // ycut[i] + 1 - 1
    for (int i = 1; i < k; i++)
      printf("%d%c", xcut[i], "\n "[i + 1 < k]);  // xcut[i] + 1 - 1
    end:;
  }

  return 0;
}
