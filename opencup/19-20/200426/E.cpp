#ifdef LOCAL
#define DBG1
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
typedef pair <ll, int> pll;

const ll INF = (1LL << 60);

struct RangeTree {
  int kk;
  vector<pll> min_;
  vector<pll> max_;
  vector<ll> add_;

  RangeTree(int n) {
    kk = 1;
    while (kk < n) {
      kk *= 2;
    }
    min_.resize(2 * kk + 10);
    max_.resize(2 * kk + 10);
    add_.resize(2 * kk + 10);

    for (int i = 0; i < kk; ++i) {
      min_[i + kk] = {0, i};
      max_[i + kk] = {0, i};
    }
    for (int i = kk - 1; i >= 1; --i) {
      update(i);
    }
  }

  void update(int t) {
    min_[t] = min(min_[2 * t], min_[2 * t + 1]);
    max_[t] = max(max_[2 * t], max_[2 * t + 1]);
  }

  void print() {
    print(1, 0, kk - 1);
    dbg("\n");
  }

  void print(int t, int Lt, int Rt) {
    if (Lt == Rt) {
      return;
    }
    pushModify(t);
    int Mt = (Lt + Rt) / 2;
    print(2 * t, Lt, Mt);
    print(2 * t + 1, Mt + 1, Rt);
  }

  void add(int L, int R, int delta) {
    return add(1, 0, kk - 1, L, R, delta);
  }

  pll get_min(int L, int R) {
    return get_min(1, 0, kk - 1, L, R);
  }

  pll get_max(int L, int R) {
    return get_max(1, 0, kk - 1, L, R);
  }

  void add(int t, int Lt, int Rt, int Lq, int Rq, int delta) {
    if (Rt < Lq || Rq < Lt) {
      return;
    }
    if (Lq <= Lt && Rt <= Rq) {
      addEntire(t, delta);
      return;
    }
    pushModify(t);
    int Mt = (Lt + Rt) / 2;
    add(2 * t, Lt, Mt, Lq, Rq, delta);
    add(2 * t + 1, Mt + 1, Rt, Lq, Rq, delta);
    update(t);
  }

  pll get_max(int t, int Lt, int Rt, int Lq, int Rq) {
    if (Rt < Lq || Rq < Lt) {
      return {-INF, -1};
    }
    if (Lq <= Lt && Rt <= Rq) {
      return max_[t];
    }
    pushModify(t);
    int Mt = (Lt + Rt) / 2;
    return max(get_max(2 * t, Lt, Mt, Lq, Rq), get_max(2 * t + 1, Mt + 1, Rt, Lq, Rq));
  }

  pll get_min(int t, int Lt, int Rt, int Lq, int Rq) {
    if (Rt < Lq || Rq < Lt) {
      return {INF, -1};
    }
    if (Lq <= Lt && Rt <= Rq) {
      return min_[t];
    }
    pushModify(t);
    int Mt = (Lt + Rt) / 2;
    return min(get_min(2 * t, Lt, Mt, Lq, Rq), get_min(2 * t + 1, Mt + 1, Rt, Lq, Rq));
  }

  void pushModify(int t) {
    addEntire(2 * t, add_[t]);
    addEntire(2 * t + 1, add_[t]);
    add_[t] = 0;
  }

  void addEntire(int t, ll delta) {
    add_[t] += delta;
    min_[t].first += delta;
    max_[t].first += delta;
  }
};

struct Segment {
  int L;
  int R;
  ll max_bal;
  int max_pos;
  ll min_bal;
  int min_pos;
};

struct MaxComp {
  bool operator()(const Segment &s1, const Segment &s2) const {
    return s1.max_bal > s2.max_bal;
  }
};

struct MinComp {
  bool operator()(const Segment &s1, const Segment &s2) const {
    return s1.min_bal < s2.min_bal;
  }
};


Segment buildSegment(RangeTree &tree, int L, int R) {
  auto [max_bal, max_pos] = tree.get_max(L, R);
  auto [min_bal, min_pos] = tree.get_min(L, R);
  return {L, R, max_bal, max_pos, min_bal, min_pos};
}


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

bool solve() {
  int n;
  if (scanf("%d", &n) != 1) { return false; }

  vector<int> a(n);
  for (int & x : a) {
    scanf("%d", &x);
  }

  vector<int> pref(n);
  for (int i = 0; i < n; ++i) {
    pref[i] = 0;
    if (i > 0 && pref[i - 1] > 0) {
      pref[i] = pref[i - 1];
    }
    pref[i] += a[i];
  }

  RangeTree tree(n);
  for (int i = 0; i < n; ++i) {
    tree.add(i, i, pref[i]);
  }

  multiset<Segment, MaxComp> segs;
  for (int i = 0; i < n;++i) {
    if (pref[i] <= 0) {
      segs.emplace(buildSegment(tree, i, i));
    } else {
      int j = i;
      while (j + 1 < n && pref[j + 1] > 0) {
        j++;
      }
      segs.emplace(buildSegment(tree, i, j));
      i = j;
    }
  }

  multiset<Segment, MinComp> active_segs;
  ll k;
  scanf("%lld\n", &k);
  ll cur_ans = segs.begin()->max_bal;
  ll init_ans = cur_ans;
  ll T = 0;
  vector<pair<ll, ll>> result;
  int active_neg = 0;
  while ((int)active_segs.size() + active_neg < n) {
    if (segs.empty() || (!active_segs.empty() && active_segs.begin()->min_bal - T < cur_ans - segs.begin()->max_bal)) {
      Segment s = *active_segs.begin();
      ll t = s.min_bal - T;
      result.emplace_back(t, active_segs.size() + active_neg);
      cur_ans -= t;
      T += t;
      active_segs.erase(active_segs.begin());
      tree.add(s.L, s.R, -s.min_bal);
      if (s.L < s.min_pos) {
        segs.insert(buildSegment(tree, s.L, s.min_pos - 1));
      }
      if (s.min_pos < s.R) {
        segs.insert(buildSegment(tree, s.min_pos + 1, s.R));
      }
      segs.insert(buildSegment(tree, s.min_pos, s.min_pos));
    } else {
      ll t = cur_ans - segs.begin()->max_bal;
      result.emplace_back(t, active_segs.size() + active_neg);
      cur_ans -= t;
      T += t;

      Segment s = *segs.begin();
      segs.erase(segs.begin());
      tree.add(s.L, s.R, T);
      s = buildSegment(tree, s.L, s.R);
      if (s.max_bal <= 0) {
        active_neg++;
      } else {
        active_segs.insert(s);
      }
    }
  }
  result.emplace_back(k, n);

  int ans = 0;
  auto norm = [](ll x) {
    return (x % MOD + MOD) % MOD;
  };
  for (auto [t, cost] : result) {
    if (t == 0) continue;
    ll full = std::min(k / cost, t);
    add(ans, mul(cost, mul(full, mul(norm(init_ans * 2 % MOD - full + 1),  (MOD + 1)/2))));
    sub(ans, full);
    init_ans -= full;
    k -= cost * full;
    if (full < t) {
      assert(k < cost);
      add(ans, mul(init_ans, k));
      k = 0;
      break;
    }
  }
  assert(k == 0);

  printf("%d\n", ans);

  return true;
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
#endif
  while (solve());
  return 0;
}
