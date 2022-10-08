#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
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

long long pw10[20];

void PreCalc() {
  pw10[0] = 1;
  for (int i = 1; i < 20; i++) {
    pw10[i] = pw10[i-1] * 10;
  }
}

long long solve_max(int cnt[10], int len) {
  int n = accumulate(cnt, cnt + 10, 0);
  assert(n % 2 == 0);
  if (n == 0) { return 0; }
    vector<long long> dp(2 * len + 1, numeric_limits<long long>::min() / 2);
    dp[0] = 0;
    for (int i = 0; i < 10; i++) {
      vector<long long> ndp(dp.size(), numeric_limits<long long>::min() / 2);
      for (int j = 0; j < (int)dp.size(); j++) {
        for (int c = cnt[i] % 2; c <= cnt[i]; c += 2) {
          if (j + c < (int)dp.size()) {
            long long cur = dp[j];
            auto get_coef = [&](int pos) {
              if (pos >= len) {
                return pw10[pos - len];
              } else {
                return -pw10[len - pos - 1];
              }
            };
            for (int k = 0; k < c; k++) {
              cur += i * get_coef(j + k);
            }

            ndp[j + c] = max(ndp[j + c], cur);
          }
        }
      }
      dp = ndp;
    }
    return dp.back();
}



void solve() {
  char s[100];
  scanf("%s", s);
  int n = strlen(s);
  if (n % 2 == 1) {
    sort(s, s + n);
    char *first0 = find_if(s, s + n, [](char c) { return c != '0';});
    swap(*first0, s[0]);
    string fs(s, s + n / 2 + 1);
    string sc(s + n / 2 + 1, s + n);
    reverse(sc.begin(), sc.end());
    long long fsi = atoll(fs.c_str());
    long long sci = atoll(sc.c_str());
    eprintf("%s %s\n", fs.c_str(), sc.c_str());
    printf("%lld\n", fsi - sci);
    return;
  }

  int cnt[10]{};
  for (int i = 0; s[i]; i++) {
    cnt[s[i]-'0']++;
  }

  if (std::all_of(cnt, cnt + 10, [](int x) { return x % 2 == 0;})) {
    printf("0\n");
    return;
  }

  long long ans = numeric_limits<long long>::max();


  for (int d1 = 1; d1 <= 9; d1++) {
    for (int d2 = d1 + 1; d2 <= 9; d2++) {
      if (cnt[d1] > 0 && cnt[d2] > 0) {
        cnt[d1]--;
        cnt[d2]--;
        ans = min(ans, (d2 - d1) * pw10[n / 2 - 1] - solve_max(cnt, n / 2 - 1));
        cnt[d1]++;
        cnt[d2]++;
      }
    }
  }

  for (int d = 1; d <= 9; d++) {
    if (cnt[d] >= 2) {
      cnt[d] -= 2;
      for (int d1 = 0; d1 <= 9; d1++) {
        for (int d2 = d1 + 1; d2 <= 9; d2++) {
          if (cnt[d1] > 0 && cnt[d2] > 0) {
            cnt[d1]--;
            cnt[d2]--;
            for (int i = 0; i <= (n - 4) / 2; i++) {
              ans = min(ans, (d2 - d1) * pw10[i] - solve_max(cnt, i));
            }
            cnt[d1]++;
            cnt[d2]++;
          }
        }
      }
      cnt[d] += 2;
    }
  }

  printf("%lld\n", ans);
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
