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

int main() {
#ifdef LOCAL
//  freopen("e.in", "r", stdin);
//  freopen("e.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);

  int moves = 0;
  while (2 * (1 << moves) - 1 < n) {
    moves++;
  }

  printf("%d\n", moves);
  fflush(stdout);
  int k;
  scanf("%d", &k);
  assert(k == 1);

  int m = 1;

  for (int it = 0; it < moves; it++) {
    int y;
    scanf("%d", &y);
    if (y == -1 || y == 0) break;

    int g = __gcd(m, y);
    ll nm = m / g * 1LL * y;
    assert(nm != m);
    if (nm > n) {
      printf("%d\n", (m - 1) % y);
    } else {
      printf("%d\n", y - 1);
      m = nm;
    }
    fflush(stdout);
  }

  return 0;
}
