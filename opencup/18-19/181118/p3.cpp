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

const int MINS = 100;
const int MAXS = 10000;
const int W = 30;
const int H = 16;

int f[MAXS + 1][H][W];
vector<int> alive;

int cnt[H][W][10];
bool done[H][W];

#ifdef LOCAL
#define TEST
#endif

int real = 0;
int failed = 0;

int ask(int x, int y) {
#ifdef TEST
  if (f[real][x][y] == -1) {
    failed++;
    assert(failed < 6);
  }
  eprintf("ask %d %d %d\n", x, y, f[real][x][y]);
  return f[real][x][y];
#else
  printf("%d %d\n", x, y);
  fflush(stdout);
  static char buf[200];
  scanf("%s", buf);
  if (!strcmp(buf, "Boom")) {
    return -1;
  } else if (!strcmp(buf, "Win")) {
    exit(0);
  } else if (!strcmp(buf, "Loose")) {
    exit(0);
  } else if (!strcmp(buf, "Empty")) {
    int r;
    scanf("%d", &r);
    return r;
  } else {
    assert(0);
  }
#endif
}

int main() {
#ifdef LOCAL
  freopen("p3.in", "r", stdin);
//  freopen("p3.out", "w", stdout);
#endif

  real = rand() % 9900 + 100;
  eprintf("seed = %d\n", real);

  int w, h, k;
  scanf("%d%d%d", &h, &w, &k);

  assert(w == W);
  assert(h == H);

  for (int s = MINS; s <= MAXS; s++) {
    alive.push_back(s);
    int t = s;
    int kk = k;
    for (; kk; ) {
      t = (t * 48271LL) % 2147483647;
      int r = (t / W) % H;
      int c = (t % W);
      if (f[s][r][c] != -1) {
        --kk;
        f[s][r][c] = -1;
      }
    }

    for (int i = 0; i < H; i++) {
      for (int j = 0; j < W; j++) {
        if (f[s][i][j] != -1) {
          for (int di = -1; di <= 1; di++) {
            for (int dj = -1; dj <= 1; dj++) {
              if (di || dj) {
                int ni = i + di;
                int nj = j + dj;
                if (0 <= ni && ni < H && 0 <= nj && nj < W) {
                  if (f[s][ni][nj] == -1) {
                    f[s][i][j]++;
                  }
                }
              }
            }
          }
        }
        cnt[i][j][f[s][i][j]+1]++;
      }
    }
  }

  int opened = 0;
  while (opened != H * W - k) {
    int bestx = -1, besty = -1;
    int score = alive.size() * 2;
    for (int i = 0; i < H; i++) {
      for (int j = 0; j < W; j++) {
        if (done[i][j]) continue;
        if (cnt[i][j][0] == 0) {
          bestx = i;
          besty = j;
          score = 0;
        } else {
          int sc = *max_element(cnt[i][j], cnt[i][j] + 10);
          if (score > sc) {
            score = sc;
            bestx = i;
            besty = j;
          }
        }
      }
    }
    assert(bestx != -1);

    done[bestx][besty] = true;
    int r = ask(bestx, besty);
    if (r != -1) {
      opened++;
    }

    for (int s = 0; s < (int)alive.size(); s++) {
      if (f[alive[s]][bestx][besty] != r) {
        for (int i = 0; i < H; i++) {
          for (int j = 0; j < W; j++) {
            cnt[i][j][f[alive[s]][i][j]+1]--;
          }
        }

        swap(alive[s], alive.back());
        alive.pop_back();
        s--;
      }
    }
  }


  return 0;
}
