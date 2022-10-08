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

const int MAX = 1000010;
int invv[MAX];

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  invv[1] = 1;
  for (int i = 2; i < MAX; i++) {
    invv[i] = mul(MOD - invv[MOD % i], MOD / i);
    assert(mul(i, invv[i]) == 1);
  }


  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> cnt(MAX);
    int sum = 0;
    for (int i = 0; i < n; i++) {
      int a;
      scanf("%d", &a);
      add(sum, a);
      cnt[a]++;
    }
    vector<int> sumg(MAX);
    for (int i = 1; i < MAX; i++) {
      for (int j = i; j < MAX; j += i) {
        add(sumg[i], mul(cnt[j], j));
      }
    }
    for (int i = 0; i < MAX; i++) {
      sumg[i] = mul(sumg[i], sumg[i]);
    }
    for (int i = MAX - 1; i >= 1; i--) {
      for (int j = 2  * i; j < MAX; j += i) {
        sub(sumg[i], sumg[j]);
      }
    }
    int ans = 0;
    for (int i = 1; i < MAX; i++) {
      if (sumg[i] != 0) {
        eprintf("%d %d\n", i, sumg[i]);
      }
      add(ans, mul(sumg[i], invv[i]));
    }
    eprintf("here!\n");
    sub(ans, sum);
    ans = mul(ans, minv(2));
    printf("%d\n", ans);
  }

  return 0;
}
