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

struct dsu {
  vector<int> p;

  explicit dsu(int n) : p(n) {
    for (int i = 0; i < n; i++) p[i] = i;
  }

  void join(int a, int b) {
    a = get(a);
    b = get(b);
    p[a] = b;
  }

  int get(int a) {
    if (a == p[a]) return a;
    return p[a] = get(p[a]);
  }

};


bool solve(int n, int m, int q) {
  vector<pair<int, int>> bs;
  dsu d(n);
  for (int i = 0; i <q ; i++) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    if (c == 0) {
      d.join(a, b);
    } else {
      bs.emplace_back(a, b);
    }
  }
  for (auto x : bs) {
    if (d.get(x.first) == d.get(x.second)) {
      return false;
    }
  }
  int comps = 0;
  for (int i = 0; i < n; i++) {
    if (d.get(i) == i) {
      comps++;
    }
  }
  if (comps < 3 && !bs.empty()) {
    return false;
  }

  ll min_edges = bs.empty() ? n - 1 : n;
  ll max_edges = (n - comps) + comps * 1LL * (comps - 1) / 2;
  return min_edges <= m && m <= max_edges;
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n, m, q;
  while (scanf("%d%d%d", &n, &m, &q) == 3) {
    printf("%s\n", solve(n, m, q) ? "Yes" : "No");
  }


  return 0;
}
