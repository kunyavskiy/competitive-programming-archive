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

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


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

static const int BITS = 30;
struct item {
  int min = 0, min2 = 0;
  int cntmin = 0;
  int x = 0;
  int chgmin = -1;
  array<int, BITS> cnt{};
};

item merge(const item &a, const item &b) {
  item res;
  res.x = a.x ^ b.x;
  for (int i = 0; i < BITS; i++) {
    res.cnt[i] = a.cnt[i] + b.cnt[i];
  }
  res.min = min(a.min, b.min);
  if (res.min == a.min) res.cntmin += a.cntmin;
  if (res.min == b.min) res.cntmin += b.cntmin;
  res.min2 = min((res.min == a.min) ? a.min2 : a.min, (res.min == b.min) ? b.min2 : b.min);
  return res;
}

vector<item> tree;

void maxeq(int v, int val) {
  if (v > (int)tree.size()) return;
  assert(val < tree[v].min2);
  if (tree[v].min >= val) return;
  assert(tree[v].chgmin <= val);
  tree[v].chgmin = val;
  if (tree[v].cntmin % 2 == 1) {
    tree[v].x ^= tree[v].min ^ val;
  }
  for (int i = 0; i < BITS; i++) {
    if (tree[v].min & (1 << i)) {
      tree[v].cnt[i] -= tree[v].cntmin;
    }
    if (val & (1 << i)) {
      tree[v].cnt[i] += tree[v].cntmin;
    }
  }
  tree[v].min = val;
}

void push(int v) {
  if (tree[v].chgmin != -1) {
    maxeq(2 * v, tree[v].chgmin);
    maxeq(2 * v + 1, tree[v].chgmin);
    tree[v].chgmin = -1;
  }
}

void maxeq(int v, int l, int r, int L, int R, int val) {
  if (r <= L || R <= l) return;
  if (L <= l && r <= R && tree[v].min2 > val) {
    maxeq(v, val);
    return;
  }
  push(v);
  maxeq(2 * v + 0, l, (l + r) / 2, L, R, val);
  maxeq(2 * v + 1, (l + r) / 2, r, L, R, val);
  tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
}

int get_xor(int v, int l, int r, int L, int R) {
  if (r <= L || R <= l) return 0;
  if (L <= l && r <= R) {
    return tree[v].x;
  }
  push(v);
  return get_xor(2 * v + 0, l, (l + r) / 2, L, R) ^
         get_xor(2 * v + 1, (l + r) / 2, r, L, R);
}

int get_cnt(int v, int l, int r, int L, int R, int bit) {
  if (r <= L || R <= l) return 0;
  if (L <= l && r <= R) {
    return tree[v].cnt[bit];
  }
  push(v);
  return get_cnt(2 * v + 0, l, (l + r) / 2, L, R, bit) +
         get_cnt(2 * v + 1, (l + r) / 2, r, L, R, bit);
}

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int n, q;
  while (scanf("%d%d", &n, &q) == 2) {
    int lst = 2;
    while (lst < n) lst *= 2;
    tree.resize(2 * lst);
    for (int i = 0; i < n; i++) {
      item &t = tree[i + lst];
      int a;
      scanf("%d", &a);
      t.min = t.x = a;
      t.cntmin = 1;
      t.chgmin = -1;
      t.min2 = numeric_limits<int>::max();
      for (int b = 0; b < BITS; b++) {
        if (a & (1 << b)) {
          t.cnt[b] = 1;
        }
      }
    }
    for (int i = lst - 1; i > 0; i--) {
      tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
    }
    for (int i = 0; i < q; i++) {
      int op, l, r, x;
      scanf("%d%d%d%d", &op, &l, &r, &x);
      --l;
      if (op == 1) {
        maxeq(1, 0, lst, l, r, x);
      } else {
        int tot_xor = get_xor(1, 0, lst, l, r) ^ x;
        int ans = 0;
        int bit = -1;
        for (int i = 0; i < BITS; i++) {
          if (tot_xor & (1 << i)) {
            bit = i;
          }
        }
        eprintf("%d %d\n", tot_xor, bit);
        if (bit != -1) {
          if (x & (1 << bit)) ans++;
          ans += get_cnt(1, 0, lst, l, r, bit);
        }
        printf("%d\n", ans);
      }
    }
  }

  return 0;
}
