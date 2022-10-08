#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
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

typedef long long ll;
typedef long double ld;

void PreCalc() {
}

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<int> v(n);
  vector<int> tss;
  for (int i = 1; i < n; i++) {
    scanf("%d", &v[i]);
  }
  sort(tss.begin(), tss.end());

  vector<pair<int, int>> ev;
  for (int i = 0; i < n; i++) {
    ev.emplace_back(v[i], i);
  }
  sort(ev.rbegin(), ev.rend());

  vector<int> nv(n);
  for (auto x : ev) {
    int i = x.second;
    if (v[i] < 0) {
      int cnt = -v[i];
      assert(cnt > 0 && cnt <= (int)tss.size());
      assert(cnt == (int)tss.size() || tss[cnt] != tss[cnt - 1]);
      nv[i] = tss[cnt - 1] + 1;
    } else {
      nv[i] = v[i];
    }
    tss.insert(lower_bound(tss.begin(), tss.end(), nv[i]), nv[i]);
    assert(std::is_sorted(tss.begin(), tss.end()));
  }
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    printf("%d ", max(1, abs(nv[a] - nv[b])));
  }
  printf("\n");
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
