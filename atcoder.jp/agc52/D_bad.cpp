#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

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

int lis(vector<int> v) {
  vector<int> dp(v.size(), numeric_limits<int>::max());
  for (int x : v) {
    *lower_bound(dp.begin(), dp.end(), x) = x;
  }
  return count_if(dp.begin(), dp.end(), [](int x) { return x != numeric_limits<int>::max();});
}

int lis_cnt(vector<int> v) {
  int best = 0, best_cnt = 0;
  for (int i = 0; i < (1 << v.size()); i++) {
    int last = 0;
    bool ok = true;
    int cnt = 0;
    for (int j = 0; j < (int)v.size(); j++) {
      if (i & (1 << j)) {
        if (last > v[j]) ok = false;
        cnt++;
        last = v[j];
      }
    }
    if (ok) {
      if (best < cnt) {
        best = cnt;
        best_cnt = 0;
      }
      if (best == cnt) {
        best_cnt++;
      }
    }
  }
  return best_cnt;
}


bool good(vector<int> v) {
  for (int i = 0; i < (1 << v.size()); i++) {
    vector<int> a, b;
    for (int j = 0; j < (int)v.size(); j++) {
      if (i & (1 << j)) {
        a.push_back(v[j]);
      } else {
        b.push_back(v[j]);
      }
    }
    if (lis(a) == lis(b)) return true;
  }
  return false;
}

bool good_smart(vector<int> v) {
  int best = 0, best_cnt = 0, best_mask = -1;
  for (int i = 0; i < (1 << v.size()); i++) {
    int last = 0;
    bool ok = true;
    int cnt = 0;
    for (int j = 0; j < (int)v.size(); j++) {
      if (i & (1 << j)) {
        if (last > v[j]) ok = false;
        cnt++;
        last = v[j];
      }
    }
    if (ok) {
      if (best < cnt) {
        best = cnt;
        best_cnt = 0;
        best_mask = i;
      }
      if (best == cnt) {
        best_cnt++;
      }
    }
  }
  if (best % 2 != 1 || best_cnt != 1) return true;
  vector<int> nv;
  int get_cnt = best / 2;
  for (int j = 0; j < (int)v.size(); j++) {
    if (best_mask & (1 << j)) {
      if (get_cnt-- > 0) {
        nv.push_back(v[j]);
      }
    } else {
      nv.push_back(v[j]);
    }
    if (lis(nv) == (best + 1) / 2) return true;
  }
  return false;
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n = 7;
  vector<int> v(n);
  iota(v.begin(), v.end(), 1);
  do {
    bool is_good = good(v);
    bool is_good_my = good_smart(v);
    if (is_good != is_good_my) {
      printf("%s: ",is_good ? "good" : "bad");
      for (int x : v) {
        printf("%d ", x);
      }
      printf(": %d %d", lis(v), lis_cnt(v));
      printf("\n");
    }
  } while (next_permutation(v.begin(), v.end()));

  return 0;
}
