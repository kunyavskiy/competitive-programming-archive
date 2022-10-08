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

typedef long long ll;
typedef long double ld;

void PreCalc() {
}

vector<int> read_gen(int n, int k) {
  vector<int> data;
  data.resize(k);
  for (int &x : data) scanf("%d", &x);
  int a, b, c, d;
  scanf("%d%d%d%d", &a, &b, &c, &d);
  while ((int)data.size() < n) {
    data.push_back((a * 1LL * data[data.size()- 2] + b * 1LL * data.back() + c) % d + 1);
  }
  return data;
}

void solve() {
  int n, m, k, x;
  scanf("%d%d%d%d", &n, &m, &k, &x);
  vector<int> s = read_gen(n, k);
  vector<int> p = read_gen(m, k);
  sort(s.begin(), s.end());
  sort(p.begin(), p.end());

  auto check = [&](int prefix) {
    int pos = (int)s.size() - 1;
    ll keys = 1;
    multiset<int> rems;
    for (int i = prefix - 1; i >= 0; i--) {
      while (pos >= 0 && s[pos] >= p[i]) {
        rems.insert(s[pos] >= x ? s[pos] % x : -1);
        keys += max(0, s[pos] / x - 1);
        pos--;
      }
      if (rems.empty()) {
        eprintf("check(%d) = 0\n", prefix);
        return false;
      }
      keys -= p[i] / x;
      auto it = rems.lower_bound(p[i] % x);
      if (it != rems.end()) {
        rems.erase(it);
      } else {
        --keys;
        rems.erase(rems.begin());
      }
    }
    while (pos >= 0) {
      keys += max(0, s[pos] / x - 1);
      pos--;
    }
    eprintf("check(%d) = %d\n", prefix, (int)(keys >= 0));
    return keys >= 0;
  };

  int l = 0;
  int r = p.size() + 1;
  while (r - l > 1) {
    int mid = (l + r) / 2;
    if (check(mid)) {
      l = mid;
    } else {
      r = mid;
    }
  }

  printf("%d\n", l);
}


int main() {
#ifdef LOCAL
//  freopen("c.in", "r", stdin);
//  freopen("c.out", "w", stdout);
#endif

  PreCalc();
  TIMESTAMP(PreCalc);

  char buf[1000];
  int testNum;
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d", &testNum);

  for (int testId = 1; testId <= testNum; testId++) {
    if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
      TIMESTAMPf("Test %d", testId);
    printf("Case #%d: ", testId);
    solve();
  }

  TIMESTAMP(end);
  return 0;
}
