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

bool is_win(ld d) {
  ll K = (ll)(d / 2.0);
  if (K % 2 == 0) {
    return false;
  } else {
    return true;
  }
}

bool solve() {
  int r, h;
  if (scanf("%d%d", &r, &h) != 2) return false;

//  h -= 2 * r;
//  ld H = h / (long double)r;
//  ld d1 = sqrt(H * H + 1);
//  ld d2 = sqrt(H * H + ld(1)/4.0);
//  if (is_win(d1) && is_win(d2)) {
//    printf("2\n");
//  } else {
//    printf("1\n");
//  }

  const long double PERIOD = sqrt(ld(15));// + sqrt((long double)3.0);
  long double H = h / (long double)r;
  H -= 2;
  int K = (int)(H / PERIOD);

  eprintf("H %.10lf\n", (double)H);

  for (int i = -10; i <= 10; ++i) {
    if (i + K < 0) { continue; }
    long double L = sqrt((long double)15.0) / 2 + (i + K) * PERIOD;
    long double R = PERIOD + (i + K) * PERIOD;
    if (L <= H && H <= R) {
      printf("2\n");
      return true;
    }
  }
  printf("1\n");

  return true;
}

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  while (solve());

  return 0;
}
