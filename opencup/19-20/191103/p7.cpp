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

const int MAX = 18;

int jmp[12][MAX][100000];

int main() {
#ifdef LOCAL
  freopen("p7.in", "r", stdin);
  freopen("p7.out", "w", stdout);
#endif

  int h, w, k, q;
  scanf("%d%d%d%d", &h, &w, &k, &q);

  vector<string> a(h);
  static char buf[100010];

  for (int i = 0; i < h; i++) {
    scanf("%s", buf);
    a[i] = buf;
  }

  vector<vector<int>> nx(h, vector<int>(w));

  for (int i = 0; i < h; i++) {
    for (int j = w - 1; j >= 0; j--) {
      if (a[i][j] == 'X') {
        nx[i][j] = j;
      } else {
        if (j == w - 1) {
          nx[i][j] = w;
        } else {
          nx[i][j] = nx[i][j + 1];
        }
      }
    }
    for (int j = 0; j < w; j++) {
      if (j + k >= w) {
        jmp[i][0][j] = w;
      } else {
        jmp[i][0][j] = nx[i][j + k];
      }
    }
    for (int t = 1; t < MAX; t++) {
      for (int j = 0; j < w; j++) {
        int x = jmp[i][t - 1][j];
        if (x < w) {
          x = jmp[i][t - 1][x];
        }
        jmp[i][t][j] = x;
      }
    }
  }

  for (int ttt = 0; ttt < q; ttt++) {
    int d, l, r;
    scanf("%d%d%d", &d, &l, &r);
    l--;
    int res = 0;
    for (int i = 0; i < d; i++) {
      int j = nx[i][l];
      if (j < r) {
        for (int t = MAX - 1; t >= 0; t--) {
          if (jmp[i][t][j] < r) {
            res += (1 << t);
            j = jmp[i][t][j];
          }
        }
        res++;
      }
    }
    printf("%d\n", res);
  }


  return 0;
}
