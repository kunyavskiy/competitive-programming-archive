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

class SegmentTreeSum {
  typedef int value_t;
  static const value_t EMPTY_VALUE;

  static inline value_t merge_values(const value_t &a, const value_t &b) {
    return a + b;
  }


  vector<value_t> tree;
  int lst;

  value_t get(int v, int l, int r, int L, int R) {
    if (r <= L || R <= l) {
      return EMPTY_VALUE;
    }
    if (L <= l && r <= R) {
      return tree[v];
    }
    return merge_values(get(2 * v, l, (l + r) / 2, L, R), get(2 * v + 1, (l + r) / 2, r, L, R));
  }

  void update(int v, int l, int r, int L, int R, const value_t &u) {
    if (r <= L || R <= l) {
      return;
    }
    if (L <= l && r <= R) {
      assert(L == R - 1);
      tree[v] = u;
      return;
    }
    update(2 * v, l, (l + r) / 2, L, R, u);
    update(2 * v + 1, (l + r) / 2, r, L, R, u);
    tree[v] = merge_values(tree[2 * v], tree[2 * v + 1]);
  }

public:

  void init(int n) {
    lst = 2;
    while (lst < n) lst *= 2;
    tree = vector<value_t>((size_t) (2 * lst), EMPTY_VALUE);
  }

  value_t get(int l, int r) {
    return get(1, 0, lst, l, r);
  }

  void update(int l, value_t u) {
    return update(1, 0, lst, l, l + 1, u);
  }
};

class SegmentTreeMin {
  typedef pair<int, int> value_t;
  typedef pair<int, int> update_t;

  static const value_t EMPTY_VALUE;

  static inline value_t merge_values(const value_t &a, const value_t &b) {
    return min(a, b);
  }

  vector<value_t> tree;
  int lst;

  value_t get(int v, int l, int r, int L, int R) {
    if (r <= L || R <= l) {
      return EMPTY_VALUE;
    }
    if (L <= l && r <= R) {
      return tree[v];
    }
    return merge_values(get(2 * v, l, (l + r) / 2, L, R), get(2 * v + 1, (l + r) / 2, r, L, R));
  }

  void update(int v, int l, int r, int L, int R, const value_t &u) {
    if (r <= L || R <= l) {
      return;
    }
    if (L <= l && r <= R) {
      assert(L == R - 1);
      tree[v] = u;
      return;
    }
    update(2 * v, l, (l + r) / 2, L, R, u);
    update(2 * v + 1, (l + r) / 2, r, L, R, u);
    tree[v] = merge_values(tree[2 * v], tree[2 * v + 1]);
  }

public:

  void init(int n) {
    lst = 2;
    while (lst < n) lst *= 2;
    tree = vector<value_t>((size_t) (2 * lst), EMPTY_VALUE);
  }

  value_t get(int l, int r) {
    return get(1, 0, lst, l, r);
  }

  void update(int l, value_t u) {
    return update(1, 0, lst, l, l + 1, u);
  }
};

const int INF = 1 << 30;

const SegmentTreeSum::value_t SegmentTreeSum::EMPTY_VALUE = 0;
const SegmentTreeMin::value_t SegmentTreeMin::EMPTY_VALUE = {INF, 0};


SegmentTreeSum trees;
SegmentTreeMin treem;

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

int minv(int a) {
  return mpow(a, MOD - 2);
}

vector<int> m;
map<int, int> s;
int ans;

void remove_s(int from, int to, int val) {
  int cnt = trees.get(from, to);
  ans = mul(ans, minv(mpow(val, cnt)));
}

void add_s(int from, int to, int val) {
  while (true) {
    auto x = treem.get(from, to);
    if (x.first > val) {
      break;
    }
    ans = mul(ans, x.first);
    treem.update(x.second, {INF, x.second});
    trees.update(x.second, 0);
  }

  int cnt = trees.get(from, to);
  ans = mul(ans, mpow(val, cnt));
}


void update_s(int pos, int val) {
  auto it = s.upper_bound(pos);
  assert(it != s.begin());
  --it;
  if (it->second >= val) {
    return;
  }
  auto nit = it;
  nit++;
  remove_s(it->first, nit->first, it->second);
  if (pos != it->first) {
    auto it2 = s.insert({pos, val}).first;
    add_s(it->first, it2->first, it->second);
    it = it2;
  } else {
    s[pos] = val;
  }

  while (nit->second < val) {
    it = nit;
    nit++;
    remove_s(it->first, nit->first, it->second);
    s.erase(it);
  }
  add_s(pos, nit->first, val);
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n, k, x;
  scanf("%d%d%d", &n, &k, &x);
  m = vector<int> (n);

  trees.init(n);
  treem.init(n);
  ans = 1;

  for (int i = 0; i < n; i++) {
    scanf("%d", &m[i]);
    if (m[i] <= x) {
      trees.update(i, 0);
      treem.update(i, {INF, i});
      ans = mul(ans, m[i]);
    } else {
      trees.update(i, 1);
      treem.update(i, {m[i], i});
      ans = mul(ans, x);
    }
  }

  s[0] = x;
  s[n] = INF;

  eprintf("ans = %d\n", ans);

  for (int i = 0; i < n; i++) {
    int s;
    scanf("%d", &s);
    if (s > x) {
      update_s(i + 1, s);
    }
  }

  printf("%d\n", ans);
  for (int i = 0; i < k; i++) {
    int ty;
    scanf("%d", &ty);
    if (ty == 0) {
      int pos, mm;
      scanf("%d%d", &pos, &mm);
      pos--;
      auto it = s.upper_bound(pos);
      assert(it != s.begin());
      auto nit = it;
      --it;
      remove_s(it->first, nit->first, it->second);
      if (trees.get(pos, pos + 1) == 0) {
        ans = mul(ans, minv(m[pos]));
      }
      trees.update(pos, 1);
      treem.update(pos, {mm, pos});
      add_s(it->first, nit->first, it->second);
      m[pos] = mm;
    } else {
      int pos, s;
      scanf("%d%d", &pos, &s);
      update_s(pos, s);
    }
    printf("%d\n", ans);
  }



  return 0;
}
