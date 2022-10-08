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

void solve() {
  int n, a, b;
  scanf("%d%d%d", &n, &a, &b);
  vector<int> need(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &need[i]);
  }
  int g = __gcd(a, b);
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      if (need[i] && need[j] && (j - i) % g != 0) {
        printf("IMPOSSIBLE\n");
        return;
      }
    }
  }

  auto norm = [&](vector<int>& v) {
    for (int i = n - 1; i >= 0; i--) {
      int e = max(0, v[i] - need[i]);
      if (i >= a) v[i - a] += e;
      if (i >= b) v[i - b] += e;
      v[i] -= e;
    }
  };

  vector<vector<int>> data;
  for (int i = 0; i < n; i++) {
    data.emplace_back(n, 0);
    data[i][i] = 1;
    norm(data[i]);
  }
  while (data.back() != need) {
    vector<int> res(n);
    if ((int)data.size() >= a) {
      for (int i = 0; i < n; i++) {
        res[i] += data[data.size() - a][i];
      }
    }
    if ((int)data.size() >= b) {
      for (int i = 0; i < n; i++) {
        res[i] += data[data.size() - b][i];
      }
    }
    norm(res);
    data.push_back(res);
  }
  printf("%d\n", (int)data.size());
}


int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
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
