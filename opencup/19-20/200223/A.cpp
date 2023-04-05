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
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int n, k;
  scanf("%*d");

  vector<vector<int>> good;
  int tot_good = 0;

  for (int i = (1 << 15); i < (1 << 16); i ++) {
    vector<int> js;
    for (int j = 0; j < 16; j++) {
      if (i & (1 << j)) {
        js.push_back(j);
      }
    }
    bool ok = true;
    for (int a : js) {
      for (int b : js) {
        if ((a & b) == 0) {
          ok = false;
        }
      }
    }
    if (ok) {
      good.push_back(js);
      tot_good += js.size();
    }
  }
  eprintf("%d %d\n", (int)good.size(), tot_good);


  while (scanf("%d%d", &n, &k) == 2) {
    vector<int> tp(n);
    for (int i = 0; i < k; i++) {
      int m;
      scanf("%d", &m);
      for (int j = 0; j < m; j++) {
        int x;
        scanf("%d", &x);
        tp[x - 1] |= 1 << i;
      }
    }

    vector<int> cnt(16);
    for (int i = 0; i < n; i++) {
      cnt[tp[i]]++;
    }

    int ans = 0;
    for (const auto& mask : good) {
      int tot = 0;
      for (int j : mask) {
        tot += cnt[j];
      }
      ans = max(ans, tot);
    }

    printf("%d\n", ans);
  }

  return 0;
}
