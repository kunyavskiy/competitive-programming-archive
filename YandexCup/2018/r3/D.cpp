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

vector<int> val;
vector<bool> is;
vector<vector<int>> g;
bool fail;

pair<double, double> check(int v, int p, double m) {
  pair<double, double> res{-1e18, 1e18};

  for (int u : g[v]) {
    if (u == p) continue;
    auto r = check(u, v, m);
    res.first = max(res.first, r.first - m);
    res.second = min(res.second, r.second + m);
  }
  if (is[v]) {
    res.first = max(res.first, (double)val[v]);
    res.second = min(res.second, (double)val[v]);
  }
  if (res.first > res.second) fail = true;
  return res;
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    val.resize(n);
    is.resize(n);
    g = vector<vector<int>>(n);
    for (int i = 0; i < n; i++) {
      if (scanf("%d", &val[i]) != 1) {
        scanf(" *");
        is[i] = false;
      } else {
        is[i] = true;
      }
    }
    for (int i = 1; i < n; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a, --b;
      g[a].push_back(b);
      g[b].push_back(a);
    }

    double l = 0;
    double r = 2e7;

    for (int i = 0; i < 100; i++) {
      fail = false;
      double m = (l + r) / 2;
      check(0, -1, m);
      if (fail) {
        l = m;
      } else {
        r = m;
      }
    }
    printf("%.10lf\n", (l + r) / 2);
  }

  return 0;
}
