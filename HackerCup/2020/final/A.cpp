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
  int n, k;
  scanf("%d%d", &n, &k);
  map<int,int> lim;
  lim[k] = k + 1;
  lim[-1] = 0;
  long long ans = k * 1LL * (k + 1) /2;

  int tot_ans = 1;

  for (int i = 0; i < n; i++) {
    int s, e;
    scanf("%d%d", &s, &e);
    e += s;
    auto it = lim.lower_bound(s);
    if (it->first != s) {
      it = lim.emplace(s, it->second).first;
    }
    if (it->second > e) {
      while (true) {
        auto prev = std::prev(it);
        ans -= (it->second - max(e, prev->second)) * 1LL * (s - prev->first);
        if (prev->second < e) {
          it->second = e;
          break;
        }
        it->second = prev->second;
        lim.erase(prev);
      }
    }
    tot_ans = mul(tot_ans, ans % MOD);
  }
  printf("%d\n", tot_ans);
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
