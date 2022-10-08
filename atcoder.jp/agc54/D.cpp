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
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  static char buf[8100];
  while (scanf("%s", buf) == 1) {
    vector<int> opens;
    vector<int> closes;
    vector<int> oxs;
    int n = strlen(buf);

    vector<int> cntopenbef(n), cntclosebef(n), cntoxbef(n);

    for (int i = 0; i < n; i++) {
      if (buf[i] == '(') {
        opens.push_back(i);
      } else if (buf[i] == ')') {
        closes.push_back(i);
      } else if (buf[i] == 'o' || buf[i] == 'x') {
        oxs.push_back(i);
      }
    }
    for (int i = 1; i < n; i++) {
      cntopenbef[i] = cntopenbef[i - 1] + (buf[i - 1] == '(');
      cntclosebef[i] = cntclosebef[i - 1] + (buf[i - 1] == ')');
      cntoxbef[i] = cntoxbef[i - 1] + (buf[i - 1] == 'o' || buf[i - 1] == 'x');
    }


    vector<vector<int>> dp1(opens.size() + 1, vector<int>(closes.size() + 1, numeric_limits<int>::max()));
    vector<vector<int>> dp2(opens.size() + 1, vector<int>(oxs.size() + 1, numeric_limits<int>::max()));
    vector<vector<int>> dp3(opens.size() + 1, vector<int>(oxs.size() + 1, numeric_limits<int>::max()));

    auto dp = [&](int cntopen, int cntclose, int cntxs) -> int & {
      return (cntopen == cntclose) ? dp2[cntopen][cntxs] : ((cntopen == cntclose + 1) ? dp3[cntopen][cntxs] : dp1[cntopen][cntclose]);
    };

    /*vector<vector<vector<int>>> dp_(opens.size() + 1,
                                   vector<vector<int>>(closes.size() + 1,
                                                       vector<int>(oxs.size() + 1, numeric_limits<int>::max())));
    auto dp = [&](int cntopen, int cntclose, int cntoxs) -> int & {
      return dp_[cntopen][cntclose][cntoxs];
    };*/

    dp(0, 0, 0) = 0;

    auto get_or_n = [&](const vector<int>& v, int pos) {
      if (pos >= (int)v.size()) return n;
      return v[pos];
    };

    auto upd = [](int& x, int y) {
      x = min(x, y);
    };

    for (int cntopen = 0; cntopen <= (int) opens.size(); cntopen++) {
      for (int cntclose = 0; cntclose <= cntopen; cntclose++) {
        int min_pos = min(closes[cntclose], get_or_n(opens, cntopen));
        int min_cntox, max_cntox;
        if (cntopen - cntclose >= 2) {
          min_cntox = max_cntox = cntoxbef[min_pos];
        } else {
          min_cntox = 0;
          max_cntox = oxs.size();
        }
        for (int cntox = min_cntox; cntox <= max_cntox; cntox++) {
          int cur = dp(cntopen, cntclose, cntox);
          if (cur == numeric_limits<int>::max()) continue;
          eprintf("dp[%d][%d][%d] = %d\n", cntopen, cntclose, cntox, cur);
          auto get_cost = [&](int pos) {
            return cur +
                   max<int>(0, cntopenbef[pos] - cntopen) +
                   max<int>(0, cntclosebef[pos] - cntclose) +
                   max<int>(0, cntoxbef[pos]  - cntox);
          };
          if (cntopen < (int) opens.size()) {
            upd(dp(cntopen + 1, cntclose, cntox), get_cost(opens[cntopen]));
          }
          if (cntclose < cntopen) {
            upd(dp(cntopen, cntclose + 1, cntox), get_cost(closes[cntclose]));
          }
          if (cntox < (int)oxs.size() && (cntclose <= cntopen - 1 || buf[oxs[cntox]] == 'o')) {
            upd(dp(cntopen, cntclose, cntox + 1), get_cost(oxs[cntox]));
          }
        }
      }
    }

    printf("%d\n", dp(opens.size(), closes.size(), oxs.size()));
  }

  return 0;
}
