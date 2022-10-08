//#include <iostream>
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
#include <stdarg.h>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if (_WIN32 || __WIN32__)
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "C"

typedef long long ll;
typedef long double ld;

const int MOD = 1000000007;

struct matrix {
  int v[2][2];

  matrix() {
    memset(v, 0, sizeof(v));
  }
  explicit matrix(int x) {
    v[0][1] = v[1][0] = 0;
    v[0][0] = v[1][1] = x;
  }
  matrix(int a, int b, int c, int d) {
    v[0][0] = a;
    v[0][1] = b;
    v[1][0] = c;
    v[1][1] = d;
  }

  void dump() {
    eprintf("[%d, %d, %d, %d]\n", v[0][0], v[0][1], v[1][0], v[1][1]);
  }
};

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

void add(int& a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

matrix operator*(const matrix& a, const matrix& b) {
  matrix res(0);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        add(res.v[i][j], mul(a.v[i][k], b.v[k][j]));
      }
    }
  }
  return res;
}

const int MAXN = 1 << 23;

matrix tree[2 * MAXN];
int lst;

void update(int pos, matrix m) {
  pos += lst;
  tree[pos] = m;
  while (pos /= 2) {
    tree[pos] = tree[2*pos + 1] * tree[2*pos];
  }
}

int cnt[MAXN][3];
int n;

void recalc(int w) {
  if (w == 0) {
    update(w, matrix(cnt[w][1], 0, 1, 0));
  } else {
    update(w, matrix(cnt[w][1], mul(cnt[w][0], cnt[w-1][2]), 1, 0));
  }
}

void add(int w, int d, int s) {
  --w;
  if (w == 0) d = max(d, 1);
  if (w == n - 1) d = min(d, 1);
  add(cnt[w][d], s);
  for (int t = -1; t <= 1; t++) {
    if (0 <= w + t && w + t< n) {
      recalc(w + t);
    }
  }
}

void solve() {
  memset(cnt, 0, sizeof(cnt));
  int m;
  scanf("%d%d", &n, &m);
  lst = 2;
  while (lst < n) lst *= n;

  for (int i = 0; i < n; i++) {
    tree[i + lst] = matrix(1, 0, 1, 0);
    cnt[i][1] = 1;
  }
  for (int i = n; i < lst; i++) {
    tree[i + lst] = matrix(1);
  }
  for (int i = lst - 1; i > 0; i--) {
    tree[i] = tree[2 * i + 1] * tree[2 * i];
  }

  int w1, aw, bw;
  scanf("%d%d%d", &w1, &aw, &bw);
  int d1, ad, bd;
  scanf("%d%d%d", &d1, &ad, &bd);
  int s1, as, bs;
  scanf("%d%d%d", &s1, &as, &bs);

  int res = 0;

  for (int i = 0; i < m; i++) {
    add(w1, d1, s1);
    int ans = tree[1].v[0][0];
    add(res, ans);
    w1 = (w1 * 1LL * aw + bw) % n + 1;
    d1 = (d1 * 1LL * ad + bd) % 3;
    s1 = (s1 * 1LL * as + bs) % 1000000000 + 1;
  }

  printf("%d\n", res);
}

int main() {
  freopen(TASKNAME".in", "r", stdin);
  freopen(TASKNAME".out", "w", stdout);

  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    printf("Case #%d: ", i);
    eprintf("Case #%d:\n", i);
    solve();
  }

  return 0;
}
