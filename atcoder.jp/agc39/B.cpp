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

  int n;
  while (scanf("%d", &n) == 1) {
    vector<vector<int>> g(n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        char c;
        scanf(" %c", &c);
        if (c == '1') {
          g[i].push_back(j);
        }
      }
    }
    int ans = -1;
    for (int s = 0; s < n; s++) {
      vector<int> d(n, -1);
      d[s] = 1;
      queue<int> q;
      q.push(s);
      bool fail = false;
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
          if (d[v] == d[u]) fail = true;
          if (d[v] == -1) {
            d[v] = d[u] + 1;
            q.push(v);
          }
        }
      }
      if (!fail) {
        ans = max(ans, *max_element(d.begin(), d.end()));
      }
    }
    printf("%d\n", ans);
  }

  return 0;
}
