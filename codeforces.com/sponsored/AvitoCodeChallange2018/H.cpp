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

namespace multiplier {
  const int ROOT = 3;
  const int MROOT = 19;
  const int MROOTP = 1<<MROOT;
  int rts[MROOTP + 10], brev[MROOTP + 10];
// \emph{Don't forget to call before}
  void PreCalcRoots(){
    rts[0] = 1; // ROOT is primary root for MOD
    rts[1] = mpow(ROOT, (MOD-1) / MROOTP);
    for (int i = 2; i < MROOTP; i++)
      rts[i] = mul(rts[i-1], rts[1]);
    for (int i = 0; i < MROOTP; i++) /*BOXNEXT*/
      brev[i] = (brev[i>>1]>>1) | ((i&1) << (MROOT-1));
  }
  inline void butterfly(int &a, int &b, int x){
    int temp = mul(x, b); b = a;
    add(a, temp); add(b, MOD - temp);
  }
  void fft(vector<int> &a, bool inv){
    int n = __builtin_ctz((int)(a.size()));
    for (int i = 0; i < (1<<n); i++){
      int temp = brev[i] >> (MROOT - n);
      if (temp > i) swap(a[i], a[temp]);
    }
    for (int step = 0; step < n; step++){
      int pos = 0; /*BOXNEXT*/
      int dlt = (inv ? -1 : 1) * (1 << (MROOT - step - 1));
      for (int i = 0; i < (1<<n); i++){
        if ((i ^ (1<<step)) > i) /*BOXNEXT*/
          butterfly(a[i], a[i ^ (1<<step)], rts[pos]);
        pos = (pos + dlt) & (MROOTP-1);
      }
    }
  }
  vector<int> multiply(vector<int> a, vector<int> b){
    int rsz = (int)(a.size()) + (int)(b.size()), rsz2 = 1;
    while (rsz2 < rsz) rsz2 *= 2;
    a.resize(rsz2); b.resize(rsz2);
    fft(a, false); fft(b, false);
    for (int i = 0; i < (int)(a.size()); i++)
      a[i] = mul(a[i], b[i]);
    fft(a, true);
    int in = mpow((int)(a.size()), MOD - 2);
    for (int i = 0; i < (int)(a.size()); i++)
      a[i] = mul(a[i], in);
    return a;
  }
}

vector<int> get_counts_recursive(const vector<int> &a, int l, int r) {
  if (r - l == 1) {
    return vector<int>{1, a[l]};
  }
  int m = (l + r) / 2;
  return multiplier::multiply(get_counts_recursive(a, l, m), get_counts_recursive(a, m, r));
}

vector<int> get_counts(const vector<int> &a) {
  return get_counts_recursive(a, 0, a.size());
}

const int MAXN = 110000;

vector<int> g[MAXN];
int n, k;
int sz[MAXN];

int dfs_sz(int v, int p = -1) {
  sz[v] = 1;
  for (int u : g[v]) {
    if (u != p) {
      sz[v] += dfs_sz(u, v);
    }
  }
  return sz[v];
}

int facs[MAXN];
int ifacs[MAXN];

int cnk(int n, int k) {
  return mul(facs[n], mul(ifacs[k], ifacs[n - k]));
}

vector<int> polys[MAXN];
map<pair<int, int>, int> cache;
int down[MAXN];

int get_cnt(int v, int val) {
  auto it = cache.find({v, val});
  if (it != cache.end()) return it->second;
  int& ans = cache[{v, val}];

  int r = 0;
  for (int i = 0; i < (int)polys[v].size(); i++) {
    int t = polys[v][i];
    sub(t, mul(r, val));
    r = t;
    t = mul(t, cnk(k, i));
    add(ans, t);
  }

  return ans;
}

int dfs_down(int v, int p = -1) {
  down[v] = get_cnt(v, n - sz[v]);

  for (int u : g[v]) {
    if (u != p) {
      down[v] += dfs_down(u, v);
    }
  }
  return down[v];
}

int ans;



int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  facs[0] = ifacs[0] = 1;
  for (int i = 1; i < MAXN; i++) {
    facs[i] = mul(facs[i - 1], i);
    ifacs[i] = mul(ifacs[i - 1], minv(i));
  }

  scanf("%d%d", &n, &k);

  for (int i = 1; i < n; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  dfs_sz(0);

  for (int i = 0; i < n; i++) {
    vector<int> szs;
    for (int v : g[i]) {
      if (sz[v] > sz[i]) {
        szs.push_back(n - sz[i]);
      } else {
        szs.push_back(sz[v]);
      }
    }
    polys[i] = get_counts(szs);
  }

  dfs_down(0);
//  dfs_up(0, -1, 0);

  printf("%d\n", ans);
  return 0;
}
