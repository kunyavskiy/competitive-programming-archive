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

ll calc(int at_most0, int at_most1,  int same_parity) {
  ll ans = 0;
  for (int i = 0; i <= at_most0 || i <= at_most1; i++) {
    if ((i >= same_parity || i % 2 == 0) && ((i % 2 == 0 && i <= at_most0) || (i % 2 == 1 && i <= at_most1))) {
      ans += i;
    }
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  vector<pair<int, int>> v(n);

  vector<vector<int>> starts(m);
  vector<vector<int>> ends(m);

  for (int i = 0; i < n; i++) {
    auto& x = v[i];
    scanf("%d%d", &x.first, &x.second);
    --x.first;
    --x.second;
    starts[x.first].push_back(i);
    ends[x.second].push_back(i);
  }

  int at_least[2] = {0, 0};
  multiset<int> same_parity[2];

  ll ans = 0;

  for (int r = 0; r < m; r++) {
    ans += calc(r - at_least[r % 2] + 1, r - at_least[(r % 2) ^ 1] + 1, (same_parity[r % 2].empty() ? 0 : r - *same_parity[r % 2].begin() + 1));

    for (int id : starts[r]) {
      same_parity[0].insert(v[id].first);
      same_parity[1].insert(v[id].first);
    }
    for (int id : ends[r]) {
      same_parity[0].erase(same_parity[0].find(v[id].first));
      same_parity[1].erase(same_parity[1].find(v[id].first));

      int lf = v[id].first;
      int rg = v[id].second;

      if ((rg - lf + 1) % 2 == 0) {
        at_least[r % 2] = max(at_least[0], lf + 1);
        at_least[(r % 2) ^ 1] = max(at_least[1], rg + 1);
      }
    }
  }

  return 0;
}
