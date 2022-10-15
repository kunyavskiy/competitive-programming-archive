#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <deque>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#ifdef DEBUG
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define timestamp(str) eprintf("[ "str" ] time=%.4lf\n", clock() / double(CLOCKS_PER_SEC))
#else
#define eprintf(...)
#define timestamp(str)
#endif
#define sz(x) (int)((x).size())

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;

#define TASKNAME ""

const int inf = 1e9;
const double eps = 1e-9;
#define INF inf
#define EPS eps

const int n = 4;
int sc[n][n];
int diff[n][n];
int maxdiff;

bool was[4 * 4 * 4 * 4][8];

void go(int a, int b) {
  if (a >= n) {
    pair<pii, int> cur[4];
    memset(cur, 0, sizeof cur);

    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++)
        cur[i].first.first += sc[i][j],
        cur[i].first.second += diff[i][j];
      cur[i].second = i;
    }
    sort(cur, cur + 4);
    reverse(cur, cur + 4);

    int res = 0;
    int tmp = 0;
    for (int i = 0; i < 4; i++) tmp = tmp * 4 + cur[i].second;
    for (int i = 0; i < 3; i++)
      res |= !!(cur[i].first == cur[i + 1].first) << i;
    was[tmp][res] = true;
    return;
  }
  if (b >= a) return go(a + 1, 0);
  if (sc[a][b] || sc[b][a]) return go(a, b + 1);

  sc[a][b] = sc[b][a] = 1;
  diff[a][b] = diff[b][a] = 0;

  go(a, b + 1);
  for (int cd = 1; cd < maxdiff; cd++) {
    sc[a][b] = 3; sc[b][a] = 0;
    diff[a][b] = cd; diff[b][a] = -cd;
    go(a, b + 1);

    sc[a][b] = 0; sc[b][a] = 3;
    diff[a][b] = -cd; diff[b][a] = cd;
    go(a, b + 1);
  }
  sc[a][b] = sc[b][a] = 0;
}

int main() {
  int m;
  while (scanf("%d", &m) >= 1) {
    memset(sc, 0, sizeof sc);
    memset(diff, 0, sizeof diff);

    for (int i = 0; i < m; i++) {
      int a, b, c, d;
      scanf("%d%d%d%d", &a, &b, &c, &d), a--, b--;
      diff[a][b] += c - d;
      diff[b][a] += d - c;

      if (c > d) sc[a][b] = 3, sc[b][a] = 0;
      else if (c == d) sc[a][b] = sc[b][a] = 1;
      else sc[b][a] = 3, sc[a][b] = 0;
    }
    memset(was, 0, sizeof was);

    if (m >= 2) {
      maxdiff = 23;
      if (m >= 3) maxdiff = 50;
      go(0, 0);
      eprintf("done\n");
    } else {
      vi tmp(4);
      for (int i = 0; i < 4; i++) tmp[i] = i;
      do {
        int id = 0;
        for (int i = 0; i < 4; i++) id = id * 4 + tmp[i];
        was[id][0] = true;
      } while (next_permutation(tmp.begin(), tmp.end()));
    }

    set<vi> wwas;
    vi base(4);
    for (int i = 0; i < 4; i++) base[i] = i;
    do {
      int cid = 0;
      for (int i = 0; i < 4; i++) cid = cid * 4 + base[i];
      for (int m = 0; m < 8; m++) if (was[cid][m]) {
        vector<pii> tys(4);
        int las = 4;
        for (int i = 0; i < 4; i++) {
          tys[i] = mp(las, base[i]);
          if (!(m & (1 << i))) las--;
        }
        sort(tys.begin(), tys.end());
//        for (int i = 0; i < 3; i++) assert(tys[i] > tys[i + 1]);

        do {
          bool g = true;
          for (int i = 0; i < 3; i++)
            g = g && tys[i].first >= tys[i + 1].first;
          if (g) {
            vi tmp2(4);
            for (int i = 0; i < 4; i++) tmp2[i] = tys[i].second;
            wwas.insert(tmp2);
          }
        } while (next_permutation(tys.begin(), tys.end()));
      }
    } while (next_permutation(base.begin(), base.end()));

    printf("%d\n", sz(wwas));
    for (set<vi>::iterator it = wwas.begin(); it != wwas.end(); it++)
      for (int i = 0; i < sz(*it); i++)
        printf("%d%c", 1 + it->at(i), "\n "[i + 1 < 4]);
  }

  timestamp("end");
  return 0;
}
