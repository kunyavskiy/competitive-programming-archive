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

int readTime();

#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

const int MAXT = 86400;

int readTime() {
  int h, m, s;
  assert(scanf("%d:%d:%d", &h, &m, &s) == 3);
  return (h * 60 + m) * 60 + s;
}

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int n, c;
  while (scanf("%d%d", &n, &c) == 2) {
    eprintf("=====\n");
    vector<vector<pair<int, int>>> edges(MAXT + 1);
    for (int i = 0; i < n; i++) {
      int t1 = readTime();
      int t2 = readTime();
      assert(0 <= t1 && t1 < t2 && t2 < MAXT);
      int p;
      scanf("%d", &p);
      p -= c * (t2 - t1);
      if (p > 0) {
        eprintf("%d-->%d (profit=%d)\n", t1, t2, p);
        edges[t1].emplace_back(t2, p);
      }
    }

    vector<ll> dyn(MAXT + 1, 0);
    for (int i = 0; i < MAXT; i++) {
      dyn[i + 1] = max(dyn[i + 1], dyn[i]);
      for (auto &e : edges[i]) {
        dyn[e.first] = max(dyn[e.first], dyn[i] + e.second);
      }
    }
    printf("%lld\n", dyn[MAXT]);
  }
  return 0;
}
