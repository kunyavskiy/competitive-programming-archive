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

#ifdef LOCAL
//#define INTERACTOR
#endif

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

int n;

int get_num(int x, int y) {
  return x * n + y;
}

void get_coord(int num, int &x, int &y) {
  y = num % n;
  x = num / n;
//  assert(1 <= x && x <= n);
//  assert(1 <= y && y <= n);
}

bool good(int x) {
  return 0 <= x && x < n;
}

const int dx[4] = {0, 1, 1, 1};
const int dy[4] = {1, 0, 1, -1};
const int kdx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int kdy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

const int MAXN = 101;
const int MAXD = 5;
const int ZZZ = (MAXD * 2 + 1) * (MAXD * 2 + 1);

int winQ[MAXN][MAXN][ZZZ];
int outK[MAXN][MAXN][ZZZ];

int get_relative(int kx, int ky, int qx, int qy) {
//  return get_num(qx, qy);
  int dx = qx - kx;
  int dy = qy - ky;
  if (abs(dx) <= MAXD && abs(dy) <= MAXD) {
    return (dx + MAXD) * (2 * MAXD + 1) + (dy + MAXD);
  } else {
    return -1;
  }
}

void solveAll() {
  memset(winQ, -1, sizeof(winQ));
  vector <pii> loseK;
  for (int i = 0; i < n * n; ++i) {
    loseK.push_back(pii(i, i));
  }

  for (int kx = 0; kx < n; ++kx) {
    for (int ky = 0; ky < n; ++ky) {
      for (int k = 0; k < 8; ++k) {
        int nkx = kx + kdx[k];
        int nky = ky + kdy[k];
        if (good(nkx) && good(nky)) {
          for (int i = 0; i < ZZZ; ++i) {
            outK[kx][ky][i]++;
          }
        }
      }
    }
  }

//  eprintf("%d\n", outK[1][2][get_relative(1, 2, 2, 1)]);

  for (int i = 0; i < int(loseK.size()); ++i) {
    int qq = loseK[i].first;
    int kk = loseK[i].second;
    int qx, qy;
    get_coord(qq, qx, qy);
    int kx, ky;
    get_coord(kk, kx, ky);

//    eprintf("k(%d %d) q(%d %d): lose for knight\n", kx, ky, qx, qy);

    for (int j = 0; j < 4; ++j) {
//      int num = get_num_row_col_diag(j, qx, qy);
//      if (cntRelax[j][kk][num] >= 2) { continue; }
//      cntRelax[j][kk][num]++;
      for (int dd = -(2 * MAXD + 1); dd <= 2 * MAXD + 1; ++dd) {
        if (!dd) { continue; }
        int nqx = qx + dd * dx[j];
        int nqy = qy + dd * dy[j];
        if (good(nqx) && good(nqy)) {
          int nqq = get_num(nqx, nqy);
          if (nqq == kk) { continue; }
          int z1 = get_relative(kx, ky, nqx, nqy);
          if (z1 == -1) { continue; }
          if (winQ[kx][ky][z1] != -1) { continue; }
          winQ[kx][ky][z1] = qq;

          //eprintf("k(%d %d) q(%d %d -> %d %d): win by queen\n", kx, ky, nqx, nqy, qx, qy);

          for (int k = 0; k < 8; ++k) {
            int nkx = kx + kdx[k];
            int nky = ky + kdy[k];
            if (good(nkx) && good(nky)) {
              int nkk = get_num(nkx, nky);
              int z2 = get_relative(nkx, nky, nqx, nqy);
              if (z2 == -1) { continue; }
              --outK[nkx][nky][z2];
              if (outK[nkx][nky][z2] == 0) {
                loseK.push_back({nqq, nkk});
              }
            }
          }
        }
      }
    }
  }
  eprintf("end solve_all\n");
}

bool solve() {
  int qx, qy, kx, ky;
  scanf("%d%d%d%d", &qx, &qy, &kx, &ky);
  --qx, --qy, --kx, --ky;

  if (qx == -1) {
    return false;
  }
  int cnt_moves = 0;
  while (kx != -1) {
    eprintf("#%d: %d %d %d %d\n", cnt_moves, qx, qy, kx, ky);
    assert(cnt_moves < n);
    cnt_moves++;
    int zz = get_relative(kx, ky, qx, qy);
    if (zz == -1) {
      int best_qq = -1, best_d = n + 1000;
      for (int j = 0; j < 4; ++j) {
        for (int dd = -n; dd <= n; ++dd) {
          if (!dd) { continue; }
          int nqx = qx + dd * dx[j];
          int nqy = qy + dd * dy[j];
          if (good(nqx) && good(nqy)) {
            if (nqx == kx || nqy == ky || nqx + nqy == kx + ky || nqx - nqy == kx - ky) {
              int cur_d = max(abs(nqx - kx), abs(nqy - ky));
              if (cur_d < best_d) {
                best_d = cur_d;
                best_qq = get_num(nqx, nqy);
              }
            }
          }
        }
      }
      assert(best_qq != -1);
      get_coord(best_qq, qx, qy);
    } else {
      int new_qq = winQ[kx][ky][zz];
      assert(new_qq != -1);
      get_coord(new_qq, qx, qy);
    }
    printf("%d %d\n", qx + 1, qy + 1);
    fflush(stdout);
  #ifdef INTERACTOR
    if (kx == qx && ky == qy) {
      kx = -1, ky = -1;
    } else {
      int att = 0 ;
      do {
        int k = rand() % 8;
        int nkx = kx + kdx[k];
        int nky = ky + kdy[k];
        ++att;
        if (good(nkx) && good(nky)) {
          if (att >= 10 || !(qx == nkx || qy == nky || qx + qy == nkx + nky || qx - qy == nkx - nky)) {
            kx = nkx, ky = nky;
            break;
          }
        }
      } while (1);
    }
  #else
    scanf("%d%d", &kx, &ky);
    --kx, --ky;
  #endif
  }
  return true;
}

int main() {
#ifdef INTERACTOR
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  scanf("%d", &n);
  solveAll();
  while (solve());

  return 0;
}
