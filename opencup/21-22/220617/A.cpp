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
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int n, k, m;
  while (scanf("%d%d%d", &n, &k, &m) == 3) {
    vector<int> c(k);
    for (int i = 0; i < n; i++) {
      int cc;
      scanf("%d", &cc);
      c[cc - 1] |= (1 << i);
    }
    vector<int> covered(1 << m);
    for (int i = 0; i < m; i++) {
      int s;
      scanf("%d", &s);
      for (int j = 0; j < s; j++) {
        int a;
        scanf("%d", &a);
        --a;
        covered[1 << i] |= (1 << a);
      }
    }
    for (int j = 0; j < (1 << m); j++) {
      covered[j] = covered[j & (j - 1)] | covered[j & ~(j - 1)];
    }

    auto encode = [&](int a, int b) { return (a << m) | b;};
    auto decode = [&](int a) { return pair{a >> m, a & ((1 << m) - 1)};};
    vector<int> d(1 << (n + m), -1);
    int start = encode(c[0], 0);
    d[start] = 0;
    queue<int> q;
    q.push(start);
    while (!q.empty()) {
      int cur = q.front(); q.pop();
      auto [correct, on] = decode(cur);
      auto reach = [&](int to) {
        if (d[to] == -1) {
//          auto [a, b] = decode(cur);
//          auto [C, D] = decode(to);
//          eprintf("(%d, %d) -> (%d, %d) [%d]\n",a ,b,C,D, d[cur]);
          d[to] = d[cur] + 1;
          q.push(to);
        }
      };
      for (int i = 0; i < m; i++) {
        reach(encode(correct, on ^ (1 << i)));
      }
      for (int cc = 0; cc < k; cc++) {
        reach(encode((correct & covered[on]) | (~covered[on] & c[cc]), on));
      }
    }
    printf("%d\n", d[encode((1 << n) - 1, 0)]);
  }

  return 0;
}
