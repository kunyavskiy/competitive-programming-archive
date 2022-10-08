#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

typedef long long ll;
typedef long double ld;

void PreCalc() {
}

void solve() {
  int n, l;
  scanf("%d%d", &n, &l);
  int tot = 0;
  vector<int> cur(l);
  for (int i = 0; i < l; i++) {
    scanf("%d", &cur[i]);
    tot += cur[i];
  }
  while ((int)cur.size() < n) {
    cur.push_back(0);
  }

  set<pair<int, int>> s;

  auto score = [&n](int x) {
    return -((x * 200 + n) % (2 * n));
  };

  for (int i = 0; i < n; i++) {
    s.insert({score(cur[i]), i});
  }

  while (tot++ < n) {
    int id = s.begin()->second;
    s.erase(s.begin());
//    eprintf("%d -> %d\n", cur[id], cur[id] + 1);
    cur[id]++;
    s.insert({score(cur[id]), id});
  }

  int ans = 0;
  for (int x : cur) {
    ans += (200 * x + n) / (2 * n);
  }

  printf("%d\n", ans);
}


int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
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
