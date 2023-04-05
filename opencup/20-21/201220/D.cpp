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


ll solve(vector<int> d) {
  int n = d.size();
  vector<int> order;
  vector<int> inv_order;
  vector<int> lcp;

  auto set_pos = [&](int pos, int val, int l) {
    order[pos] = val;
    inv_order[val] = pos;
    lcp[val] = l;
  };

  auto insert = [&](int pos, int val, int l) {
    order.push_back(-1);
    inv_order.push_back(-1);
    lcp.push_back(-1);
    for (int i = order.size() - 1; i >= 0; i--) {
      set_pos(i, order[i - 1], lcp[i - 1]);
    }

    set_pos(pos, val, l);
  };

  auto get = [&](int pos, int len) {
    return (pos + len >= n ? numeric_limits<int>::max(): (d[pos + len] <= len ? d[pos + len] : -1));
  };

  int cur_pos = 0;
  int cur_lcp = 0;
  long long ans = n;

  insert(0, 0, 0);

  for (int i = 1; i < (int)d.size(); i++) {
    while (true) {
      while (cur_pos < (int) order.size() && lcp[cur_pos] > cur_lcp) {
        cur_pos++;
      }
      if (cur_pos == (int)order.size() || (cur_pos && lcp[cur_pos] < cur_lcp)) {
        break;
      }
//      eprintf("checking %d %d at pos %d: %d and %d\n", order[cur_pos], i, cur_lcp, get(order[cur_pos], cur_lcp), get(i, cur_lcp));
      if (get(order[cur_pos], cur_lcp) < get(i, cur_lcp)) {
        cur_pos++;
        continue;
      }
      if (get(order[cur_pos], cur_lcp) == get(i, cur_lcp)) {
        cur_lcp++;
        continue;
      }
      break;
    }
    insert(cur_pos, i, cur_lcp);
    eprintf("%d %d\n", i, cur_lcp);
    ans += (n - i - cur_lcp);
    cur_lcp--;
    if (cur_lcp == 0 || cur_pos == 0) {
      cur_pos = cur_lcp = 0;
    } else {
      assert(cur_pos);
      cur_pos = inv_order[order[cur_pos - 1] + 1];
    }
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif
  int n;
  string s;
  while (cin >> n >> s) {
    vector<int> diffs(s.size());
    vector<int> last(26, -1);
    for (int i = 0; i < (int)s.size();i++) {
      diffs[i] = i - last[s[i] - 'a'];
      last[s[i] - 'a'] = i;
    }
    printf("%lld\n", solve(diffs));
  }

  return 0;
}
