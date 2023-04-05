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
typedef unsigned long long ull;
typedef long double ld;

const int P1 = 23917;
const int P2 = 17239;

const int MAXN = 5000;


ull p1[3 * MAXN + 10];
ull p2[3 * MAXN + 10];

ull get_hash(int x, int y) {
  x += MAXN;
  y += MAXN;
  return p1[x] * p2[y];
}

ull C[MAXN + 1];
int cnt[MAXN + 1];


int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
#endif

  p1[0] = p2[0] = 1;
  for (size_t i = 1; i < sizeof(p1) / sizeof(p1[0]); i++) {
    p1[i] = p1[i - 1] * P1;
    p2[i] = p2[i - 1] * P2;
  }

  for (int i = -MAXN; i <= MAXN; i++) {
    for (int j = -MAXN; j <= MAXN; j++) {
      int d2 = i * i + j * j;
      int d = sqrt(d2);
      while (d * d > d2) d--;
      while (d * d < d2) d++;
      if (d < (int) (sizeof(C) / sizeof(C[0]))) {
        C[d] += get_hash(i, j);
        cnt[d]++;
      }
    }
  }

  for (int i = 1; i <= MAXN; i++) {
    C[i] += C[i - 1];
    cnt[i] += cnt[i - 1];
  }

  vector<int> miny(2 * MAXN + 1, 1e9);
  vector<int> maxy(2 * MAXN + 1, -1e9);

  int n;
  scanf("%d", &n);
  ll sumx = 0, sumy = 0;
  ull have_hash = 0;
  for (int i = 1; i <= n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    x += MAXN;
    y += MAXN;
    have_hash += get_hash(x, y);
    sumx += x;
    sumy += y;
    miny[x] = min(miny[x], y);
    maxy[x] = max(maxy[x], y);

    auto check = [&]() {
      if (sumx % i == 0 && sumy % i == 0) {
        int cx = sumx / i;
        int cy = sumy / i;
        if (0 <= cx && cx < (int) miny.size()) {
          int R = max(cy - miny[cx], maxy[cx] - cy);
          if (R < 0 || R > MAXN) return false;
          int lcnt = cnt[R] - i;
          int L = lower_bound(cnt, cnt + MAXN + 1, lcnt) - cnt;
          if (L == MAXN + 1 || cnt[L] != lcnt) return false;
          ull need_hash = (C[R] - C[L]) * p1[cx] * p2[cy];
          return need_hash == have_hash;
        }
      }
      return false;
    };

    if (check()) {
      printf("TAK\n");
    } else {
      printf("NIE\n");
    }
  }

  return 0;
}
