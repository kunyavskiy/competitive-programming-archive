#include <algorithm>
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
  int n, m, k, s;
  scanf("%d%d%d%d", &n, &m, &k, &s);
  auto p = read_gen(n, k);
  auto q = read_gen(m, k);
  sort(p.begin(), p.end());
  sort(q.begin(), q.end());
  ll l = 0;
  ll r = 1e10;
  auto tm = [](ll a, ll b, ll c) {
    return b - a + min(abs(c - a), abs(c - b));
  };
  auto check = [&](ll x) {
    int pt = 0;
    for (int i = 0; i < n && pt < m; i++) {
      int st = pt;
      if (abs(p[i] - q[st]) > x) continue;
      pt++;
      while (pt < m && tm(q[st], q[pt], p[i]) <= x) pt++;
    }
    return pt == m;
  };
  while (r - l > 1) {
    ll m = (l + r) / 2;
    if (check(m)) {
      r = m;
    } else {
      l = m;
    }
  }
  printf("%lld\n", r);
}



int main() {
#ifdef LOCAL
//  freopen("b.in", "r", stdin);
//  freopen("b.out", "w", stdout);
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
