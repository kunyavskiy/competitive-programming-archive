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

int minv(int x) {
  return mpow(x, MOD - 2);
}

const int MAXN = 110000;

vector<int> g[MAXN];
int tot_cnt;
int tot_sum;

pair<int, int> dfs(int v, int p = -1) {
  vector<int> cnts;
  vector<int> sums;
  for (int u : g[v]) {
    if (u == p) continue;
    auto r = dfs(u, v);
    cnts.push_back(r.first);
    sums.push_back(r.second);
  }
  int cnt = 1;
  for (int i = 0; i < (int)cnts.size(); i++) {
    sums[i] = mul(sums[i], cnt);
    cnt = mul(cnt, cnts[i] + 1);
  }
  int sum = cnt;
  cnt = 1;
  for (int i = (int)cnts.size() - 1; i >= 0; i--) {
    sums[i] = mul(sums[i], cnt);
    cnt = mul(cnt, cnts[i] + 1);
    add(sum, sums[i]);
  }
  add(tot_cnt, cnt);
  add(tot_sum, sum);
//  eprintf("v = %d, cnt = %d, sum = %d\n", v, cnt, sum);
  return {cnt, sum};
};

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  auto res = dfs(0);

  printf("%d %d\n", tot_cnt, tot_sum);

  return 0;
}
