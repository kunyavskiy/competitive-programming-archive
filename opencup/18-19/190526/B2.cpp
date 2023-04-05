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

int coefs[4][40];
int n;

bool go(int s, int ln, int side, int sum) {
  if (s == 0) {
    return true;
  }
  int lf_id = s;
  int rg_id = n - (ln == 3) - s - 1;
  int len = n - (ln == 3);
  if (side == 2) {
    for (int i = 0; i + s < len; i++) {
      assert(coefs[ln][i] && coefs[ln][i + s]);
      sum += coefs[ln][i] * coefs[ln][i + s] * (1 + (ln >= 2));
    }
    return go(s, ln + 1, 0, sum);
  }
  if (ln == 2 && side == 0 && sum % 4 == 0) {
    return false;
  }
  if (ln == 4) {
    if (sum != 0) return false;
    return go(s - 1, 0, 0, 0);
  }
  if (lf_id < 0 || rg_id >= len) {
    return go(s, ln, side + 1, sum);
  }
  int &val = coefs[ln][side == 0 ? lf_id : rg_id];
  if (val) {
    return go(s, ln, side + 1, sum);
  }
  val = -1;
  if (go(s, ln, side + 1, sum)) return true;
  val = 1;
  if (go(s, ln, side + 1, sum)) return true;
  val = 0;
  return false;
}

int main() {
#ifdef LOCAL
  freopen("b2.in", "r", stdin);
  freopen("b2.out", "w", stdout);
#endif

  for (int i = 0; i < 4; i++) {
    char buf[200];
    scanf("%s", buf);
    if (i == 0) n = strlen(buf);
    for (int j = 0; j < n; j++) {
      if (buf[j] == '+') {
        coefs[i][j] = 1;
      } else if (buf[j] == '-') {
        coefs[i][j] = -1;
      } else {
        coefs[i][j] = 0;
      }
    }
  }

  bool res = go(n - 1, 0, 0, 0);
  assert(res);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < n - (i == 3); j++) {
      printf("%c", (coefs[i][j] == 1) ? '+' : '-');
    }
    printf("\n");
  }

  return 0;
}
