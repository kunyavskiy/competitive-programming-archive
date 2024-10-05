#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <numeric>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x)                                                           \
  eprintf("[" #x "] Time : %.3lf s.\n",                                        \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...)                                                     \
  eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__,                            \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() { TIMESTAMPf("%s", what.data()); }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

struct stack_op {
  int is_push;
  ll sum;
  ll ans;
  int count;
};

vector<vector<stack_op>> get_stack_ops(vector<int> d) {
  struct item {
    ll sum, ans;
    int count;
  };
  vector<item> s;
  vector<vector<stack_op>> ops;
  auto push = [&](ll sum, ll ans, int count) {
    s.emplace_back(sum, ans, count);
    ops.back().push_back(stack_op{true, sum, ans, count});
  };
  auto pop = [&]() {
    ops.back().push_back(stack_op{false, s.back().sum, s.back().ans, s.back().count});
    s.pop_back();
  };
  for (int x : d) {
    ops.push_back({});
    ll cur_sum = x;
    ll cur_ans = x;
    int cur_count = 1;
    // s.back().sum / s.back().count >= cur_sum / cur_count
    while (!s.empty() && (s.back().sum * cur_count >= cur_sum * s.back().count)) {
      cur_ans += cur_sum * s.back().count + s.back().ans;
      cur_sum += s.back().sum;
      cur_count += s.back().count;
      pop();
    }
    push(cur_sum, cur_ans, cur_count);
  }
  return ops;
}

struct item {
  ll sum;
  ll cost;
  int count;
  ll sum_below;
  int count_below;
};


bool cmp(const item& a, const item& b) {
  return a.sum * b.count < b.sum * a.count;
};

struct TwoStacks {
  vector<item> s[2];
  ll cur_ans = 0;


  ll get_ans() {
#ifdef LOCAL
    vector<item> a = s[0];
    a.insert(a.end(), s[1].begin(), s[1].end());
    sort(a.begin(), a.end(), cmp);

    ll ans = 0;
    int curw = 0;
    for (int i = 0; i < (int)a.size(); i++) {
      ans += a[i].cost;
      ans += a[i].sum * curw;
      curw += a[i].count;
    }
    assert(ans == cur_ans);
#endif
    return cur_ans;
  }

  int count_below2(int id, int position) {
    if (position < 0) return 0;
    return s[id][position].count_below;
  }
  ll sum_below2(int id, int position) {
    if (position < 0) return 0;
    return s[id][position].sum_below;
  }


  void push(int id, ll sum, ll cost, int count) {
    cur_ans += cost;
    ll sum_below = s[id].empty() ? 0 : s[id].back().sum_below;
    int count_below = s[id].empty() ? 0 : s[id].back().count_below;
    cur_ans += sum * count_below;
    s[id].push_back(item{sum, cost, count, sum_below + sum, count_below + count});
    int position = lower_bound(s[id^1].begin(), s[id ^ 1].end(), s[id].back(), cmp) - s[id^1].begin();
    cur_ans += count_below2(id ^ 1, position - 1) * sum;
    cur_ans += (sum_below2(id ^ 1, (int)s[id^1].size() - 1) - sum_below2(id ^ 1, position - 1)) * count;
  }
  void pop(int id, ll sum, ll cost, int count) {
    int position = lower_bound(s[id^1].begin(), s[id ^ 1].end(), s[id].back(), cmp) - s[id^1].begin();
    cur_ans -= (sum_below2(id ^ 1, (int)s[id^1].size() - 1) - sum_below2(id ^ 1, position - 1)) * count;
    cur_ans -= count_below2(id ^ 1, position - 1) * sum;
    s[id].pop_back();

    int count_below = s[id].empty() ? 0 : s[id].back().count_below;
    cur_ans -= sum * count_below;
    cur_ans -= cost;
  }

  void apply(int id, bool undo, stack_op op) {
    if (op.is_push ^ undo) {
      push(id, op.sum, op.ans, op.count);
    } else {
      assert(!s[id].empty());
      assert(s[id].back().sum == op.sum);
      assert(s[id].back().cost == op.ans);
      assert(s[id].back().count == op.count);
      pop(id, op.sum, op.ans, op.count);
    }
  }
};

ll solve(vector<int> d) {
  vector<vector<stack_op>> f = get_stack_ops(d);
  reverse(d.begin(), d.end());
  vector<vector<stack_op>> s = get_stack_ops(d);
  reverse(d.begin(), d.end());
  reverse(s.begin(), s.end());

  TwoStacks solver;

  for (int i = (int)d.size() - 1; i > 0; i--) {
    for (const auto &op : s[i]) {
      solver.apply(1, false, op);
    }
  }

  ll ans = 0;

  for (int i = 0; i + 1 < (int)d.size(); i++) {
    if (i > 0) {
      for (auto op : f[i - 1]) {
        solver.apply(0, false, op);
      }
    }
    reverse(s[i+1].begin(), s[i+1].end());
    for (auto op : s[i + 1]) {
      solver.apply(1, true, op);
    }
    /*
    eprintf("i = %d, ans = %lld, part=%lld, l = %d\n", i, solver.get_ans() + ((ll)d.size() - 1LL) * (d[i] + d[i+1]), solver.get_ans(), d[i] + d[i+1]);
    for (int it = 0; it < 2; it++) {
      eprintf("s%d: ", it);
      for (auto x : solver.s[it]) {
        eprintf("(%lld, %lld, %d)\n", x.sum, x.cost, x.count);
      }
      eprintf("\n");
    }
     */
    ans = max(ans, solver.get_ans() + ((ll)d.size() - 1LL) * (d[i] + d[i+1]));
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<int> a(n);
    for (int &x : a) {
      scanf("%d", &x);
    }
    a.push_back(0);
    a.push_back(m + 1);
    sort(a.begin(), a.end());
    vector<int> d(n + 1);
    for (int i = 0; i <= n; i++) {
      d[i] = a[i + 1] - a[i];
    }
    printf("%lld\n", solve(d));
  }

  return 0;
}
