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

static const int MAXN = 1000100;
vector<int> g[MAXN];
int q[MAXN];

int dfs(int x, int p) {
  int s = 1;
  for (int y : g[x]) {
    if (y != p) {
      int t = dfs(y, x);
      q[t]++;
      s += t;
    }
  }
  return s;
}

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    x--;y--;
    g[x].push_back(y);
    g[y].push_back(x);
  }

  dfs(0, -1);

  for (int i = n - 1; i >= 1; i--) {
    if (n % i) continue;
    int cnt = 0;
    for (int j = i; j < n; j += i) {
      cnt += q[j];
    }
    if (cnt == (n / i - 1)) {
      printf("%d ", cnt);
    }
  }
  printf("\n");
  return 0;
}
