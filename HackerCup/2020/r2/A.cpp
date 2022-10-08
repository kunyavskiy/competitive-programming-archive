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
    data.push_back((a * 1LL * data[data.size()- 2] + b * 1LL * data.back() + c) % d);
  }
  return data;
}

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  auto s = read_gen(n, k);
  auto x = read_gen(n, k);
  auto y = read_gen(n, k);

  long long minv, maxv, overflow, underflow, total;
  minv = maxv = overflow = underflow = total = 0;
  for (int i = 0; i < n; i++) {
    minv += x[i];
    maxv += x[i] + y[i];
    overflow += max(0, s[i] - x[i] - y[i]);
    underflow += max(0, x[i] - s[i]);
    total += s[i];
  }
  if (total < minv || total > maxv) {
    printf("-1\n");
  } else {
    printf("%lld\n", max(underflow, overflow));
  }
}


int main() {
#ifdef LOCAL
//  freopen("a.in", "r", stdin);
//  freopen("a.out", "w", stdout);
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
