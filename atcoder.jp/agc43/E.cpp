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


bool solve(int n, string s) {
  if (s[0] == '0')
    return false;
  vector<int> bads;
  for (int i = 0; i < (1 << n); i++) {
    for (int j = 0; j < n; j++) {
      if (!(i & (1 << j))) {
        continue;
      }
    }
    bool found_zero_sub = false;
    for (int j = 0; j < n; j++) {
      if (!(i & (1 << j))) {
        continue;
      }
      if (s[i ^ (1 << j)] == '0') {
        found_zero_sub = true;
      }
    }
    if (found_zero_sub) {
      if (s[i] == '1') {
        return false;
      }
    } else {
      if (s[i] == '0') {
        bads.push_back(i);
      }
    }
  }

  vector<int> seq;

  for (int x : bads) {
    vector<int> ss;
    for (int i = 0; i < n; i++) {
      if (!(x & (1 << i))) {
        continue;
      }
      int cur = ss.size();
      ss.push_back(i + 1);
      for (int j = cur - 1; j >= 0; j--) {
        ss.push_back(-ss[j]);
      }
      if (cur) {
        ss.push_back(-(i + 1));
      }
    }
    seq.insert(seq.end(), ss.begin(), ss.end());
  }

  printf("Possible\n");

  vector<pair<int, int>> pts;

  pts.emplace_back(0, 0);

  auto push = [&] (int x,int y) {
    if (pts.size() > 1 && pts[pts.size() - 2].first == x && pts[pts.size() - 2].second == y) {
      pts.pop_back();
    } else {
      pts.emplace_back(x, y);
    }
  };

  for (int x : seq) {
    if (x < 0) {
      x = -x;
      for (int i = 1; i <= x; i++) {
        push(0, i);
      }
      push(1, x);
      push(1, x - 1);
      for (int i = x - 1; i >= 0; i--) {
        push(0, i);
      }
    } else {
      for (int i = 1; i < x; i++) {
        push(0, i);
      }
      push(1, x - 1);
      push(1, x);
      for (int i = x ; i >= 0; i--) {
        push(0, i);
      }
    }
  }

  printf("%d\n", (int)pts.size() - 1);
  for (auto p : pts) {
    printf("%d %d\n", p.second, p.first);
  }
  return true;
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    char s[512];
    scanf("%s", s);
    if (!solve(n, s)) {
      printf("Impossible\n");
    }
  }

  return 0;
}
