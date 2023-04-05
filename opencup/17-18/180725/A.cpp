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

const int MAXN = 1e6 + 10;

#define FAST_ALLOCATOR_MEMORY 200 << 20

int allocator_pos = 0;
char allocator_memory[(int)FAST_ALLOCATOR_MEMORY];
inline void * operator new ( size_t n ) {
  char *res = allocator_memory + allocator_pos;
  allocator_pos += n;
  assert(allocator_pos <= (int)FAST_ALLOCATOR_MEMORY);
  return (void *)res;
}
inline void operator delete ( void * ) noexcept { }


int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  vector<vector<int>> divs(MAXN);

  for (int i = 1; i < MAXN; i++) {
    for (int j = i; j < MAXN; j += i) {
      divs[j].push_back(i);
    }
  }

  TIMESTAMP(divs);

  vector<ll> ans(MAXN, -1);

  for (int i = 1; i < MAXN; i++) {
    int sz = divs[i].size();
    for (int j = 2; j <= 3; j++) {
      if (i % j != 0) continue;
      int a = i / j;
      for (int k = 0; k < sz; k++) {
        int b = divs[i][k];
        int c = i - a - b;
        if (c > 0 && i % c == 0) {
          ans[i] = max(ans[i], a * 1LL * b * c);
        }
      }
    }
  }

  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int x;
    scanf("%d", &x);
    printf("%lld\n", ans[x]);
  }

  return 0;
}
