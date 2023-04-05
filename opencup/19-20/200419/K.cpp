#ifdef DBG1
#define LOCAL
#endif

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <cmath>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <functional>

#ifdef DBG1
#define dbg(...) fprintf(stderr, __VA_ARGS__)
#else
#define dbg(...)
#endif

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair <int, int> pii;

struct RangeTree {
  int kk;
  vector<ll> b;

  RangeTree(int n) {
    kk = 1;
    while (kk < n) {
      kk *= 2;
    }
    b.resize(2 * kk + 10);
  }

  void print() const {
//    for (auto & x : b) {
//      dbg("%lld ", x);
//    }
//    dbg("\n");
  }

  void assign(int t, ll val) {
    t += kk;
    b[t] = val;
//    dbg("b[%d] = %lld\n", t, b[t]);
    while (t > 1) {
      t /= 2;
      b[t] = b[2 * t] + b[2 * t + 1];
//      dbg("b[%d] = %lld\n", t, b[t]);
    }
  }

  int find_kth(int t, int L, int R, ll k) const {
//    dbg("find_kth t %d b[t] %lld L %d R %d k %lld\n", t, b[t], L, R, k);
    assert(0 < k && k <= b[t]);
    if (L == R) {
      return L;
    }
    int M = (L + R) / 2;
    if (k <= b[2 * t]) {
      return find_kth(2 * t, L, M, k);
    } else {
      return find_kth(2 * t + 1, M + 1, R, k - b[2 * t]);
    }
  }

  int find_kth(ll k) const {
    return find_kth(1, 0, kk - 1, k);
  }

  ll sum(int L, int R) const {
    ll res = 0;
    L += kk, R += kk;
    while (L <= R) {
      if (L % 2 == 1) {
        res += b[L++];
      }
      if (R % 2 == 0) {
        res += b[R--];
      }
      L /= 2, R /= 2;
    }
    return res;
  }

  ll get(int index) const {
    return sum(index, index);
  }
};

ll solve(const RangeTree &tree_sum, const RangeTree&tree_cnt, ll k) {
//  tree_cnt.print();
  int x = tree_cnt.find_kth(k);

  dbg("x %d\n", x);

  if (x == 1) {
    return k;
  }

  ll cnt_small = tree_cnt.sum(0, x - 1);
  ll sum_small = tree_sum.sum(0, x - 1);

  ll res = 0;
  res += sum_small;
  k -= cnt_small;
  dbg("small %lld %lld\n", cnt_small, sum_small);

  ll cur = tree_cnt.get(x);
  while (1) {
    dbg("k %lld x %d cur_cnt %lld\n", k, x, cur);
    assert(k > 0);

    if (cur == k) {
      res += x * cur;
      k = 0;
      break;
    }

    assert(cur > k);

    ll new_next = 0;

    ll half = cur / 2;
    ll it = min(k, half);
    res += it * (x - 1);
    new_next += it;
    k -= it;
    dbg("%lld * (%d - 1)\n", it, x);

    if (k) {
      res += x;
      k--;
      dbg("%d * %d\n", 1, x);
    }

    if (k) {
      x++;
      cur = tree_cnt.get(x) + new_next;
    } else {
      break;
    }
  }
  return res;
}

bool solve() {
  int q;
  if (scanf("%d", &q) != 1) { return false; }
  const int MAX = 1000100;
  RangeTree tree_sum(MAX);
  RangeTree tree_cnt(MAX);
  for (int i = 0; i < q; ++i) {
    int t;
    scanf("%d", &t);

    if (t == 1) {
      int x, y;
      scanf("%d%d", &x, &y);
      dbg("add hp %d cnt %d\n", x, y);
      tree_cnt.assign(x, y);
      tree_sum.assign(x, ll(x) * y);

//      tree_cnt.print();
    } else if (t == 2) {
      ll k;
      scanf("%lld", &k);
      dbg("get k %lld\n", k);
      printf("%lld\n", solve(tree_sum, tree_cnt, k));
    } else {
      assert(0);
    }
  }

  return true;
}

int main() {
  freopen("k.in", "r", stdin);
  while (solve());
  return 0;
}
