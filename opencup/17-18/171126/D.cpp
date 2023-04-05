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

#define BB 100

int op[2010][2010];
int vl[2010][2010];
int a[2010][2010];
int mv[2010][2010];
int next_b[2010];
int n, m;

int nx(int i) {
  return i == n - 1 ? 0 : i + 1;
}

int go(int i, int j) {
  int jj = j;
  int ii = nx(i);
  if (a[ii][j == 0 ? m - 1 : j - 1] > a[ii][jj]) jj = j == 0 ? m - 1 : j - 1;
  if (a[ii][j == m - 1 ? 0 : j + 1] > a[ii][jj]) jj = j == m - 1 ? 0 : j + 1;
  return jj;
}

void recalc(int i, int j) {
  int ii = nx(i);
  int jj = go(i, j);
  if (ii == next_b[i]) {
    mv[i][j] = jj;
  } else {
    mv[i][j] = mv[ii][jj];
  }
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  scanf("%d%d", &m, &n);

  for (int j = 0; j < m; j++) {
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i][j]);
    }
  }

  int nxb = 0;
  for (int i = n - 1; i >= 0; i--) {
    next_b[i] = nxb;
    if (i == n - 1 || i % BB == 0) {
      nxb = i;
    }
  }

  for (int i = n - 1; i >= 0; i--) {
    for (int j = 0; j < m; j++) {
      recalc(i, j);
    }
  }

  int qqq;
  scanf("%d", &qqq);
  char str[10];
  int x = 0;
  int y = 0;
  int ooo = 0;
  for (int ttt = 0; ttt < qqq; ttt++) {
    scanf("%s", str);
    if (str[0] == 'm') {
      ooo++;
      int k;
      scanf("%d", &k);
      while(k > 0) {
        eprintf("> %d %d %d\n", x, y, k);
        if (op[x][y] == ooo) {
          int d = vl[x][y] - k;
          eprintf("%d %d %d\n", x, y, d);
          k %= d;
        }
        op[x][y] = ooo;
        vl[x][y] = k;
        int d = next_b[x] - x;
        if (d < 0) d += n;
        eprintf(".%d %d\n", x, next_b[x]);
        if (d <= k) {
          y = mv[x][y];
          x = next_b[x];
          k -= d;
        } else if (k) {
          y = go(x, y);
          x = nx(x);
          k--;
        }
        eprintf("> %d %d %d\n", x, y, k);
      }
      printf("%d %d\n", y + 1, x + 1);
    } else {
      int r, c, e;
      scanf("%d%d%d", &r, &c, &e);
      r--;c--;
      a[c][r] = e;
      int k = c == 0 ? n - 1 : c - 1;
      for (int i = k; i >= 0 && next_b[i] == next_b[k]; i--) {
        int lo = r - (k - i) - 1;
        int hi = r + (k - i) + 1;
        for (int j = lo; j <= hi; j++) {
          recalc(i, (j % m + m) % m);
        }
      }
    }
  }

  return 0;
}
