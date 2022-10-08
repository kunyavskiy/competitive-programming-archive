#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cassert>

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

bool check(const vector<pair<int, int>> &rules, vector<ll> cnt) {
  ll total = 0;
  for (ll x : cnt) {
    total += x;
  }
  queue<int> q;
  for (int i = 0; i < (int)cnt.size(); i++) {
    if (cnt[i] < 0) {
      q.push(i);
    }
  }
  while (total >= 0 && !q.empty()) {
    int v = q.front();
    q.pop();
    ll x = cnt[v];
    total += x;
    cnt[v] -= x;
    cnt[rules[v].first] += x;
    cnt[rules[v].second] += x;
    if (cnt[rules[v].first] < 0) q.push(rules[v].first);
    if (cnt[rules[v].second] < 0) q.push(rules[v].second);
  }
  return total >= 0;
}

void solve() {
  int n;
  scanf("%d", &n);
  vector<pair<int, int>> rules(n);
  vector<ll> cnt(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &rules[i].first, &rules[i].second);
    --rules[i].first;
    --rules[i].second;
  }
  for (int i = 0; i < n; i++) {
    scanf("%lld", &cnt[i]);
  }


  ll l = 0;
  ll r = 1e15;

  while (r - l > 1) {
    ll m = (l + r) / 2;
    cnt[0] -= m;
    if (check(rules, cnt)) {
      l = m;
    } else {
      r = m;
    }
    cnt[0] += m;
  }
  printf("%lld\n", l);
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
