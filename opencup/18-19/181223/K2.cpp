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
  freopen("k.in", "r", stdin);
  //freopen("k.out", "w", stdout);
#endif

  int n, m, q;
  while (scanf("%d%d%d", &n, &m, &q) == 3) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    vector<vector<pair<int, int>>> vct(m + 2);
    for (int i = 0; i < n; i++) {
      vct[a[i]].push_back({i, i});
    }

    for (int i = 0; i <= m; i++) {
      sort(vct[i].begin(), vct[i].end());

      int j = 0;
      for (auto o : vct[i]) {
        while (j < (int)vct[i].size() && vct[i][j].first < o.second + 1) j++;

        if (j < (int)vct[i].size() && vct[i][j].first == o.second + 1) {
          vct[i + 1].push_back({o.first, vct[i][j].second});
        }
      }
    }

    for (int i = 0; i < q; i++) {
      int l, r, k;
      scanf("%d%d%d", &l, &r, &k);
      l--;
      r--;

      int L, R;

      int res = 0;

      L = -1, R = vct[k].size();
      while (R - L > 1) {
        int M = (L + R) >> 1;
        if (vct[k][M].first < l) L = M;
        else R = M;
      }
      res -= R;

      L = -1, R = vct[k].size();
      while (R - L > 1) {
        int M = (L + R) >> 1;
        if (vct[k][M].second < r) L = M;
        else R = M;
      }
      res += R;

      res = max(res, 0);

      printf("%d\n", res);
    }
  }

  return 0;
}
