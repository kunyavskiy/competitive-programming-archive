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

int solve_stupid(int k, vector<int> x) {
  k *= 2;
  for (int i = 0; i < (int)x.size(); i++) {
    x[i] *= 2;
  }
  int ans = numeric_limits<int>::max();
  for (int i = 1; i < (1 << k); i++) {
    vector<int> v;
    for (int j = 0; j < k; j++) {
      if (i & (1 << j)) {
        v.push_back(j);
      }
    }
    v.insert(v.begin(), v.back() - k);
    v.push_back(v[1] + k);
    bool ok = true;
    for (int pos : x) {
      auto it = lower_bound(v.begin(), v.end(), pos);
      if (*it == pos) {
        ++it;
      }
      ok = ok && (*(it - 1) + *it == 2 * pos);
    }
    if (ok) {
      ans = min(ans, (int)v.size() - 2);
      /*
      if (v.size() == 4 + 2) {
        for (int i = 1; i < (int)v.size() - 1; i++) {
          eprintf("%d ",v[i]);
        }
        eprintf("\n");
      }
       */
    }
  }
  return ans;
}

void solve() {
  int k, n;
  scanf("%d%d", &k, &n);
  vector<int> x(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &x[i]);
  }
  for (int i = 0; i < n; i++) {
    scanf("%*d");
  }
#ifdef LOCAL
  int ans2 = solve_stupid(k, x);
#endif

  auto fixup = [&] {
    for (int i = 1; i < n; i++) {
      x[i] -= x[0];
    }
    x[0] = 0;
  };

  auto rotate = [&] {
    x.pop_back();
    std::rotate(x.begin(), x.begin() + 1, x.end());
    x.back() += k;
    fixup();
    x.push_back(k);
  };

  fixup();
  x.push_back(k);

  auto can_all = [&] {
    int coef = 1;
    int add = 0;
    int mn = 0;
    int mx = x[1];

    for (int i = 1; i < n; i++) {
      add = 2 * x[i] - add;
      coef = -coef;
      if (coef > 0) {
        // x[i] <= y + add <= x[i + 1]
        mn = max(mn, x[i] - add);
        mx = min(mx, x[i + 1] - add);
      } else {
        // x[i] <= -y + add <= x[i + 1]
        mn = max(mn, -(x[i + 1] - add));
        mx = min(mx, -(x[i] - add));
      }
    }

    add = k - add;
    coef = -coef;


    if (mn >= mx) return false;
    if (coef < 0 && !(2 * mn < add && add < 2 * mx)) return false;
    if (coef > 0 && add != 0) return false;
    return true;
  };

  int ans = numeric_limits<int>::max();
  if (can_all()) {
    ans = n;
  } else {
    for (int it = 0; it < n; it++) {
      int l = 0, r = x[1];
      int cur = n;
      for (int i = 1; i < n; i++) {
        swap(l, r);
        l = 2 * x[i] - l;
        r = 2 * x[i] - r;
        if (l >= x[i + 1]) {
          cur++;
          l = x[i];
          r = x[i + 1];
        }
        r = min(r, x[i + 1]);
      }
      if (l != k) {
        cur++;
      }
      ans = min(ans, cur);
      rotate();
    }
  }
  printf("%d\n", ans);
#ifdef LOCAL
  eprintf("ans : %d, ans2 = %d\n", ans, ans2);
  assert(ans == ans2);
#endif
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
