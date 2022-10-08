#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

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

const int MOD = 1000000007;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) {
  return mpow(x, MOD - 2);
}

void solve() {
  int n;
  scanf("%d", &n);
  vector<pair<int, int>> v(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &v[i].first);
    v[i].second = i;
  }
  int ans = 0;
  for (int i = 0; i < n; i++) {
    int cur = v[i].first;
    cur = mul(cur, i + 1);
    cur = mul(cur, n - i);
    sub(ans, cur);
    eprintf("-%d\n", cur);
  }
  sort(v.rbegin(), v.rend());

  set<int> done;
  for (auto p : v) {
    int id = p.second;
    int val = p.first;
    auto rit = done.lower_bound(id);
    int rpos = rit == done.end() ? n : *rit;
    int lpos = rit == done.begin() ? -1 : *--rit;
    int to_add = val;
    to_add = mul(to_add, rpos - id);
    to_add = mul(to_add, id - lpos);
    to_add = mul(to_add, n - rpos + lpos + 1);
    add(ans, to_add);

    to_add = val;
    to_add = mul(to_add, rpos - id);
    to_add = mul(to_add, id - lpos);
    add(ans, to_add);
    done.insert(id);
  }

  printf("%d\n", ans);
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
