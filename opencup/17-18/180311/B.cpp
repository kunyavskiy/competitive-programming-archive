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
typedef pair<int,int> pii;

const int MAXN = 12;
int n;
char g[6][MAXN][MAXN + 1];
int sq[6];

int order[6];
char field[MAXN][MAXN][MAXN + 1];
int cnt[MAXN][MAXN][MAXN];
bool good_shift[6][2][2];
int good_shift_counts[6];
bool good_transform[6][2][4][2][2];

struct Point {
  int x, y, z;
};

Point getPoint(int x, int y, int num) {
  if (num == 0) {
    return Point({0, x, y});
  } else if (num == 1) {
    return Point({x, 0, y});
  } else if (num == 2) {
    return Point({x, y, 0});
  } else   if (num == 3) {
    return Point({n - 1, x, y});
  } else if (num == 4) {
    return Point({x, n - 1, y});
  } else if (num == 5) {
    return Point({x, y, n - 1});
  } else {
    assert(0);
  }
}

bool in_range(int n, int x) {
  return 0 <= x && x < n;
}

void rotate(int &x, int &y, int j) {
  while (j) {
    swap(x, y);
    x = n - 1 - x;
    --j;
  }
}


bool check() {
  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < n; ++y) {
      for (int z = 0; z < n; ++z) {
        if (cnt[x][y][z] == 0 && field[x][y][z] == '.') {
          return false;
        }
      }
    }
  }
  return true;
}

void printAns() {
  for (int i = 0; i < 6; ++i) {
    int p = order[i];
    for (int x = 1; x < n - 1; ++x) {
      for (int y = 1; y < n - 1; ++y) {
        Point z = getPoint(x, y, i);
        field[z.x][z.y][z.z] = p == -1 ? '.' : (char)('A' + p);
      }
    }
  }
  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < n; ++y) {
      printf("%s\n", field[x][y]);
    }
    printf("\n");
  }
}


void brute(int used_mask_g, int k) {
//  printf("mask %d k %d\n", used_mask_g, k);
//  printAns();

  if (k == 6) {
    printAns();
    exit(0);
  }

  vector <int> pps;
  for (int p = 0; p < 6; ++p) {
    if (used_mask_g & (1 << p)) { continue; }
    pps.push_back(p);
  }
  sort(pps.begin(), pps.end(), [](int i, int j){return good_shift_counts[i] < good_shift_counts[j];});

  for (int p : pps) {
    assert(!(used_mask_g & (1 << p)));
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 4; ++j) {
        for (int dx = 0; dx < 2; ++dx) {
          for (int dy = 0; dy < 2; ++dy) {
            if (!good_transform[p][i][j][dx][dy]) { continue; }
            bool ok = true;
            for (int nxi = 0; nxi < n; ++nxi) {
              for (int nyi = 0; nyi < n; ++nyi) {
                if (nxi != 0 && nxi != n - 1) {
                  if (nyi == 1) { nyi = n - 1; }
                }

                if (!ok) { break; }
                int nx = nxi;
                int ny = nyi;
                int x = nxi - dx;
                int y = nyi - dy;
                if (!in_range(n, x) || !in_range(n, y) || g[p][x][y] == '.') { continue; }


                rotate(nx, ny, j);
                if (i) { swap(nx, ny); }
                if (p == 5) {
//                  printf("x %d y %d => p %c rot %d sym %d dx %d dy %d => %d %d\n", x, y, 'A' + p, j, i, dx, dy, nx, ny);
                }

                Point z = getPoint(nx, ny, k);
                if (field[z.x][z.y][z.z] != '.') {
                  ok = false;
                } else {
                  field[z.x][z.y][z.z] = g[p][x][y];
                }
              }
            }
            for (int x = 0; x < n; ++x) {
              for (int y = 0; y < n; ++y) {
                if (x != 0 && x != n - 1) {
                  if (y == 1) { y = n - 1; }
                }

                Point z = getPoint(x, y, k);
                cnt[z.x][z.y][z.z] -= 1;
                if (cnt[z.x][z.y][z.z] == 0 && field[z.x][z.y][z.z] == '.') {
                  ok = false;
                }
              }
            }
            if (ok) {
              order[k] = p;
//              printf("p %c rot %d sym %d dx %d dy %d\n", 'A' + p, j, i, dx, dy);
              brute(used_mask_g | (1 << p), k + 1);
              order[k] = -1;
            }
            for (int x = 0; x < n; ++x) {
              for (int y = 0; y < n; ++y) {
                if (x != 0 && x != n - 1) {
                  if (y == 1) { y = n - 1; }
                }

                Point z = getPoint(x, y, k);
                cnt[z.x][z.y][z.z] += 1;
                if (field[z.x][z.y][z.z] == 'A' + p) {
                  field[z.x][z.y][z.z] = '.';
                }
              }
            }
          }
        }
      }
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

#if LOCAL
  n = 10;
  vector<int> perm;
  for (int i = 0; i < 6; ++i) {
    perm.push_back(i);
  }
  random_shuffle(perm.begin(), perm.end());
  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < n; ++y) {
      for (int z = 0; z < n; ++z) {
        int mask = 0;
        if (x == 0) {
          mask |= (1 << 0);
        }
        if (y == 0) {
          mask |= (1 << 1);
        }
        if (z == 0) {
          mask |= (1 << 2);
        }
        if (x == n - 1) {
          mask |= (1 << 3);
        }
        if (y == n - 1) {
          mask |= (1 << 4);
        }
        if (z == n - 1) {
          mask |= (1 << 5);
        }
        if (mask) {
          int zz;
          do {
            zz = rand() % 6;
          } while ((mask & (1 << zz)) == 0);
          field[x][y][z] = (char)('A' + perm[zz]);
        } else {
          field[x][y][z] = '.';
        }
      }
    }
  }
  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < n; ++y) {
      printf("%s\n", field[x][y]);
    }
    printf("\n");
  }
  for (int i = 0; i < 6; ++i) {
    int j = 0;
    while (j < 6 && perm[j] != i) {
      ++j;
    }
    assert(j < 6);
    eprintf("i %d j %d\n", i, j);

    for (int x = 0; x < n; ++x) {
      for (int y = 0; y < n; ++y) {
        Point z = getPoint(x, y, j);
        char ch = field[z.x][z.y][z.z];
        if (ch != 'A' + i) {
          ch = '.';
        }
        g[i][x][y] = ch;
      }
    }
    for (int x = 0; x < n; ++x) {
      printf("%s\n", g[i][x]);
    }
    printf("\n");
  }
