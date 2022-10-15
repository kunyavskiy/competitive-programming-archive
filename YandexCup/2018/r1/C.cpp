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

void add_range(const vector<vector<int>> &pos, const vector<int> &bs, int from, int to, int &res, int coef){
  for (int b : bs) {
    int cnt = upper_bound(pos[b].begin(), pos[b].end(), to) - lower_bound(pos[b].begin(), pos[b].end(), from);
    add(res, mul(coef, cnt));
  }
}


int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  static const int INV2 = minv(2);

  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  vector<int> v(n);
  vector<int> cnt(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &v[i]);
  }
  vector<int> s(k);
  vector<vector<int>> pos(n);

  for (int j = 0; j < k; j++) {
    scanf("%d", &s[j]);
    --s[j];
    pos[s[j]].push_back(j);
    cnt[s[j]]++;
  }

  vector<vector<int>> g(n);
  vector<int> coef(n, 1);
  vector<int> rcoef(n);

  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  vector<bool> big(n);
  for (int i = 0; i < n; i++) {
    big[i] = g[i].size() >= 1000;
  }

  TIMESTAMP(1);
  for (int vs : s) {
    if (!big[vs]) {
      for (int j: g[vs]) {
        add(rcoef[j], coef[j]);
      }
    }
    coef[vs] = mul(coef[vs], INV2);
  }
  TIMESTAMP(2);

  for (int i = 0; i < n; i++) {
    vector<int> bs;
    for (int j : g[i]) {
      if (big[j]) {
        bs.push_back(j);
      }
    }
    int c = 1;
    int last = 0;
    for (int j : pos[i]) {
      add_range(pos, bs, last, j, rcoef[i], c);
      c = mul(c, INV2);
      last = j;
    }
    add_range(pos, bs, last, k, rcoef[i], c);
  }
  TIMESTAMP(3);

  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (rcoef[i] == 0 || v[i] == 0) continue;
    if (cnt[i] == 0) {
      printf("-1\n");
      return 0;
    }
    int start = mul(rcoef[i], v[i]);
    int prog = 1;
    sub(prog, minv(mpow(2, cnt[i])));
    prog = minv(prog);
    add(ans, mul(start, prog));
  }

  printf("%d\n", ans);
  return 0;
}
