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

static const int INF = 1e9;

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n, m, k;
  while (scanf("%d%d%d", &n, &m, &k)== 3) {
    set<pair<int, int>> s;
    for (int i = 0; i < k; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      s.insert({x, y});
    }

    map<int, vector<int>> parts;

    for (auto p : s) {
      if (!s.count({p.first - 1, p.second})) {
        parts[2 * (p.first - 1) + 1].push_back(p.second);
      }
      if (p.first != n - 1 && !s.count({p.first + 1, p.second})) {
        parts[2 * p.first + 1].push_back(p.second);
      }
      if (p.second != 0 && !s.count({p.first, p.second - 1})) {
        parts[2 * p.first].push_back(p.second);
      }
      if (!s.count({p.first, p.second + 1})) {
        parts[2 * p.first].push_back(p.second + 1);
      }
    }

    vector<int> res;
    for (const auto& x : parts ) {
      vector<int> v = x.second;
      if (x.first % 2 == 0) {
        sort(v.rbegin(), v.rend());
      } else {
        sort(v.begin(), v.end());
      }
      for (auto a : v) {
        res.push_back(-a);
      }
    }

    vector<int> ans(res.size(), INF);
    for (int x : res) {
      *lower_bound(ans.begin(), ans.end(), x) = x;
    }

    int tot = 0;
    for (int x : ans) {
      if (x != INF) tot++;
    }

    printf("%d\n", tot);


  }

  return 0;
}