#else
  scanf("%d", &n);
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < n; ++j) {
      scanf("%s", g[i][j]);
    }
  }
#endif

  for (int i = 0; i < 6; ++i) {
    sq[i] = 0;
    for (int x = 0; x < 6; ++x) {
      for (int y = 0; y < 6; ++y) {
        if (g[i][x][y] != '.') {
          sq[i] += 1;
        }
      }
    }
  }

  for (int i = 0; i < 6; ++i) {
    int j = 0;
    while (j < n && g[i][0][j] == '.') {
      ++j;
    }
    if (j == n) {
      for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
          g[i][x][y] = (x == n - 1 ? '.' : g[i][x + 1][y]);
        }
      }
    }
  }
  for (int i = 0; i < 6; ++i) {
    int j = 0;
    while (j < n && g[i][j][0] == '.') {
      ++j;
    }
    if (j == n) {
      for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
          g[i][x][y] = (y == n - 1 ? '.' : g[i][x][y + 1]);
        }
      }
    }
  }


  for (int i = 0; i < 6; ++i) {
    for (int dx = 0; dx < 2; ++dx) {
      for (int dy = 0; dy < 2; ++dy) {
        bool ok = true;
        for (int x = 0; x < n; ++x) {
          for (int y = 0; y < n; ++y) {
            int nx = x + dx;
            int ny = y + dy;
            if (g[i][x][y] == '.') {
              if (0 < nx && nx < n - 1 && 0 < ny && ny < n - 1) {
                ok = false;
              }
              continue;
            }
            if (!in_range(n, nx) || !in_range(n, ny)) {
              ok = false;
              continue;
            }
          }
        }
        good_shift[i][dx][dy] = ok;
        if (ok) {
          good_shift_counts[i] += 1;
          eprintf("i %d dx %d dy %d\n", i, dx, dy);
        }
      }
    }
  }
  for (int p = 0; p < 6; ++p) {
    set<vector<pii>> used;
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 4; ++j) {
        for (int dx = 0; dx < 2; ++dx) {
          for (int dy = 0; dy < 2; ++dy) {
            if (!good_shift[p][dx][dy]) { continue; }
            vector <pii> vv;
            for (int nxi = 0; nxi < n; ++nxi) {
              for (int nyi = 0; nyi < n; ++nyi) {
                if (nxi != 0 && nxi != n - 1) {
                  if (nyi == 1) { nyi = n - 1; }
                }

                int nx = nxi;
                int ny = nyi;
                int x = nxi - dx;
                int y = nyi - dy;
                if (!in_range(n, x) || !in_range(n, y) || g[p][x][y] == '.') { continue; }

                rotate(nx, ny, j);
                if (i) { swap(nx, ny); }
                vv.push_back(pii(nx, ny));
              }
            }
            if (!used.count(vv)) {
              good_transform[p][i][j][dx][dy] = true;
              used.insert(vv);
            }
          }
        }
      }
    }
  }

  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < n; ++y) {
      for (int z = 0; z < n; ++z) {
        field[x][y][z] = '.';
        if (x == 0 || x == n - 1) {
          cnt[x][y][z] += 1;
        }
        if (y == 0 || y == n - 1) {
          cnt[x][y][z] += 1;
        }
        if (z == 0 || z == n - 1) {
          cnt[x][y][z] += 1;
        }
        if (cnt[x][y][z] == 0) {
          cnt[x][y][z] = 10;
        }
      }
    }
  }

  memset(order, 0xff, sizeof(order));
  brute(0, 0);
  assert(0);

  return 0;
}
