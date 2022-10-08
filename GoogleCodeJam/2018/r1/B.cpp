#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

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

int solve(const vector<int> &f, const vector<int> &s, const vector<int>& b, int from, int n) {
  int l = from;
  int r = n + 1;
  auto ffrom = lower_bound(f.begin(), f.end(), from);
  auto sfrom = lower_bound(s.begin(), s.end(), from);
  auto bfrom = lower_bound(b.begin(), b.end(), from);
  while (r - l > 1) {
    int m = (l + r) / 2;
    int cnt = lower_bound(f.begin(), f.end(), m) - ffrom;
    cnt += lower_bound(s.begin(), s.end(), m) - sfrom;
    cnt -= lower_bound(b.begin(), b.end(), m) - bfrom;
    if (cnt == m - from) {
      l = m;
    } else {
      r = m;
    }
  }
  return l;
}

void solve() {
  int n;
  scanf("%d", &n);
  map<int, vector<int>> f, s;
  map<pair<int, int>, vector<int>> b;
  vector<int> fv(n), sv(n);
  for (int i = 0; i < n; i++) {
    int a, bb, d;
    scanf("%d%d%d", &d, &a, &bb);
    f[fv[i] = d + a].push_back(i);
    s[sv[i] = d - bb].push_back(i);
    b[{fv[i], sv[i]}].push_back(i);
  }

  int best, bestcnt;
  best = bestcnt = 0;

  int samef, sames;
  samef = sames = n;

  for (int i = n - 1; i >= 0; i--) {
    if (i != n - 1) {
      if (fv[i] != fv[i + 1]) samef = i + 1;
      if (sv[i] != sv[i + 1]) sames = i + 1;
    }
    int nsv = samef == n ? -1 : sv[samef];
    int nfv = sames == n ? -1 : fv[sames];
    int r1 = solve(f[fv[i]], s[nsv], b[{fv[i], nsv}],  i, n);
    int r2 = solve(f[nfv], s[sv[i]], b[{nfv, sv[i]}], i, n);
    eprintf("%d %d %d\n", i, r1, r2);
    int r = max(r1, r2) - i;
    if (r > best) {
      best = r;
      bestcnt = 0;
    }
    if (r == best) {
      bestcnt++;
    }
  }
  printf("%d %d\n", best, bestcnt);
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
