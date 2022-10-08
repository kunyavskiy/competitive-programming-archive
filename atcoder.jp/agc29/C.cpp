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

bool check(const vector<int>& a, int n) {
  vector<pair<int, int>> p;
  int sum = 0;
  for (int x : a) {
    if (sum >= x) {
      while (sum - p.back().second >= x) {
        sum -= p.back().second;
        p.pop_back();
      }
      assert(!p.empty());
      p.back().second = x - (sum - p.back().second);
      sum = x;
      while (!p.empty() && (p.back().first == n - 1 || p.back().second == 0)) {
        sum -= p.back().second;
        p.pop_back();
      }
      if (p.empty()) {
        return false;
      }
      if (p.back().second == 1) {
        p.back().first++;
      } else {
        p.back().second--;
        p.emplace_back(p.back().first + 1, 1);
      }
    }
    if (x > sum) {
      p.push_back({0, x - sum});
      sum = x;
    }
  }
  return true;
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> a(n);
    for (int& x : a) {
      scanf("%d", &x);
    }

    int l = 0;
    int r = n;
    while (r - l > 1) {
      int m = (l + r) / 2;
      if (check(a, m)) {
        r = m;
      } else {
        l = m;
      }
    }
    printf("%d\n", r);
  }

  return 0;
}
