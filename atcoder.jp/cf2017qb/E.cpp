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

const int MAXN = 2010;
int cnk[MAXN][MAXN];
int cnks[MAXN][MAXN];
int cnkss[MAXN][MAXN];

int solve2(int a, int b) {
  if (b == 0) return 1;
  int ans1 = cnkss[b - 1][min(a, b - 1)];
  int ans2 = mul(max(0, a - b + 1), cnks[b - 1][b - 1]);
  add(ans1, ans2);
  return ans1;
}

int solve1(int a, int b) {
  int ans = 0;
  for (int i = 0; i <= b && i <= a; i++) {
    add(ans, mul(solve2(a - i, i), cnk[b][i]));
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  cnk[0][0] = 1;
  for (int i = 0; i < MAXN; i++) {
    for (int j = 0; j < MAXN; j++) {
      if (i) add(cnk[i][j], cnk[i - 1][j]);
      if (i && j) add(cnk[i][j], cnk[i - 1][j - 1]);
    }
  }

  for (int i = 0; i < MAXN; i++) {
    for (int j = 0; j < MAXN; j++) {
      cnks[i][j] = cnk[i][j];
      if (j) add(cnks[i][j], cnks[i][j-1]);
    }
  }
  for (int i = 0; i < MAXN; i++) {
    for (int j = 0; j < MAXN; j++) {
      cnkss[i][j] = cnks[i][j];
      if (j) add(cnkss[i][j], cnkss[i][j-1]);
    }
  }


  int a, b;
  while (scanf("%d%d", &a, &b) == 2) {

    int ans = 0;
    for (int i = 0; i <= a; i++) {
      add(ans, solve1(a - i, b - 1));
    }

    printf("%d\n", ans);
  }


  return 0;
}
