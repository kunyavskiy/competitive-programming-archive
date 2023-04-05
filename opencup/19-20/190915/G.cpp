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
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  vector<vector<vector<int>>> g(4, vector<vector<int>>(21));
  for (int n = 0; n <= 20; n++) {
    for (int b = 0; b < 4; b++) {
      g[b][n].resize(1 << n);
      for (int x = 0; x < (1 << n); x++) {
        vector<bool> z(2 * n + 5);
        for (int i = 0; i < n; i++) {
          if (x & (1 << i)) {
            int gg = g[b][n][x - (1 << i)];
            if (gg < (int)z.size()) z[gg] = true;
            int xl = x & ((1 << i) - 1);
            int nl = i;
            int bl = (b & 1) + 2;
            int xr = x >> (i + 1);
            int nr = n - i - 1;
            int br = (b & 2) + 1;
            gg = g[bl][nl][xl];
            gg ^= g[br][nr][xr];
            if (gg < (int)z.size()) z[gg] = true;
          } else {
            bool ok = true;
            if (i == 0 && (b & 1) == 0) ok = false;
            if (i == (n - 1) && (b & 2) == 0) ok = false;
            if (ok) {
              int xl = x & ((1 << i) - 1);
              int nl = i;
              int bl = (b & 1);
              int xr = x >> (i + 1);
              int nr = n - i - 1;
              int br = (b & 2);
              int gg = g[bl][nl][xl] ^ g[br][nr][xr];
              if (gg < (int)z.size()) z[gg] = true;
            }
          }
        }
        while (z[g[b][n][x]]) g[b][n][x]++;
      }
    }
  }

  ios::sync_with_stdio(false);
  int t;
  cin >> t;

  for (int i = 0; i < t; i++) {
    int m;
    cin >> m;
    int b = 2;
    int n = 0;
    int x = 0;
    int res = 0;
    for (int j = 0; j < m; j++) {
      string s;
      cin >> s;
      if (s == "III") {
        n++;
        x = x * 2 + 1;
      } else if (s == "II." || s == ".II") {
        n++;
        x *= 2;
      } else if (s == "I.I") {
        b = b + 1;
        res ^= g[b][n][x];
        n = 0;
        x = 0;
        b = 2;
      } else if (s == ".I.") {
        res ^= g[b][n][x];
        n = 0;
        x = 0;
        b = 0;
      } else {
        assert(false);
      }
    }
    b = b + 1;
    res ^= g[b][n][x];

    if (res == 0) {
      cout << "Second\n";
    } else {
      cout << "First\n";
    }

  }

  return 0;
}
