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

int A[3500][3500];
int B[3500][3500];

int D = 3500 / 2;

int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  char s[2];

  for (int i = 0; i < n; i++) {
    int x, y, d;
    scanf("%s%d%d%d", s, &x, &y, &d);
    x += D;
    y += D;
    if (s[0] == 'A') {
//      printf("%d %d %d\n", x, y, d);
      A[x + d / 2][y + d / 2]++;
      A[x + d / 2][y - d / 2]--;
      A[x - d / 2][y + d / 2]--;
      A[x - d / 2][y - d / 2]++;
    } else {
      B[x + d / 2][y]++;
      B[x][y - d / 2]--;
      B[x][y + d / 2]--;
      B[x - d / 2][y]++;
    }
  }
  for (int i = 2 * D - 2; i >= 2; i--) {
    for (int j = 2 * D - 2; j >= 2; j--) {
      A[i][j] = A[i][j] + A[i + 1][j] + A[i][j + 1] - A[i + 1][j + 1];
    }
  }
  for (int i = 2 * D - 3; i >= 2; i--) {
    for (int j = 2 * D - 2; j >= 2; j--) {
      B[i][j] = B[i][j] + B[i + 1][j + 1] + B[i + 1][j - 1] - B[i + 2][j];
    }
  }

  double res = 0;
  for (int i = 2; i < 2 * D - 2; i++) {
    for (int j = 2; j < 2 * D - 2; j++) {
      if (A[i][j]) {
        res += 1;
      } else {
        int q1 = (B[i][j] > 0 || B[i + 1][j] > 0);
        int q2 = (B[i + 1][j] > 0 || B[i + 1][j - 1] > 0);
        int q3 = (B[i][j] > 0 || B[i][j - 1] > 0);
        int q4 = (B[i][j - 1] > 0 || B[i + 1][j - 1] > 0);
        res += (q1 + q2 + q3 + q4) * 0.25;
      }
    }
  }

//  double res = 0;

  printf("%.18f", res);

  return 0;
}
