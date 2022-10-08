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

#define prev prev_i_love_std

const int MAXN = 110000;
int prev[MAXN];

template<typename comp>
vector<int> solve(const vector<int> &p) {
  vector<int> vals;
  vals.reserve(p.size());

  for (int x : p) {
    int id = lower_bound(vals.begin(), vals.end(), x, comp()) - vals.begin();
    if (id == (int)vals.size()) {
      vals.push_back(x);
    } else {
      vals[id] = x;
    }
    prev[x] = (id == 0) ? -1 : vals[id - 1];
    vals[id] = x;
  }

  vector<int> ans;
  ans.reserve(vals.size());
  int cur = vals.back();
  while (cur != -1) {
    ans.push_back(cur);
    cur = prev[cur];
  }
  reverse(ans.begin(), ans.end());
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t --> 0) {
    int n;
    scanf("%d", &n);
    vector<int> p(n);
    for (int &x : p) {
      scanf("%d", &x);
    }
    vector<int> pbk = p;

    vector<vector<int>> ans;

    auto remove = [&](const vector<int>&to_remove) {
      vector<int> np;
      np.reserve(p.size() - to_remove.size());
      for (int x : p) {
        if (!binary_search(to_remove.begin(), to_remove.end(), x)) {
          np.push_back(x);
        }
      }
      p = np;
    };

    while (!p.empty()) {
      double s = (int)sqrt(p.size());
      while (!p.empty()) {
        vector<int> res = solve<less<int>>(p);
        if ((int)res.size() >= s) {
          ans.push_back(res);
        } else {
          break;
        }
        remove(res);
      }
      while (!p.empty()) {
        vector<int> res = solve<greater<int>>(p);
        if ((int)res.size() >= s) {
          ans.push_back(res);
        } else {
          break;
        }
        reverse(res.begin(), res.end());
        remove(res);
      }
    }

//    if ((ans.size() - 1) * (ans.size() - 1) < (size_t)n) {
//      eprintf("%d\n", (int)pbk.size());
//      for (int x : pbk) {
//        eprintf("%d ", x);
//      }
//      eprintf("\n");
//      eprintf("ans = %d\n", (int)ans.size());
//      assert(false);
//    }

    printf("%d\n", (int)ans.size());
    for (const auto& x : ans) {
      printf("%d", (int)x.size());
      for (int y : x) {
        printf(" %d", y);
      }
      printf("\n");
    }

  }

  return 0;
}
