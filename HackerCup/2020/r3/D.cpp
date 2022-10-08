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
  int n;
  scanf("%d", &n);
  vector<int> a(n), b(n);
  vector<int> na(n + 2, -1), nb(n + 2, -1);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &a[i], &b[i]);
    --a[i], --b[i];
    na[a[i]] = i;
    nb[b[i]] = i;
  }
  auto split = [](const vector<int>& na) {
    vector<int> f;
    for (int i = na[na.size() - 2]; i != -1; i = na[i]) {
      f.push_back(i);
    }
    vector<int> s;
    for (int i = na[na.size() - 1]; i != -1; i = na[i]) {
      s.push_back(i);
    }
    return make_pair(f, s);
  };

  auto [f1, f2] = split(na);
  auto [t1, t2] = split(nb);

  vector<ll> ans(n + 2);
  auto add_ans = [&](int x, ll val) {
    ans[x + 1] += val;
  };

  auto small = [](const vector<int>& a, int limit) {
    return (int)a.size() <= limit;
  };

  {
    int init_good = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] == b[i]) {
        init_good += 1;
      }
    }
    // Q = 0;
    for (int C = 0; C <= n; C++) {
      for (int X = 0; X <= n; X++) {
        for (int Y = 0; Y <= n; Y++) {
          if (small(f1, min(X, C)) && small(f2, min(Y, C))) {
            add_ans(init_good, 1);
          } else {
            add_ans(-1, 1);
          }
        }
      }
    }
  }

  {
    // Q = 2;
    for (int C = 0; C <= n; C++) {
      for (int X = 0; X <= n; X++) {
        for (int Y = 0; Y <= n; Y++) {
          if (small(f1, C) && small(f2, C) && min(X, C) + min(Y, C) >= n) {
            if (small(t1, min(X, C)) && small(t2, min(Y, C))) {
              add_ans(n, n - 1);
            } else {
              add_ans(n - 1, n - 1);
            }
          } else {
            add_ans(-1, n - 1);
          }
        }
      }
    }
  }

  {
    f1.insert(f1.begin(), n);
    f2.insert(f2.begin(), n + 1);
    // Q = 1;
    for (int C = 0; C <= n; C++) {
      if (!small(f1, C + 1) || !small(f2, C + 1)) {
        add_ans(-1, (n + 1) * (n + 1));
        continue;
      }
      int fixed = n - C;
      assert(!small(f1, fixed) && !small(f2, fixed));
      set<int> bad;
      set<int> fix;
      for (int i = 0; i < fixed; i++) {
        bad.insert(f1[i]);
        bad.insert(f2[i]);
      }
      fix = bad;
      fix.insert(f1[fixed]);
      fix.insert(f2[fixed]);
      int will_ans = n;
      for (int i = 0; i < n; i++) {
        if (a[i] != b[i] && (bad.count(b[i]) || fix.count(i))) {
          will_ans--;
        }
      }
      vector<int> chunks;
      auto get_len = [&](int start) {
        int cnt = 1;
        for (int i = nb[start]; i != -1 && !fix.count(i); i = nb[i]) {
          cnt++;
        }
        return cnt;
      };
      chunks.reserve(bad.size());
      for (int x : bad) {
        chunks.push_back(get_len(x) - 1);
      }
      vector<int> dp(n + 1);
      dp[fixed + get_len(f1[fixed]) - 1] = 1;
      for (int x : chunks) {
        for (int i = n - x; i >= 0; i--) {
          if (dp[i]) {
            dp[i + x] = 1;
          }
        }
      }
      vector<int> dps(dp.size() + 1);
      for (int i = 0; i < (int)dp.size(); i++) {
        dps[i + 1] = dps[i] + dp[i];
      }
      auto have_one = [&](int l, int r) {
        return dps[l] != dps[r];
        for (int i = l; i < r; i++) {
          if (dp[i]) {
            assert(dps[l] != dps[r]);
            return true;
          }
        }
        assert(dps[l] == dps[r]);
        return false;
      };
      for (int X = 0; X <= n; X++) {
        for (int Y = 0; Y <= n; Y++) {
          if (min(X, C) + min(Y, C) >= n) {
            if (have_one(n - min(Y, C), min(X, C) + 1)) {
              add_ans(will_ans, 1);
            } else {
              add_ans(will_ans - 1, 1);
            }
          } else {
            add_ans(-1, 1);
          }
        }
      }
    }
  }


  for (ll x : ans) {
    printf(" %lld", x);
  }
  printf("\n");
}


int main() {
#ifdef LOCAL
//  freopen("d.in", "r", stdin);
//  freopen("d.out", "w", stdout);
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
    printf("Case #%d:", testId);
    solve();
  }

  TIMESTAMP(end);
  return 0;
}
