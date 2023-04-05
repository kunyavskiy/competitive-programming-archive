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
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  char s[10];
  int a[n][7];
  int max[n];
  for (int i = 0; i < n; i++) {
    scanf("%s", s);
    max[i] = 0;
    for (int j = 0; j < 7; j++) {
      a[i][j] = s[j] - '0';
      max[i] = max(max[i], a[i][j]);
    }
  }

  int d[n][n][7];
  for (int l = n - 1; l >= 0; l--) {
    for (int r = l; r < n; r++) {
      if (l == r) {
        for (int i = 0; i < 7; i++) {
          d[l][r][i] = a[l][i] == max[l] ? 0 : 1000000;
        }
      } else {
        for (int i = 0; i < 7; i++) {
          d[l][r][i] = 1000000;
          for (int m = l; m < r; m++) {
            d[l][r][i] = min(d[l][r][i], d[l][m][i] + d[m + 1][r][i]);
          }
        }
      }
      for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
          d[l][r][i] = min(d[l][r][i], d[l][r][j] + 1);
        }
      }
    }
  }

  cout << d[0][n - 1][0];

  return 0;
}
