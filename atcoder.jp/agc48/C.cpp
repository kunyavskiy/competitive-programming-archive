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

ll solve_left(vector<int> a, vector<int> b) {
  for (int i = 1; i < (int)a.size(); i++) {
    assert(a[i] > b[i]);
  }
  ll ans = 0;
  while (b.back() != 0) {
    int val = b.back();
    int cnt = 0;
    while (b.back() == val) {
      b.pop_back();
      a.pop_back();
      cnt++;
    }
    int id = upper_bound(a.begin(), a.end(), val) - a.begin() - 1;
    assert(id >= 0);
    if (a[id] != val) {
      return -1;
    }
    ans += cnt + a.size() - id - 1;
  }
  while (a.back() != 0) {
    a.pop_back();
    ans++;
  }
  return ans;
}

ll solve_right(vector<int> a, vector<int> b) {
  for (int i = 0; i < (int)a.size(); i++) {
    a[i] = a.back() - a[i];
    b[i] = b.back() - b[i];
  }
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  for (int i = 1; i < (int)a.size(); i++) {
    if (b[i] >= a[i]) {
      return -1;
    }
  }
  return solve_left(a, b);
}

ll solve_all_move(vector<int> a, vector<int> b) {
  for (int i = 1; i < (int)a.size(); i++) {
    if (a[i] <= b[i]) {
      ll res1 = solve_left(vector<int>(a.begin(), a.begin() + i), vector<int>(b.begin(), b.begin() + i));
      ll res2 = solve_right(vector<int>(a.begin() + i, a.end()), vector<int>(b.begin() + i, b.end()));
      if (res1 == -1 || res2 == -1) {
        return -1;
      }
      return res1 + res2;
    }
  }
  assert(a.size() == 1);
  return 0;
}

ll solve(vector<int> a, vector<int> b) {
  int prev = 0;
  ll ans = 0;
  auto subv = [](const vector<int>& a, int l, int r) {
    vector<int> res(r - l);
    for (int i = l; i < r; i++) {
      res[i - l] = a[i] - a[l];
    }
    return res;
  };
  for (int i = 0; i < (int)a.size(); i++) {
    if (a[i] == b[i]) {
      ll cur = solve_all_move(subv(a, prev, i + 1), subv(b, prev, i + 1));
      if (cur == -1) {
        return -1;
      }
      prev = i;
      ans += cur;
    }
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, l;
  while (scanf("%d%d", &n, &l) == 2) {
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
      a[i] -= i + 1;
    }
    for (int i = 0; i < n; i++) {
      scanf("%d", &b[i]);
      b[i] -= i + 1;
    }
    l -= n;
    a.insert(a.begin(), 0);
    a.push_back(l);
    b.insert(b.begin(), 0);
    b.push_back(l);
    printf("%lld\n", solve(a, b));
  }

  return 0;
}
