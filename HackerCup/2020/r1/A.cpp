#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <cassert>
#include <map>

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

const int MOD = 1000000007;

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  auto l = read_gen(n, k);
  auto w = read_gen(n, k);
  auto h = read_gen(n, k);

  assert(is_sorted(h.rbegin(), h.rend()));

  std::map<pair<int, int>, int> ls;
  ll res = 1;
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    auto it = ls.lower_bound({l[i], l[i]});
    int lf = l[i];
    int rg = l[i] + w[i];
    if (it != ls.begin()) {
      auto it2 = it;
      it2--;
      if (it2->first.second >= rg) {
        ans += h[i] - it2->second;
        auto old = *it2;
        ls.erase(it2);
        if (old.first.first != lf) {
          ls[{old.first.first, lf}] = old.second;
        }
        if (old.first.second != rg) {
          ls[{rg, old.first.second}] = old.second;
        }
        ans -= rg - lf;
      } else if (it2->second >= lf) {
        ans += h[i] - it2->second;
        auto old = *it2;
        ls.erase(it2);
        if (old.first.first != lf) {
          ls[{old.first.first, lf}] = old.second;
        }
        ls.erase(it2);
      } else {
        ans += h[i];
      }
    } else {
      ans += h[i];
    }
    while (it != ls.end() && it->first.first <= l[i] + w[i]) {
      ans -= it->second;
      rg = max(rg, it->second);
      ans -= it->second - it->first;
      it = ls.erase(it);
    }
    ans += rg - lf;
    ls[{lf, rg}] = h[i];

//    eprintf("ans = %lld\n", 2 * ans);
    res = (res * (2 * ans % MOD)) % MOD;
  }

  printf("%lld\n", res);
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
