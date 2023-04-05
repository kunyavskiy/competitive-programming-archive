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

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char* what) : what(what){};
  __timestamper(const string& what) : what(what){};
  ~__timestamper(){
    TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

void solve(int test, vector<int> a) {
  int n = a.size();
  sort(a.begin(), a.end());

  vector<int> vct;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      for (int k = j + 1; k < n; k++) {
        if (a[k] < a[i] + a[j]) {
          vct.push_back((1 << i) + (1 << j) + (1 << k));
        }
      }
    }
  }

  vector<pair<int, int>> dp(1 << n, make_pair(0, 0));
  for (int i = 0; i < (int)vct.size(); i++) {
    dp[vct[i]] = {1, vct[i]};
    for (int j = i + 1; j < (int)vct.size(); j++) {
      if (!(vct[i] & vct[j])) {
        dp[vct[i] | vct[j]] = {2, vct[i] | vct[j]};
      }
    }
  }
  for (int k = 1; k < (1 << n); k *= 2) {
    for (int i = 0; i < (1 << n); i += 2 * k) {
      for (int j = 0; j < k; j++) {
        dp[i + k + j] = max(dp[i + k + j], dp[i + j]);
      }
    }
  }

  int best_val = 0;
  int best_mask1 = 0;
  int best_mask2 = 0;
  for (int i = 0; i < (1 << n); i++) {
    if (best_val < dp[i].first) {
      best_val = dp[i].first;
      best_mask1 = dp[i].second;
      best_mask2 = 0;
    }
  }

  for (int i = 0; i < (int)vct.size(); i++) {
    dp[vct[i]] = {1, vct[i]};
    for (int j = i + 1; j < (int)vct.size(); j++) {
      if (!(vct[i] & vct[j])) {
        int cmpl = ((1 << n) - 1) ^ (vct[i] | vct[j]);

        if (best_val < 2 + dp[cmpl].first) {
          best_val = 2 + dp[cmpl].first;
          best_mask1 = vct[i] | vct[j];
          best_mask2 = dp[cmpl].second;
        }
      }
    }
  }

  vector<int> ans;
  function<void(int)> restore = [&](int mask) {
    if (dp[mask].first == 1) {
      ans.push_back(dp[mask].second);
      return;
    }
    for (int i = 0; i < (1 << n); i++) {
      if ((i & mask) == i && dp[i].first > 0 && dp[mask ^ i].first > 0) {
        restore(i);
        restore(mask ^ i);
        return;
      }
    }
  };
  restore(best_mask1);
  restore(best_mask2);


  printf("Case #%d: %d\n", test, (int)ans.size());
  for (auto v : ans) {
    for (int i = 0; i < n; i++) if (v & (1 << i)) printf("%d ", a[i]);
    printf("\n");
  }
}

void test() {
  for (int it = 0; it < 6000; it++) {
    int n = 12;
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = 1 << i;
    solve(it, a);
  }
  exit(0);
}

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
//  freopen("k.out", "w", stdout);
#endif
//test();

  int T;
  scanf("%d", &T);
  for (int test = 1; test <= T; test++) {
    int n = 12;
    vector<int> a(n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    solve(test, a);
  }

  return 0;
}
