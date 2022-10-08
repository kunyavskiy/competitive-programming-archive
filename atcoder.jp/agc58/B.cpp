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

const int MOD = 998244353;

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

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif
  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &p[i]);
    }
    vector<int> next(n);
    vector<int> prev(n);
    {
      vector<pair<int, int>> st;
      st.emplace_back(std::numeric_limits<int>::max(), -1);
      for (int i = 0; i < n; i++) {
        while (st.back().first < p[i]) st.pop_back();
        prev[i] = st.back().second;
        st.emplace_back(p[i], i);
      }
    }
    {
      vector<pair<int, int>> st;
      st.emplace_back(std::numeric_limits<int>::max(), n);
      for (int i = n - 1; i >= 0; i--) {
        while (st.back().first < p[i]) st.pop_back();
        next[i] = st.back().second;
        st.emplace_back(p[i], i);
      }
    }

    vector<int> dp(n + 1);
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j <= i; j++) {
        // [j, i]
        int count = 0;
        for (int k = 0; k < n; k++) {
          if (prev[k] < j && next[k] > i) {
            count++;
          }
        }
        eprintf("[%d, %d] -> %d\n", j, i, count - (j != 0));
        add(dp[i + 1], mul(dp[j], count - (j != 0)));
      }
    }
    printf("%d\n", dp.back());
  }

  return 0;
}
