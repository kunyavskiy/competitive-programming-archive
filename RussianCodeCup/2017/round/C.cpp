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

set<pair<int, int>> s;

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

void dfs(pair<int, int> p, vector<pair<int, int>> &v, int k) {
  if (s.find(p) == s.end()) return;
  if ((int)v.size() == k) return;
  s.erase(p);
  v.push_back(p);
  for (int i = 0; i < 4; i++) {
    dfs({p.first + dx[i], p.second + dy[i]}, v, k);
  }
}

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  s.clear();

  if (2 * n < k) while (true);
  vector<pair<int, int>> v(n);
  for (auto& x : v) {
    scanf("%d%d", &x.first, &x.second);
  }
  int maxx = max_element(v.begin(), v.end())->first;
  for (const auto& x : v) {
    s.insert({2 * maxx - x.first + 1, x.second});
  }
  dfs(*s.begin(), v, k);
  if ((int)v.size() < k && !s.empty()) {
    while (true);
  }
  assert((int)v.size() == k);
  printf("%d\n", k);
  for (auto x : v) {
    printf("%d %d\n", x.first, x.second);
  }
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);

  while (t --> 0) {
    solve();
  }

  return 0;
}
