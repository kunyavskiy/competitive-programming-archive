#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
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

const int MAX = 120;
ll d1[MAX][MAX][MAX];
ll d2[MAX][MAX][MAX];
ll pen[MAX][MAX];

int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  vector<int> x(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &x[i]);
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      ll d = abs(x[i] - x[j]);
      ll dd = (ll)sqrt(d);
      while (dd * dd < d) dd++;
      while (dd * dd > d) dd--;
      pen[i][j] = d * dd;
    }
  }
  for (int l = n - 1; l >= 0; l--) {
    for (int r = l; r < n; r++) {
      for (int i = l; i <= r; i++) {
        d1[l][r][0] += pen[i][r];
        d1[r][l][0] += pen[i][l];
        d2[l][r][0] += pen[i][r];
        d2[r][l][0] += pen[i][l];
      }
      for (int h = 1; h < n - 1; h++) {
        d1[l][r][h] = d1[l][r][h - 1];
        d1[r][l][h] = d1[r][l][h - 1];
        d2[l][r][h] = d2[l][r][h - 1];
        d2[r][l][h] = d2[r][l][h - 1];
        for (int i = l; i < r; i++) {
          d2[l][r][h] = min(d2[l][r][h], d1[i][l][h - 1] + d1[i + 1][r][h] + pen[l][r]);
        }
        for (int i = l + 1; i <= r; i++) {
          d2[r][l][h] = min(d2[r][l][h], d1[i][r][h - 1] + d1[i - 1][l][h] + pen[l][r]);
        }
        for (int i = l; i < r; i++) {
          d1[l][r][h] = min(d1[l][r][h], d1[l][i][h - 1] + d2[i][r][h]);
        }
        for (int i = l + 1; i <= r; i++) {
          d1[r][l][h] = min(d1[r][l][h], d1[r][i][h - 1] + d2[i][l][h]);
        }
      }
    }
  }
  vector<ll> res(n, LLONG_MAX);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      res[j] = min(res[j], d1[0][i][j] + d1[n - 1][i][j]);
    }
  }
  for (int i = 0; i < n - 1; i++) {
    cout << res[i] << "\n";
  }

  return 0;
}
