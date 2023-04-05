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
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


using namespace std;

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

  ~__timestamper() {
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
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  vector<vector<int>> a(n, vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", &a[i][j]);
    }
  }

  vector<vector<int>> cmp(m, vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      for (int k = j + 1; k < m; k++) {
        if (a[i][k] > a[i][j]) {
          cmp[j][k] |= (1 << i);
        }
      }
    }
  }

  ll res = 0;

  for (int x = 1; x < (1 << n); x++) {

//    ll pres = res;

    vector<bool> good(m, true);
    for (int j = 0; j < m; j++) {
      int last = -1;
      int sign = 0;
      for (int i = 0; i < n; i++) {
        if (x & (1 << i)) {
          if (last == -1) {
            last = a[i][j];
          } else {
            int s = a[i][j] > last ? 1 : -1;
            if (sign == 0) {
              sign = s;
            } else if (s != sign) {
              good[j] = false;
            }
            last = a[i][j];
          }
        }
      }
      if (good[j]) res++;
    }


    map<int, vector<pair<int, int>>> g;

    for (int j = 0; j < m; j++) if (good[j]){
      for (int k = j + 1; k < m; k++) if (good[k]) {
        int c = cmp[j][k] & x;
        g[c].emplace_back(j, k);
      }
    }

    for (auto l: g) {
      vector<int> cnt(m, 1);
      for (auto p: l.second) {
        res += cnt[p.first];
        cnt[p.second] += cnt[p.first];
      }
    }

//    cout << x << " " << res - pres << endl;

  }

  cout << res << endl;

  return 0;
}

