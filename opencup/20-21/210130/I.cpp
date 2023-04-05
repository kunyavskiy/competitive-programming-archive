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

const int MAX = 1.1e6;

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  vector<vector<int>> divs(MAX);
  for (int i = 1; i < MAX; i++) {
    for (int j = 2 * i; j < MAX; j += i) {
      divs[j].push_back(i);
    }
  }

  TIMESTAMP(init);

  int t;
  scanf("%d", &t);
  while (t-->0) {
    vector<int> cnt(MAX);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
      int a;
      scanf("%d", &a);
      cnt[a]++;
    }
    long long ans = 0;
    for (int i = 0; i < MAX; i++) {
      for (int j : divs[i]) {
        if ((i & j) == j) {
          ans += cnt[i] * 1LL * cnt[i-j];
        }
      }
    }
    printf("%lld\n", ans);
  }


  return 0;
}
