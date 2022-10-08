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

vector<int> solve_in(int n, int c) {
  if (c < 0) {
    return {};
  }
  if (n == 1) {
    if (c) return {};
    return {1};
  }
  if (n - 1 <= c) {
    vector<int> r = solve_in(n - 1, c - (n - 1));
    if (r.empty()) return r;
    reverse(r.begin(), r.end());
    for (int &x : r) x++;
    r.push_back(1);
    return r;
  }
  auto r = solve_in(n - 1, c);
  if (r.empty()) return r;
  for (int &x : r) x++;
  r.insert(r.begin(), 1);
  return r;
}

void solve() {
  int n, c;
  scanf("%d%d", &n, &c);
  auto v = solve_in(n, c - n + 1);
  if (v.empty()) {
    printf("IMPOSSIBLE\n");
    return;
  }
  for (int x : v) printf("%d ", x);
  printf("\n");
}


int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
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
