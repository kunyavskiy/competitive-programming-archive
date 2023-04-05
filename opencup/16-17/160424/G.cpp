//#include <iostream>
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
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "G"

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

const int MOD = 1000000033;

void add(int& a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int& a, int b) {
  if ((a -= b) < 0) a += MOD;
}


int mul(int a, int b) {
  return (a * 1LL * b) % MOD;
}

int pow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int inv(int a) {
  return pow(a, MOD - 2);
}

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int n, k;
  scanf("%d%d",&n,&k);
  vector<int> v(k);

  for (int i = 0; i < k; i++) {
    scanf("%d",&v[i]);
  }

  vector<int> dp(n + 1);
  dp[0] = 1;
  int sum = 1;

  for (int i = 1; i <= n; i++) {
    dp[i] = sum;
    for (int j : v)
      if (i - j >= 0) {
        sub(dp[i], dp[i - j]);
      }
    dp[i] = mul(dp[i], inv(i));
    {
      int t = dp[i];
      for (int j = 1; j <= i; j++) {
        t = mul(t, j);
      }
    }
    add(sum, dp[i]);
  }

  int ans = dp[n];

  for (int i = 1; i <= n; i++) {
    ans = mul(ans, i);
  }

  printf("%d\n", ans);
  return 0;
}
