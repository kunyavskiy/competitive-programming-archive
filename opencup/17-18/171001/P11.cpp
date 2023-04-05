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

const int MAXN = 50;

ll g[MAXN];
ll e[MAXN];
int n;

int calc(ll e, ll g) {
  return __builtin_popcountll(g & ~e);
}

map<ll, int> dp;

int solve(ll have) {
  auto it = dp.find(have);
  if (it != dp.end()) {
    return it->second;
  }
  int& res = dp[have];
  res = -1000000;
  bool any = false;
  for (int i = 0; i < n; i++) {
    if (!(g[0] & (1LL << i))) continue;
    ll extra = ~have & g[i];
    if (extra) {
      res = max(res, solve(have | g[i]) + calc((e[0] & (1LL << i)) ? ~e[i] : e[i], extra));
      any = true;
    }
  }
  if (!any) {
    res = 0;
  }
  return res;
}

vector<int> r;

void restore(ll have) {
  auto it = dp.find(have);
  assert(it != dp.end());
  int res = it->second;
  for (int i = 0; i < n; i++) {
    if (!(g[0] & (1LL << i))) continue;
    ll extra = ~have & g[i];
    if (extra) {
      int cur = solve(have | g[i]) + calc((e[0] & (1LL << i)) ? ~e[i] : e[i], extra);
      if (res == cur) {
        r.push_back(i);
        return restore(have | g[i]);
      }
    }
  }
  assert(res == 0);
}


int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    --a, --b;
    g[a] |= 1LL << b;
    g[b] |= 1LL << a;
    if (c) {
      e[a] |= 1LL << b;
      e[b] |= 1LL << a;
    }
  }

  int res = solve(g[0] | 1) + calc(e[0], g[0]);
  printf("%.10lf\n", res * 1.0 / (n - 1));
  restore(g[0] | 1);

  for (int i = 0; i < n; i++) {
    if (g[0] & (1LL << i)) {
      if (find(r.begin(), r.end(), i) == r.end()) {
        r.push_back(i);
      }
    }
  }

  for (int x : r) {
    printf("%d ", x + 1);
  }
  printf("\n");

  return 0;
}
