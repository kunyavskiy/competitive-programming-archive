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
#include <unordered_map>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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

class Solver {
  map<pair<int, int>, int> m;
  vector<pair<int, int>> v;
  int n;
public:
  Solver(vector<pair<int, int>> v):v(v) {
    n = v.size();
    for (int p = 0; p < n; p++) {
      add(p, v[p].first, v[p].second);
    }
  }

  ll get(int x, int y) {
    ll ans = 0;
    for (int xx = x; xx >= 0; xx = (xx & (xx + 1)) - 1) {
      for (int yy = y; yy >= 0; yy = (yy & (yy + 1)) - 1) {
        ans += m[{xx, yy}];
      }
    }
    return ans;
  }

  ll get(int l, int r, int x) {
    return get(r - 1, x) - get(l - 1, x);
  }

  ll get(int l, int r, int min, int max) {
    return get(l, r, min - 1) - get(l, r, max);
  }

  void add(int x, int y, int v) {
    for (int xx = x; xx < n; xx = xx | (xx + 1)) {
      for (int yy = y; yy < n; yy = yy | (yy + 1)) {
        m[{xx, yy}] += v;
      }
    }
  }

  void add(int p, int x) {
    add(p, v[p].first, x);
  }
};

// calculates cyclic shifts
const int MAXL = 300002; // without \0
const int ALPHA = 128;  // |alphabet|, should be<=MAXL
char s[MAXL + 1];
/*BOXNEXT*/
int *sarr; // cyclic shifts, in sorted order
int sapos[MAXL]; // sarr ^ -1

#define nlen(x) ((x) >= len ? (x) - len : (x))

void build() {
  int len = strlen(s);

  static int _sarr1[MAXL], _sarr2[MAXL];
  static int _cols1[MAXL], _cols2[MAXL];
  static int cnt[MAXL];

  sarr = _sarr1;
  int *nsarr = _sarr2;
  int *cols = _cols1, *ncols = _cols2;

  for (int i = len - 1; i >= 0; i--) {
    cols[i] = s[i];
    sarr[i] = i;
  }

  int colcnt = ALPHA;
  for (int clen = 0; clen < len;
       clen = clen ? (clen << 1) : 1) {
    memset(cnt, 0, sizeof(cnt[0]) * colcnt);
    for (int i = 0; i < len; i++)
      cnt[cols[i]]++;
    for (int i = 1; i < colcnt; i++)
      cnt[i] += cnt[i - 1];

    for (int i = len - 1; i >= 0; i--) {
      int a = nlen(sarr[i] + len - clen);
      nsarr[--cnt[cols[a]]] = a;
    }

    colcnt = 0;
    for (int i = 0; i < len; i++) {
      int a = nsarr[i], b = nlen(a + clen); /*BOXNEXT*/
      if (i == 0 || cols[a] != cols[nsarr[i - 1]] || cols[b] != cols[nlen(nsarr[i - 1] + clen)])
        colcnt++;
      ncols[a] = colcnt - 1;
    }
    swap(cols, ncols);
    swap(sarr, nsarr);

    if (colcnt == len) break;
  }
  if (colcnt < len) { // required, otherwise equal shifts will be sorted by (i+wtf)
    memset(cnt, 0, sizeof(cnt[0]) * colcnt);
    for (int i = 0; i < len; i++)
      cnt[cols[i]]++;
    for (int i = 1; i < colcnt; i++)
      cnt[i] += cnt[i - 1];
    for (int i = len - 1; i >= 0; i--)
      sarr[--cnt[cols[i]]] = i;
  }
  for (int i = 0; i < len; i++)
    sapos[sarr[i]] = i;
}

int lcps[MAXL]; // lcp[i] = lcp(sarr[i], sarr[i+1])

void build_lcp() {
  int len = strlen(s);
  if (len <= 1) return;

  int i = nlen(sarr[len - 1] + 1), clcp = 0;
  for (int step = 0; step < len - 1; step++) {
    int j = sarr[sapos[i] + 1];

    while (clcp < len) {
      int pos1 = nlen(i + clcp),
          pos2 = nlen(j + clcp);
      if (s[pos1] != s[pos2]) break;
      clcp++;
    }
    lcps[sapos[i]] = clcp;

    if (j == len - 1) clcp = 0;
    if (++i >= len) i = 0;
    clcp = max(clcp - 1, 0);
  }
}

const int MAXK = 20;
int sp[MAXK][MAXL];

int l2[MAXL];

int getmin(int l, int r) {
  int d = (r - l);
  int k = l2[d];
  return min(sp[k][l], sp[k][r - (1 << k)]);
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  l2[1] = 0;
  for (int i = 2; i < MAXL; i++) {
    l2[i] = l2[i - 1];
    if ((i & (i - 1)) == 0) {
      l2[i]++;
    }
  }

  scanf("%s", s);
  int slen = strlen(s);
  s[slen] = '#';
  scanf("%s", s + slen + 1);
  int tlen = strlen(s + slen + 1);
  s[slen + tlen + 1] = '$';
  s[slen + tlen + 2] = 0;

  reverse(s, s + slen);
  reverse(s + slen + 1, s + slen + 1 + tlen);

  build();
  build_lcp();

//  for (int i = 0; s[i]; i++) {
//    printf("%s %d\n", s + sarr[i], lcps[i]);
//  }

  int n = strlen(s);

  for (int k = 0; k < MAXK; k++) {
    int l = (1 << k);
    for (int i = 0; i + l <= n; i++) {
      if (l == 1) {
        sp[k][i] = lcps[i];
      } else {
        sp[k][i] = min(sp[k - 1][i], sp[k - 1][i + l / 2]);
      }
    }
  }

  vector<pair<int, int>> v(n, {-1, 0});

  for (int i = 0; i < slen; i++) {
    int x;
    scanf("%d", &x);
    int j = sapos[slen - 1 - i];
    v[j] = {slen - 1 - i, x};
  }

  Solver solver(v);

  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; i++) {
    int t;
    scanf("%d", &t);
    if (t == 1) {
      int x, y;
      scanf("%d%d", &x, &y);
      x = slen - x - 1;
      int j = sapos[x];
      solver.add(j, y - v[j].second);
      v[j].second = y;
    } else {
      int t1, t2, s1, s2;
      scanf("%d%d%d%d", &t1, &t2, &s1, &s2);
      t1 = tlen - t1 - 1;
      t2 = tlen - t2 - 1;
      swap(t1, t2);
      t2++;
      s1 = slen - s1 - 1;
      s2 = slen - s2 - 1;
      swap(s1, s2);
      s2++;

      int L = 0, R = 0;
      int pp = sapos[slen + 1 + t1];

      {
        int l = pp;
        int r = n + 1;
        while (r > l + 1) {
          int m = (l + r) / 2;
          if (getmin(pp, m) >= (t2 - t1)) {
            l = m;
          } else {
            r = m;
          }
        }
        R = r;
      }
      {
        int l = -1;
        int r = pp;
        while (r > l + 1) {
          int m = (l + r) / 2;
          if (getmin(m, pp) >= (t2 - t1)) {
            r = m;
          } else {
            l = m;
          }
        }
        L = r;
      }

      // x + (t2 - t1) <= s2
      cout << solver.get(L, R, s1, s2 - t2 + t1) << endl;
    }
  }


  return 0;
}
