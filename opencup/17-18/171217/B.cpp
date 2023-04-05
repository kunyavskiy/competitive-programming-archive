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
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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
typedef unsigned long long ull;
typedef long double ld;

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


int n, m;
map<ull, int> dp[64];
map<ull, int> ndp[64];

void go(ll in_masks, int mask, int pos, int cnt, map<ull, int>& to, int bit) {
  ll res_masks = 0;
  for (int i = 0; i < (1 << n); i++) {
    if (!(in_masks & (1ULL << i))) {
      continue;
    }
    if (!(i & (1 << pos))) {
      if (((mask >> pos) & 1) != bit) {
        int ni = i | (1 << pos);
        res_masks |= (1ULL << ni);
      }
    } else {
      {
        int ni = i & ~(1 << pos);
        res_masks |= (1ULL << ni);
      }
      if (pos && !(i & (1 << (pos - 1))) && ((mask >> (pos - 1)) & 1) != bit) {
        int ni = i | (1 << (pos - 1)) | (1 << pos);
        res_masks |= (1ULL << ni);
      }
    }
  }
  if (res_masks && cnt) {
    add(to[res_masks], cnt);
  }
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  scanf("%d%d", &n, &m);
  dp[0][1ULL << ((1 << n) - 1)] = 1;

  for (int j = 0; j < m; j++) {
    for (int i = 0; i < n; i++) {
      for (int mask = 0; mask < (1 << n); mask++) {
        for (auto x : dp[mask]) {
          go(x.first, mask, i, x.second, ndp[mask & ~(1 << i)], 0);
          go(x.first, mask, i, x.second, ndp[mask | (1 << i)], 1);
        }
      }

      for (int mask = 0; mask < (1 << n); mask++) {
        dp[mask].swap(ndp[mask]);
        ndp[mask].clear();
      }
    }
  }

  int ans = 0;
  for (int mask = 0; mask < (1 << n); mask++) {
    for (auto x : dp[mask]) {
      if (x.first & (1ULL << ((1 << n) - 1))) {
        add(ans, x.second);
      }
    }
  }

  printf("%d\n", ans);

  return 0;
}
