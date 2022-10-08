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
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  const int K = 15;

  for (int i = 0; i < (1 << K); i++) {
    bool found = false;
    for (int j = 0; j < K && !found; j++) {
      map<int, int> cnt;
      int mask = (1 << j) - 1;
      for (int k = 0; k + j <= K; k++) {
        cnt[(i >> k) & mask]++;
      }
      for (auto [a, b] : cnt) {
        if (b == 1) {
          found = true;
          if (j == 7) {
            for (int x = 0; x < K; x++) {
              eprintf("%d", (i >> x) & 1);
            }
            eprintf(" ");
            for (int x = 0; x < j; x++) {
              eprintf("%d", (a >> x) & 1);
            }
            eprintf("\n");
            break;
          }
        }
      }
    }
  }

  int n, k;
  while (scanf("%d%d", &n, &k) == 2) {
    for (int i = 0; i < (n - k) / 2; i++) printf("0");
    for (int i = 0; i < k; i++) printf("1");
    for (int i = 0; i < (n - k) / 2; i++) printf("0");
    printf("\n");
  }

  return 0;
}
